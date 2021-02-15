#include "HttpClient.h"

#include <time.h>
#include <unistd.h>
#include <curl/curl.h>
#include <iostream>

using namespace std;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


HttpRequest::HttpRequest(const string& method, const string& endpoint)
 :m_method(method),
 m_endpoint(endpoint),
 m_curl(nullptr),
 m_curl_headers(nullptr)
{}
    
void HttpRequest::AddHeader(const string& name, const string& value)
{
    m_headers[name] = value;
}

void HttpRequest::AddBody(vector<unsigned char> bytes)
{
    m_body = bytes;
}

void HttpRequest::AddBody(const string body)
{
    m_body = vector<unsigned char>(&body.c_str()[0], &body.c_str()[body.size()]);
}

vector<unsigned char> HttpRequest::GetBodyData()
{
    return m_body;
}


map<string,string> HttpRequest::GetHeaders()
{
    return this->m_headers;
}

CURL* HttpRequest::GetCURL(const string& host, int port)
{
    if(m_curl == nullptr) {
        curl_global_init(CURL_GLOBAL_ALL);

        m_curl = curl_easy_init();
        if(! m_curl) return NULL;
        
        curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, this->m_method.c_str());

        auto headers = this->GetCurlHeaders();
        if(headers != NULL) {
            curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headers);
        }

        if(m_body.size() > 0) {
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, &m_body.at(0));
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, m_body.size());
        }
    }
    string url = host + ":" + to_string(port);
    if( ends_with(url, "/")) {
        url += "/";
    } 
    url += this->m_endpoint;

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    return m_curl;
}

struct curl_slist * HttpRequest::GetCurlHeaders()
{
    struct curl_slist *headers=NULL;

    for(auto it = m_headers.begin(); it != m_headers.end(); it++)
    {
        string header = it->first + ": " + it->second;
        headers = curl_slist_append(headers, header.c_str());
    }
    return headers;
}


HttpRequest::~HttpRequest()
{
    if(m_curl != nullptr) {
        curl_easy_cleanup(m_curl);
    }
    if(m_curl_headers != nullptr) {
        curl_slist_free_all(m_curl_headers);
    }
}



static size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e)
    {
        return 0;
    }
    return newLength;
}

HttpClient::HttpClient(std::string host, unsigned short port) :
m_host(host),
m_port(port)
{
}



HttpStatusCode HttpClient::DoRequest(HttpRequest& request)
{
    auto curl = request.GetCURL(this->m_host, this->m_port);

    if(curl)
    {

        string response = "";
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
      }
      sleep(2);
      return HttpStatusCode::HTTP_STATUS_OK;
}

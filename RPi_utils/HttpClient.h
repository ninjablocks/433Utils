
#include <string>
#include <vector>
#include <map>

#include "curl/curl.h"

typedef enum {
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_UNAUTHORIZED = 401,
    HTTP_STATUS_FORBIDDEN = 403,
    HTTP_STATUS_NOT_FOUNT = 404,
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500
} HttpStatusCode;

class HttpRequest {
public:
    HttpRequest(const std::string& method, const std::string& endpoint);
    
    void AddHeader(const std::string& name, const std::string& value);

    void AddBody(std::vector<unsigned char> bytes);

    void AddBody(const std::string body);

    std::vector<unsigned char> GetBodyData();

    std::map<std::string,std::string> GetHeaders();

    CURL * GetCURL(const std::string& host, int port);

    ~HttpRequest();

private:
    struct curl_slist * GetCurlHeaders();

    std::map<std::string, std::string> m_headers;
    std::string m_method;
    std::string m_endpoint;
    std::vector<unsigned char> m_body;

    struct curl_slist * m_curl_headers;

    CURL* m_curl;
};

class HttpClient {
public:
    HttpClient(std::string host, unsigned short port);
    
    HttpStatusCode DoRequest(HttpRequest& request);
private:

    std::string m_host;
    unsigned short m_port;

};
#include <stdio.h>
#include <stdlib.h>
#include "HttpClient.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <unistd.h>

#include <mqueue.h>

#include <string.h>

#include <signal.h>

#define QUEUE_PERMISSIONS 0660

using namespace std;

static int32_t qid;

mqd_t mqd;

static void intHandler(int dummy) {
    mq_close(mqd);
    mq_unlink("/RFSniffer_MQ");
    exit(0);
}


static int32_t send_value_http(int32_t value)
{
    HttpClient client("http://192.168.15.9", 8080);
    HttpRequest req("PUT", "/signal");
    char body[32];

    signal(SIGINT, intHandler);

    sprintf(body, "Received %d", value);

    req.AddHeader("Content-Type", "text/*");
    
    req.AddBody(string(body));
    

    HttpStatusCode ret = client.DoRequest(req);
    return  (int) ret;
}

int main(int argc, char * argv[])
{

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(int);
    attr.mq_curmsgs = 0;

    mqd = mq_open("/RFSniffer_MQ", O_CREAT | O_RDONLY ,  0660, &attr);
    if(mqd == -1) {
        perror("mq_open");
        return -1;
    }

    while(1)
    {
        char *buffer = (char*) calloc (sizeof(int), 10);
        unsigned int priority = 0;

        if ((mq_receive (mqd, buffer, sizeof(int) *10, NULL)) == -1)
        {
            perror ("Failed to receive message\n");

            continue;
        }

        int value = *((int*)buffer);
        //rfs_message.message.value = 12;
        printf(" Received message value [%d]\n", value);

        send_value_http(value);

        free(buffer);
    }
    
    mq_close(mqd);

    return 0;
}

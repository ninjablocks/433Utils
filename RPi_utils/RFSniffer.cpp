/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <mqueue.h>
     
RCSwitch mySwitch;

static mqd_t mqd = -1;
static struct mq_attr attr;

static int send_value_to_mq(int value)
{
  if(mqd == -1)
  {
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(int);
    attr.mq_curmsgs = 0;

    mqd = mq_open("/RFSniffer_MQ", O_WRONLY ,  0777, &attr);
  }
  
  if(mqd == -1) {
    perror("mq_open");
    return -1;
  }

  attr.mq_flags |= O_NONBLOCK;
  mq_setattr(mqd, &attr, NULL);
  if(mq_send(mqd,(char*) &value, sizeof(int), 0) == -1)
  {
    perror("mq_send: ");
    mq_close(mqd);
    mqd = -1;
    return -1;
  }
  attr.mq_flags &= (~O_NONBLOCK);
  mq_setattr(mqd, &attr, NULL);

  return 0;
}

int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }

     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
   
          attr.mq_flags |= O_NONBLOCK;
          send_value_to_mq(value);
        }
    
        fflush(stdout);
        mySwitch.resetAvailable();
      }
      usleep(100);
  }

  exit(0);


}


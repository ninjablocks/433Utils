/*
  Usage: ./send <systemCode> <unitCode> <command> [<pulseLength>]
  Command is 0 for OFF and 1 for ON

  [] = optional
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    char* systemCode = argv[1];
    int unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);
    int pulseLength = 0;
    if (argv[4] != NULL) pulseLength = atoi(argv[4]);
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
	RCSwitch mySwitch = RCSwitch();
	if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
	mySwitch.enableTransmit(PIN);
    
    switch(command) {
        case 1:
            mySwitch.switchOn(systemCode, unitCode);
            break;
        case 0:
            mySwitch.switchOff(systemCode, unitCode);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
	return 0;
}

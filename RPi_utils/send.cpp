/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    const char* code[6] = { "00000", "10000", "01000", "00100", "00010", "00001" };

    if (argc < 4) {
        printf("Sending 433 MHz remote plug control codes, hardcoded on wiringpi pin %d.\n", PIN);
        printf("Usage: %s <systemCode> <unitCode> <command> [pulseLength]\n", argv[0]);
        printf("systemCode  - First five settings of Type A 10 pole DIP switch, e.g. 11111\n");
        printf("unitCode    - Switch number [1 .. 5] or [10000 .. 00001]\n");
        printf("command     - 0 for OFF and 1 for ON\n");
        printf("pulseLength - optional pulse length\n");
        return -1;
    }

    char* systemCode = argv[1];
    const char* unitCode;
    if (strlen(argv[2]) == 5) {
        unitCode = argv[2];
    } else if (atoi(argv[2]) > 0 and atoi(argv[2]) < 6) {
        unitCode = code[atoi(argv[2])];
    } else {
        return -1;
    }
    int command  = atoi(argv[3]);

    if (wiringPiSetup () == -1) return 1;
    printf("sending systemCode[%s] unitCode[%s] command[%i]\n", systemCode, unitCode, command);
    RCSwitch mySwitch = RCSwitch();
    if (argv[4] != NULL)
        mySwitch.setPulseLength(atoi(argv[4]));
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

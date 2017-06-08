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
     XIO-P* do not have a good enough time resolution to work properly
     */
    int PIN;
    if( get_gpio_number("AP-EINT3", &PIN) == -1 )
        return 2;
    if( gpio_allowed(PIN) < 1 )
        return 3;
    gpio_unexport(PIN);
    if( gpio_export(PIN) < 0 )
        return 4;

    char* systemCode = argv[1];
    int unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);
    
    printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
    RCSwitch mySwitch = RCSwitch();
    if (argv[4] != NULL) mySwitch.setPulseLength(atoi(argv[4]));
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
	    gpio_unexport(PIN);
            return -1;
    }

    gpio_unexport(PIN);
    return 0;
}

/*

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.
 Usage: ./codesend decimalcode [-p <PIN Number>] [-l <Pulse Length>]
 (Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter)
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "RCSwitch.h"

#define DEFAULT_PIN 0

void printUsage(char *argv[]) {
    printf("Usage: %s <code> [-p <PIN Number> (default: %i)] [-l <Pulse Length>].\n", argv[0], DEFAULT_PIN);
}

int main(int argc, char *argv[]) {
    int i;

    char * argumentPIN = NULL;
    char * argumentPulseLength = NULL;

    int c;
    while ((c = getopt(argc, argv, "p:l:")) != -1) {
        switch (c) {
            case 'p':
                argumentPIN = optarg;
                break;

            case 'l':
                argumentPulseLength = optarg;
                break;

            case '?':
            default:
                printUsage(argv);
                break;
            }
    }

    // This PIN is not the first PIN on the Raspberry Pi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = DEFAULT_PIN;

    if (argumentPIN != NULL) {
        PIN = atoi(argumentPIN);
    }

    /* Now set the values of "argc" and "argv" to the values after the
       options have been processed, above. */
    argc -= optind;

    if (argc == 0) {
        printUsage(argv);
        return EXIT_FAILURE;
    }

    argv += optind;

    // Parse the first parameter to this command as an integer
    int code = atoi(argv[0]);

    if (wiringPiSetup () == -1) {
        return EXIT_FAILURE;
    }

    RCSwitch mySwitch = RCSwitch();

    // Pulse length depends on the RF outlets you are using. Use RFSniffer to see what pulse length your device uses.
    if (argumentPulseLength != NULL) {
        int pulseLength = atoi(argumentPulseLength);
        mySwitch.setPulseLength(pulseLength);
        printf("Sending Code: %i. PIN: %i. Pulse Length: %i\n", code, PIN, pulseLength);    
    } else {
        printf("Sending Code: %i. PIN: %i.", code, PIN);    
    }

    mySwitch.enableTransmit(PIN);
    mySwitch.send(code, 24);

    return EXIT_SUCCESS;
}

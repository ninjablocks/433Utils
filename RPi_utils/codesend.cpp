/*
Usage: ./codesend decimalcode [protocol] [pulselength]
decimalcode - As decoded by RFSniffer
protocol    - According to rc-switch definitions
pulselength - pulselength in microseconds

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.

(Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter 
or your remote control)
*/
#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     

int main(int argc, char *argv[]) {
    
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 0;
    
    // Parse the first parameter to this command as an integer
    int protocol = 0; // A value of 0 will use rc-switch's default value
    int pulseLength = 0;
    int bitLength = 24;

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s decimalcode [protocol] [pulselength] [bitlength]\n", argv[0]);
        printf("decimalcode\t- As decoded by RFSniffer\n");
        printf("protocol\t- According to rc-switch definitions\n");
        printf("pulselength\t- pulselength in microseconds\n");
        printf("bitlength\t- bit length\n");
        return -1;
    }

    // Change protocol and pulse length accroding to parameters
    char *eptr;
    unsigned long code = strtoul(argv[1], &eptr, 10);
    if (argc >= 3) protocol = atoi(argv[2]);
    if (argc >= 4) pulseLength = atoi(argv[3]);
    if (argc >= 5) bitLength = atoi(argv[4]);
    
    if (wiringPiSetup () == -1) return 1;
    printf("sending code[%lu]\n", code);
    RCSwitch mySwitch = RCSwitch();
    if (protocol != 0) mySwitch.setProtocol(protocol);
    if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
    mySwitch.enableTransmit(PIN);
    
    mySwitch.send(code, bitLength);
    
    return 0;

}

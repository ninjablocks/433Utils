/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "../rc-switch/RCSwitch.h"

extern "C" {
	#include <unistd.h>
}

#include <stdlib.h>
#include <stdio.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
  
    /*
     output PIN is hardcoded for testing purposes
     */
    int PIN;
    // XIO-P* do not have a good enough time resolution to work properly
    if( get_gpio_number("AP-EINT3", &PIN) == -1 )
        return 2;

    if (PIN != lookup_gpio_by_name("AP-EINT3")
       && PIN != lookup_gpio_by_name("AP-EINT1")
       && PIN != lookup_gpio_by_name("I2S-MCLK") // CHIP PRO
       && PIN != lookup_gpio_by_name("I2S-DI") // CHIP PRO
       && PIN != lookup_gpio_by_name("PWM1") // CHIP PRO
       && !(PIN >= lookup_gpio_by_name("XIO-P0") && PIN <= lookup_gpio_by_name("XIO-P7"))) {
      printf("Callbacks currently available on AP-EINT1, AP-EINT3, and XIO-P0 to XIO-P7 only\n");
      return -1;
    }

    if( gpio_allowed(PIN) < 1 )
        return 3;
    gpio_unexport(PIN);
    if( gpio_export(PIN) < 0 )
        return 4;

     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);
     
    
     while(1) {
       usleep(10000);	// only check to see if we got anything every 10ms
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
   
          printf("Received %i\n", mySwitch.getReceivedValue() );
        }
    
        mySwitch.resetAvailable();
    
      }
      
  
  }

  gpio_unexport(PIN);
  exit(0);


}


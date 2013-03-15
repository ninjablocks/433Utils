
/*
  SendDemo - sends RF codes - they will be received by your Ninja Block as normal.
  
  hacked from 
  
  http://code.google.com/p/rc-switch/ by @justy
  
*/

#include <RCSwitch.h>

#define CODE_Button 4575536  // Use whatever number you saw in the RF Sniffer Sketch
    
    
#define CODE_PotLow  100000  // HEX 186A0
#define CODE_PotMid  100001  // HEX 186A1
#define CODE_PotHigh 100002  // HEX 186A2
    
#define SETTING_UsePot false  // Make this true for Step Four of the tutorial.

RCSwitch mySwitch = RCSwitch();

void setup() {
  
  // Power up the send unit by using the digital pins.
  // Plug the unit in so that:
 
  // Transmiter hack- use the following if you plan to use my easy transmitter connection hack
 
  // VCC  : 5
  // GND  : 6
  // Data : 7
  // ANT  : in between the two headers!
  
 
  // Data
  pinMode(7, OUTPUT);  // Either way, we'll use pin 7 to drive the data pin of the transmitter.
  
  //// NOTE /////
  // The next two pin assignments are only for the transmitter hack I demonstrate in the blog post / video
  // However, it doesn't hurt to leave them in even if you're not going to attach the transmitter that way.
  
  // GND
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);   // I do this first to avoid any reverse polarity

  // VCC
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(7);
  
}

void loop() {
  
      
   
      if (SETTING_UsePot) {
        
        // Send your pot's simplified state every 5 seconds
          
        int val = analogRead(0);
        delay(100);
        val = analogRead(0);
          
        // The pot should report values from 0..1023; we'll define low as < 256  
        if (val < 256) {
          mySwitch.send(CODE_PotLow, 24);
        }
        
        if (val >= 256 && val < 768) {
          mySwitch.send(CODE_PotMid, 24);
        }
        
        if (val >= 768) {
          mySwitch.send(CODE_PotHigh, 24);
        }
        
          
      } else {
        
        // Send your button's code every 5 seconds.
        mySwitch.send(CODE_Button, 24);
        delay(5000);
      
      }
  
}

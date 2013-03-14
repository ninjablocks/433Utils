
/*
  SendDemo - sends RF codes - they will be received by your Ninja Block as normal.
  
  hacked from 
  
  http://code.google.com/p/rc-switch/ by @justy
  
*/

#include <RCSwitch.h>

#define CODE_Button 500000    // Use whatever number you saw in the RF Sniffer Sketch

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
  
      // Send your button's code every 5 seconds.
      mySwitch.send(CODE_Button, 24);
      delay(5000);
  
}

/*
  Servo Receive Demo
 
 Hacked from http://code.google.com/p/rc-switch/ by @justy
 
 */

#include <Servo.h> 
#include <RCSwitch.h>

// Define some codes that will be understood by the receiver.  These should not collide with other codes!
// Practically speaking, they shouldn't collide with the codes of devices in your vicinity.

#define CODE_Up 500000      // HEX 7A120
#define CODE_Down 500001    // HEX 7A121
#define CODE_Left 500002    // HEX 7A122
#define CODE_Right 500003   // HEX 7A123
#define CODE_Home 500004    // HEX 7A124

#define ENABLE_Sniffer true


RCSwitch mySwitch = RCSwitch();  // Create an instance of RCSwitch

Servo panServo;  // create servo objects to control our servos
Servo tiltServo;

int pan = 50;
int tilt = 50;

int min_pan = 10;
int max_pan = 170;

int min_tilt = 0;
int max_tilt = 160;

int del = 500;


void setup() {
  Serial.begin(9600);
  // ********* IMPORTANT ***********
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  panServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  tiltServo.attach(3);
}

void loop() {

  if (mySwitch.available()) {

    long value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
    } 
    else {

      if (ENABLE_Sniffer) {
      Serial.print("Received ");
      Serial.print( value );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      
      }

      switch (value) {

      case CODE_Left:
        pan-=5;
        if (pan < min_pan) pan = min_pan;
        break;

      case CODE_Right:
        pan+=5;
        if (pan > max_pan) pan = max_pan;
        break;

      case CODE_Up:
        tilt-=5;
        if (tilt < min_tilt) tilt = min_tilt;
        break;

      case CODE_Down:
        tilt+=5;
        if (tilt > max_tilt) tilt = min_tilt;
        break;
        
       case CODE_Home:
        tilt=50;
        pan=50; 
        break;


      }

    }

    // Prepare for more input
    mySwitch.resetAvailable();
  }


  // Update our servos with their current values
  // This could be optimised to only do this when values have changed.
  tiltServo.write(tilt);                             
  panServo.write(pan);           
  delay(del);                     
}



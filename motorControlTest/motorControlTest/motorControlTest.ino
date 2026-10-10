#include <Servo.h>

// Setup for servo variables
Servo pinkyServo;
Servo indexServo;
Servo middleServo;
Servo ringServo;
Servo thumbServo;
Servo wristServo1;
Servo wristServo2;
Servo wristServo3;
Servo elbowServo;

// Set input pins for values from sensor board(s). All fingers are placed independently to
// future-proof to an extent, the Middle and Thumb are the only ones used for this version.
// The Middle pin controls all four fingers and the Thumb pin controls the thumb
int pinkyPin = A0; // Pin 14, A0
int ringPin = A1; // Pin 15, A1
int middlePin = A2; // Pin 16, A2
int indexPin = A3; // Pin 17, A3
int thumbPin = A4; // Pin 18, A4
int wristPin1 = A5; // Pin 19, A5
int wristPin2 = A6; // Pin 20, A6
int wristPin3 = A7; // Pin 21, A7
int bicepPin = A8; // Pin 22, A8
int tricepPin = A9; // Pin 23, A9
int handAngleDefault = 0; // Default angle for finger servos, in degrees (placeholder)
int elbowAngleDefault = 0; // Default angle for elbow servo, in degrees (placeholder)
int wristAngleDefault = 90; // Default speed for wrist servos (90 is motionless, range of 0-180)

// Create variables for input pin values
int pinkyValue;
int ringValue;
int middleValue;
int indexValue;
int thumbValue;
int wristValue1;
int wristValue2;
int wristValue3;
int bicepValue;
int tricepValue;

void setup() {
  // Set the pins to be used for each servo, based on Teensy 4.1 pinout
  pinkyServo.attach(0);
  ringServo.attach(1);
  middleServo.attach(2);
  indexServo.attach(3);
  thumbServo.attach(4);
  wristServo1.attach(5);
  wristServo2.attach(6);
  wristServo3.attach(7);
  elbowServo.attach(8);

  // Set servos to their default value on startup
  pinkyServo.write(handAngleDefault);
  ringServo.write(handAngleDefault);
  middleServo.write(handAngleDefault);
  indexServo.write(handAngleDefault);
  thumbServo.write(handAngleDefault);
  elbowServo.write(elbowAngleDefault);
  // More math will need to be done to "center" the wrist, may not actually be possible
  // without persistent storage. The wrist servos are continuous so thye don't have a built-in
  // "default" position/angle like the finger servos. This is essentially telling them to not move
  // as the startup code.
  wristServo1.write(wristAngleDefault);
  wristServo2.write(wristAngleDefault);
  wristServo3.write(wristAngleDefault);

  delay(2000); // Allow everything to reach its starting point before code execution
}

void loop() {
  // Begin the test sequence, going through each individual part of the arm and displaying
  // the different functions
  // Elbow movement code
  elbowServo.write(70);
  delay(1000);
  elbowServo.write(1);
  delay(1000);
  // End elbow movement
  // Wrist movement code here, once I figure out the math
  delay(1000);
  // End wrist movement
  // Hand movement code
  pinkyServo.write(90);
  delay(200);
  ringServo.write(90);
  delay(200);
  middleServo.write(90);
  delay(200);
  indexServo.write(90);
  delay(200);
  thumbServo.write(90);
  delay(1000);
  thumbServo.write(0);
  delay(200);
  indexServo.write(0);
  delay(200);
  middleServo.write(0);
  delay(200);
  ringServo.write(0);
  delay(200);
  pinkyServo.write(0);
  delay(200);
  // End hand movement
  delay(2000); // Delay before the loop restarts
}

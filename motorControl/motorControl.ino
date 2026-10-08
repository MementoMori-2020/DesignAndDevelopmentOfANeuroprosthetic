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

// Threshold variables to determine servo position for fingers. Above the threshold results in 
//fully closed, below is fully open. Only Middle and Thumb are used for now.
//int pinkyThreshold;
//int ringThreshold;
int middleThreshold;
//int indexThreshold;
int thumbThreshold;

// The elbow is based on whether or not the signal from the bicep/tricep are active. Each has a threshold, and
// both or neither being active results in no elbow movement.
int bicepThreshold;
int tricepThreshold;

// The wrist is based on three independent values for the three wheels, each determining how fast the wheel should
// spin and in what direction. Not implemented for real control yet.
//int wristThreshold1;
//int wristThreshold2;
//int wristThreshold3;

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
  //pinkyServo.write(handAngleDefault);
  //ringServo.write(handAngleDefault);
  middleServo.write(handAngleDefault);
  //indexServo.write(handAngleDefault);
  thumbServo.write(handAngleDefault);
  elbowServo.write(elbowAngleDefault);
  // More math will need to be done to "center" the wrist, may not actually be possible
  // without persistent storage. The wrist servos are continuous so thye don't have a built-in
  // "default" position/angle like the finger servos. This is essentially telling them to not move
  // as the startup code.
  //wristServo1.write(wristAngleDefault);
  //wristServo2.write(wristAngleDefault);
  //wristServo3.write(wristAngleDefault);
}

void loop() {
  // Update the values for each input pin
  //pinkyValue = analogRead(pinkyPin);
  //ringValue = analogRead(ringPin);
  middleValue = analogRead(middlePin);
  //indexValue = analogRead(indexPin);
  thumbValue = analogRead(thumbPin);
  //wristValue1 = analogRead(wristPin1);
  //wristValue2 = analogRead(wristPin2);
  //wristValue3 = analogRead(wristPin3);
  bicepValue = analogRead(bicepPin);
  tricepValue = analogRead(tricepPin);

  // Set the values for each servo based on the input value. Each needs a certain threshold set based on what
  // the actual input is for that pin. Currently setting the elbow, thumb, and middle servos.

  // Current servo setting is overly simplified, actual setting should be based on an analog signal, higher
  // signal means more curling, to allow for greater control. Elbow especially would benefit from this, where a 
  // more tensed muscle equals more movement in that direction.

  // Thumb servo setting
  if (thumbValue > thumbThreshold) {
    thumbServo.write(180);
  } else {
    thumbServo.write(0);
  }

  // Middle servo setting
  if (middleValue > middleThreshold) {
    middleServo.write(180);
  } else {
    middleServo.write(0);
  }

  // Elbow servo setting. Slightly more complex than fingers due to bicep/tricep checks.
  // Elbow is set as curled with bicep, extended with tricep, and halfway with both/neither.
  if (bicepValue > bicepThreshold && tricepValue < tricepThreshold) {
    elbowServo.write(180);
  } else if (bicepValue < bicepThreshold && tricepValue > tricepThreshold) {
    elbowServo.write(0);
  } else {
    elbowServo.write(90);
  }
}

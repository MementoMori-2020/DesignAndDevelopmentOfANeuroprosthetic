#include <PCA9685.h>
// #include <EEPROM.h>
// int eepromAddress = 0; // Set the default address for the eeprom to 0
// int wristMemStart = 0;

// Setup for servo channels on PCA9685
int pinkyServo = 0;
int ringServo = 1;
int middleServo = 2;
int indexServo = 3;
int thumbServo = 4;
int wristServo1 = 5;
int wristServo2 = 6;
int wristServo3 = 7;
int elbowServo = 8;

PCA9685 pwmController(Wire); // Set up the servo driver interface
PCA9685_ServoEval pwmServoSG90(102, 307, 512);
PCA9685_ServoEval pwmServoHV(102, 307, 512);
PCA9685_ServoEval pwmServoHS422(102, 307, 512);

int handAngleDefault = -90; // Default angle for finger servos, in degrees (-90 to +90)
int elbowAngleDefault = -90; // Default angle for elbow servo, in degrees (-90 to +90)
int wristSpeedDefault = 0; // Default speed for wrist servos (0 is motionless, range of -90 to 90)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // Start communication with the servo driver
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  Wire.begin();                      // Start up the Wire communication
  pwmController.resetDevices();       // Reset devices on i2c lines to clean slate
  pwmController.init();               // Initializes module with default settings from library
  pwmController.setPWMFrequency(200);
  pwmController.setPWMFreqServo();    // Sets servo frequency to 50Hz, which is the standard 20ms phase

  // Set servos to their correct value
  pwmController.setChannelsPWM(0, 5, pwmServoSG90.pwmForAngle(-90));
  pwmController.setChannelsPWM(5, 3, pwmServoHV.pwmForAngle(0));
  pwmController.setChannelPWM(8, pwmServoHS422.pwmForAngle(-90));
  delay(2000);
  
  // More math will need to be done to "center" the wrist, may not actually be possible
  // without persistent storage. The wrist servos are continuous so they don't have a built-in
  // "default" position/angle like the finger servos. This is just telling them to not move
  // as the startup code.
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  // Begin the test sequence, going through each individual part of the arm and displaying
  // the different functions
  // Elbow movement code
  pwmController.setChannelPWM(8, pwmServoHS422.pwmForAngle(-20));
  delay(1000);
  pwmController.setChannelPWM(8, pwmServoHS422.pwmForAngle(-90));
  delay(1000);
  // End elbow movement
  // Wrist movement code here, once I figure out the math
  // Just rotation for now, go one direction for 1 second, then the other for 1 second, then stop
  // For now 1 at a time to confirm they all work, once better power source is found can move more at once (too much current)
  pwmController.setChannelPWM(5, pwmServoHV.pwmForSpeed(90));
  delay(500);
  pwmController.setChannelPWM(5, pwmServoHV.pwmForSpeed(-90));
  delay(500);
  pwmController.setChannelPWM(5, 0);
  delay(200);
  pwmController.setChannelPWM(6, pwmServoHV.pwmForSpeed(90));
  delay(500);
  pwmController.setChannelPWM(6, pwmServoHV.pwmForSpeed(-90));
  delay(500);
  pwmController.setChannelPWM(6, 0);
  delay(200);
  pwmController.setChannelPWM(7, pwmServoHV.pwmForSpeed(90));
  delay(500);
  pwmController.setChannelPWM(7, pwmServoHV.pwmForSpeed(-90));
  delay(500);
  pwmController.setChannelPWM(7, 0);
  delay(1000);
  // Update wrist position values, requires position-readable wrist servos
  //eepromAddress = 0;
  //EEPROM.update(eepromAddress, position1);
  //eepromAddres += sizeof(position1);
  //EEPROM.update(eepromAddress, position2);
  //eepromAddres += sizeof(position2);
  //EEPROM.update(eepromAddress, position3);
  // End wrist movement
  // Hand movement code, slight delay between each finger moving to have a "smooth" motion
  pwmController.setChannelPWM(0, pwmServoSG90.pwmForAngle(90));
  delay(150);
  pwmController.setChannelPWM(1, pwmServoSG90.pwmForAngle(90));
  delay(150);
  pwmController.setChannelPWM(2, pwmServoSG90.pwmForAngle(90));
  delay(150);
  pwmController.setChannelPWM(3, pwmServoSG90.pwmForAngle(90));
  delay(150);
  pwmController.setChannelPWM(4, pwmServoSG90.pwmForAngle(90));
  delay(1000);
  pwmController.setChannelPWM(4, pwmServoSG90.pwmForAngle(0));
  delay(150);
  pwmController.setChannelPWM(3, pwmServoSG90.pwmForAngle(0));
  delay(150);
  pwmController.setChannelPWM(2, pwmServoSG90.pwmForAngle(0));
  delay(150);
  pwmController.setChannelPWM(1, pwmServoSG90.pwmForAngle(0));
  delay(150);
  pwmController.setChannelPWM(0, pwmServoSG90.pwmForAngle(0));
  // delay(200);
  // End hand movement
  delay(2000); // Delay before the loop restarts
}

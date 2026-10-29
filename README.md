# Design and Development of a Neuroprosthetic
The repository for my Master's Project code. This is C++ code, used with Arduino IDE intended for a Teensy 4.1 board. To adjust the code for a different Arduino-compatible board, just adjust the pins assigned to the SDA/SDL used for I2C communication with the PCA9865 Adafruit board, which then controls the servos themselves.

This repo contains a .ino file with test code for the servos that ensures they all work as intended, and the PCA9865 is functioning properly. One of the 3.3V pins from the Teensy should be used to power the PCA board, and the servo power should be 6V with at least 10A of current draw possible in order to ensure that all the servos can move at the same time if needed. This file is also used to ensure that the prosthetic arm has the full intended movement range.

A separate .ino file exists which is for the actual live testing of the arm, and uses the analog input pins on the Teensy in order to receive input signals from the PCBs used for initial signal processing of EMG and EEG signals. The schematics for both of these boards are included in this repo as well.

The teensy.exe file is used to allow the Teensy to be programmed via direct file upload, and is included here for the sake of posterity.

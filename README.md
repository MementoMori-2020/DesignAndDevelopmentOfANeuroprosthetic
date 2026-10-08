# MastersProjectCode
The repository for my Master's Project code. This is C++ code, used with Arduino IDE intended for a Teensy 4.1 board. To adjust the code for a different Arduino-compatible board, just adjust the pins assigned to the servos/inputs. This code is intended to control version 2 of
an experimental neuroprosthetic arm.

This repo contains a .ino file with test code for the servos that ensures they all work and all relevant pins on the Teensy are transmitting properly.
This file is also used to ensure that the prosthetic arm has the full intended movement range.

A separate .ino file exists which is for the actual live testing of the arm, and takes the analog input pins into account for the control of
the servos.

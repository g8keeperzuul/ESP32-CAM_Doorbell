#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

//#define DISABLE_SERIAL_OUTPUT 1

// https://arduino.stackexchange.com/questions/9857/can-i-make-the-arduino-ignore-serial-print
#ifdef DISABLE_SERIAL_OUTPUT
#define Sprintln(x)
#define Sprint(x)
#define SprintlnHEX(x)
#else
#define Sprintln(x) (Serial.println(x))
#define Sprint(x) (Serial.print(x))
#define SprintlnHEX(x) (Serial.println(x, 16))
#endif

#endif
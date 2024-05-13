#ifndef __MAIN_H_INCLUDE
#define __MAIN_H_INCLUDE

#include "SHT31.h"
#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define ON_PIN 2
#define OFF_PIN 3

#define LINE_LENGTH 20

#define MIN_TEMP 21.5
#define MAX_TEMP 23
#define WIRE_CLOCK 100000

void clear_line(uint8_t line_number);
void turn_heater_on();
void turn_heater_off();
void press_button(uint8_t pin);

#endif
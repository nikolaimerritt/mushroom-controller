#ifndef __MAIN_H_INCLUDE
#define __MAIN_H_INCLUDE

#include "SHT31.h"
#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define ON_PIN 2
#define OFF_PIN 3

#define LINE_LENGTH 20

#define MIN_TEMP 22
#define MAX_TEMP 23
#define WIRE_CLOCK 100000

#define ONE_HOUR_MS 3600000
#define MEASUREMENT_INTERVAL_MS 7000

void print_measurements();
void toggle_heater();

void(* reset_arduino) (void) = 0;

void clear_line(uint8_t line_number);
void turn_heater_on();
void turn_heater_off();
void press_button(uint8_t pin);


#endif
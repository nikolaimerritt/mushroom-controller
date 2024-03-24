#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
#include "SHT31.h"

#define on_pin 2
#define off_pin 3

bool is_fan_on = false;

#define min_humidity 60
#define max_humidity 68

SCD4x co2Sensor;
#define line_length 20
LiquidCrystal_I2C lcd(0x27, 20, 4); 
SHT31 sht;

void clearLine(uint8_t lineNumber) {
  for (uint8_t c = 0; c < line_length; c++) {
    lcd.setCursor(c, lineNumber);
    lcd.write(' ');
  }
  lcd.setCursor(0, lineNumber);
}


void PressButton(uint8_t pin)
{
  digitalWrite(pin, LOW);
  delay(100);
  digitalWrite(pin, HIGH);
  delay(1000);
}

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();

  Wire.begin();
  Wire.setClock(100000);

  sht.begin();

  co2Sensor.begin();

  clearLine(0);
  lcd.print("Fartuino 1660 Ti v2");

  digitalWrite(on_pin, HIGH);
  digitalWrite(off_pin, HIGH);

  pinMode(on_pin, OUTPUT);
  pinMode(off_pin, OUTPUT);

  PressButton(off_pin);

}




void loop()
{
  if (co2Sensor.readMeasurement()) // readMeasurement will return true when fresh data is available
  {
    uint16_t const co2 = co2Sensor.getCO2();    
    clearLine(3);
    lcd.print("CO2: ");
    lcd.print(co2);
    lcd.print(" PPM");
  }
  sht.read(false);

  clearLine(2);
  lcd.print("Temp: ");
  float temp = sht.getTemperature();
  lcd.print(temp);
  lcd.write('C');


  clearLine(1);
  lcd.print("Humidity: ");
  float humidity = sht.getHumidity();
  lcd.print(humidity);
  lcd.write('%');

  if (humidity > max_humidity && !is_fan_on) {
      PressButton(on_pin);
      is_fan_on = true;
  } else if (humidity < min_humidity && is_fan_on) {
    PressButton(off_pin);
    is_fan_on = false;
  }

  delay(300);
}

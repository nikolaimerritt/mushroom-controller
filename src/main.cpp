#include "main.h"

SCD4x co2_sensor;
LiquidCrystal_I2C lcd(0x27, 20, 4);
SHT31 temp_humidity_sensor;
bool is_heater_on = true;

void setup() {
    lcd.init();
    lcd.backlight();

    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    temp_humidity_sensor.begin();

    co2_sensor.begin();

    clearLine(0);
    lcd.print("Fartuino 1660 Ti v4");

    digitalWrite(ON_PIN, HIGH);
    digitalWrite(OFF_PIN, HIGH);

    pinMode(ON_PIN, OUTPUT);
    pinMode(OFF_PIN, OUTPUT);

    PressButton(ON_PIN);
    delay(1000);
}

void loop() {
    temp_humidity_sensor.read(false);
    float const temperature = temp_humidity_sensor.getTemperature();
    float const humidity = temp_humidity_sensor.getHumidity();

    clearLine(1);
    lcd.print("Humidity:  ");
    lcd.print(humidity);
    lcd.write('%');

    clearLine(2);
    lcd.print("Temp:      ");
    lcd.print(temperature);
    lcd.print(" C");

    if (co2_sensor.readMeasurement()) {
        uint16_t const co2 = co2_sensor.getCO2();
        clearLine(3);
        lcd.print("CO2:       ");
        lcd.print(co2);
        lcd.print(" PPM");
    }

    if (temperature > MAX_TEMP && is_heater_on) {
        PressButton(OFF_PIN);
        is_heater_on = false;
    } else if (temperature < MIN_TEMP && !is_heater_on) {
        PressButton(ON_PIN);
        is_heater_on = true;
    }

    delay(5000);
}

void clearLine(uint8_t line_number) {
    for (uint8_t c = 0; c < LINE_LENGTH; c++) {
        lcd.setCursor(c, line_number);
        lcd.write(' ');
    }
    lcd.setCursor(0, line_number);
}

void PressButton(uint8_t pin) {
    digitalWrite(pin, LOW);
    delay(500);
    digitalWrite(pin, HIGH);
}
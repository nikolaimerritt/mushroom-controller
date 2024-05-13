#include "main.h"

SCD4x co2_sensor;
LiquidCrystal_I2C lcd(0x27, 20, 4);
SHT31 temp_humidity_sensor;
bool is_heater_on;

void setup() {
    lcd.init();
    lcd.backlight();

    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    temp_humidity_sensor.begin();

    co2_sensor.begin();

    clear_line(0);
    lcd.print("Fartuino 1660 Ti v5");

    digitalWrite(ON_PIN, HIGH);
    digitalWrite(OFF_PIN, HIGH);

    pinMode(ON_PIN, OUTPUT);
    pinMode(OFF_PIN, OUTPUT);

    turn_heater_on();
    delay(1000);
}

void loop() {
    temp_humidity_sensor.read(false);
    float const temperature = temp_humidity_sensor.getTemperature();
    float const humidity = temp_humidity_sensor.getHumidity();

    clear_line(1);
    lcd.print("Humidity:  ");
    lcd.print(humidity);
    lcd.write('%');

    clear_line(2);
    lcd.print("Temp:      ");
    lcd.print(temperature);
    lcd.print(" C");

    if (co2_sensor.readMeasurement()) {
        uint16_t const co2 = co2_sensor.getCO2();
        clear_line(3);
        lcd.print("CO2:       ");
        lcd.print(co2);
        lcd.print(" PPM");
    }

    if (temperature > MAX_TEMP && is_heater_on) {
        turn_heater_off();
    } else if (temperature < MIN_TEMP && !is_heater_on) {
        turn_heater_on();
    }

    delay(5000);
}

void clear_line(uint8_t line_number) {
    for (uint8_t c = 0; c < LINE_LENGTH; c++) {
        lcd.setCursor(c, line_number);
        lcd.write(' ');
    }
    lcd.setCursor(0, line_number);
}

void turn_heater_on() {
    press_button(ON_PIN);
    is_heater_on = true;
}

void turn_heater_off() {
    press_button(OFF_PIN);
    is_heater_on = false;
}

void press_button(uint8_t pin) {
    digitalWrite(pin, LOW);
    delay(500);
    digitalWrite(pin, HIGH);
}
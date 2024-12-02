
#include "DHT.h"
#define DHTPIN 9
#define DHTTYPE DHT11
#include <LiquidCrystal.h>


DHT dht(DHTPIN, DHTTYPE);
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600);
  dht.begin(); // initialize the sensor
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

  // Clears the LCD screen
	lcd.clear();
}

void loop() {
  // wait a few seconds between measurements.
  delay(5000);

  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();

  // stores humidty level quality
  String hum_lvl = "ideal";
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  
  else {
    // humidity too low
    if (humi < 30) {hum_lvl = " too low";}

    // humidity ideal
    else if (humi >= 30 && humi <= 50) {hum_lvl = "ideal";}

    // humidity good
    else if (humi > 50  && humi <= 60) {hum_lvl = "good";}

    // humidity satisfactory
    else if (humi > 60  && humi <= 70) {hum_lvl = "satisfactory";}

    // humidity too high
    else if (humi > 70) {hum_lvl = "too high";}

    // serial printing
    Serial.print("Humidity: " + String(humi) + "%");
    Serial.println(); 
    Serial.print("Temperature: " + String(tempC) + "°C");

    // LCD screen printing
    lcd.setCursor(0, 0);
    lcd.print("Humidity: " + String(humi) + "%" + " | Humidity Level: " + hum_lvl);
    lcd.setCursor(0, 1);
    lcd.print("Temperature: " + String(tempC) + "°C");
  }
}
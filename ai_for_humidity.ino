#include <ArduinoJson.h>

#define SOIL_HUMIDITY_SENSOR_PIN A0
#define RELAY_PIN 7

int soilHumidityRaw;
int temperature = 34; // Set a fixed temperature or use a sensor if available

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  // Read raw value from soil humidity sensor
  soilHumidityRaw = analogRead(SOIL_HUMIDITY_SENSOR_PIN);

  // Map raw values to percentage
  int soilHumidityPercentage = map(soilHumidityRaw, 0, 1023, 0, 100);

  // Create a JSON object
  StaticJsonDocument<200> doc;
  doc["Soil Humidity Percentage"] = soilHumidityPercentage;
  doc["Temperature (°C)"] = temperature;

  // Serialize JSON to string and send
  String output;
  serializeJson(doc, output);
  Serial.println(output);

  // Control the relay based on soil humidity percentage
  if (soilHumidityPercentage < 70) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the pump
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the pump
  }
  
  delay(5000); // Wait 5 seconds before next reading
}

// Pin definitions
const int soilHumidityPin = A0; // Define the pin for soil humidity sensor (analog pin A0)
const int relayPin = 7;        // Define the pin for the relay module (digital pin 7)

// Variables for sensor readings
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read soil humidity sensor value
  int soilHumidityValue = analogRead(soilHumidityPin);

  // Simulate reading temperature and humidity (replace with actual readings)
  temperature = 25.0;  // Replace with actual temperature reading
  humidity = 50.0;     // Replace with actual humidity reading

  // Send data to Python script
  Serial.print("SoilHumidity:");
  Serial.print(soilHumidityValue);
  Serial.print(",");
  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print("Humidity:");
  Serial.println(humidity);

  // Check if there's data available from Python script
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Control the relay based on command
    if (command == '1') {
      if (digitalRead(relayPin) == LOW) {  // Only write HIGH if the relay is currently LOW
        digitalWrite(relayPin, HIGH); // Turn on relay
      }
    } else if (command == '0') {
      if (digitalRead(relayPin) == HIGH) {  // Only write LOW if the relay is currently HIGH
        digitalWrite(relayPin, LOW); // Turn off relay
      }
    }
  }

  // Non-blocking delay
  static unsigned long previousMillis = 0;
  const long interval = 100;  // Short interval for relay check (adjust as needed)

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Perform tasks or updates here
  }
}

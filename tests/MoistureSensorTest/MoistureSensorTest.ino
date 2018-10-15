/**
 * MoistureSensorTest.ino
 * Run this code to test the setup of the moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */

// Initialize globals.
const int DELAY_SECONDS = 1; // Time between each read of the sensor in seconds
const int AIR_VALUE = 1000;  // Replace this value with sensor reading of air
const int WATER_VALUE = 200; // Replace this value with sensor reading of water
const int INTERVAL = 200;    // Replace this with (AIR_VALUE - WATER_VALUE)/4
const int DEBUG = 0;         // Set this to 1 to call get_moisture_level()

/**
 * One time setup; opens serial port and sets baud rate to 9600.
 */
void setup() {
  Serial.begin(9600);
}

/**
 * Sets a string encoding moisture level: This provides a range that the humidity falls into.
 */
void get_moisture_level(int moisture_val, String &moisture_level) {
  switch (moisture_val) {
    case (WATER_VALUE - 100) ... WATER_VALUE:
      moisture_level = "Humidity: 100%";
      break;
    case (WATER_VALUE + 1) ... (WATER_VALUE + INTERVAL):
      moisture_level = "Humidity: >75%";
      break;
    case (WATER_VALUE + INTERVAL + 1) ... (WATER_VALUE + 2 * INTERVAL):
      moisture_level = "Humidity: >50%";
      break;
    case (WATER_VALUE + 2 * INTERVAL + 1) ... (WATER_VALUE + 3 * INTERVAL):
      moisture_level = "Humidity: >25%";
      break;
    case (WATER_VALUE + 3 * INTERVAL + 1) ... AIR_VALUE:
      moisture_level = "Humidity: >0%";
      break;
    default: // Humididty level of soil is less than humidity in air
      moisture_level = "Humidity: 0%";
      break;
  }
}

/**
 * Get moisture as a percentage value.
 */
int moisture_percentage(int moisture_val) {
  int moisture_range = AIR_VALUE - WATER_VALUE;
  return ((moisture_val - WATER_VALUE) * 100) / moisture_range;
}

/**
 * Sets a string encoding the moisture level: This provides an exact percentage.
 * The sensor may drift, so this percentage can appear to "float" around.
 */
void get_moisture_percentage(int moisture_val, String &moisture_level) {
  int moisture_pcent_val = moisture_percentage(moisture_val);
  moisture_level = "Humididty: " + String(moisture_pcent_val) + "%";
}

/**
 * Print the exact sensor value.
 */
void print_sensor_value(int moisture_val) {
  Serial.print("Moisture Sensor Value:\t"); Serial.println(moisture_val);
}

/**
 * Main loop.
 */
void loop() {
  int moisture_val;
  moisture_val = analogRead(0); // connect sensor to Analog 0
  print_sensor_value(moisture_val);
  if (DEBUG) {
    String moisture_level;
    get_moisture_level(moisture_val, moisture_level);
    Serial.println(moisture_level);
  }
  delay(DELAY_SECONDS * 1000);
}

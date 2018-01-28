/**
 * MoistureSensorTest.ino
 * Run this code to test the setup of the moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */


/**
 * Perform one time setup, opening serial port.
 */
void setup() {
  Serial.begin(9600); // set the baud rate to 9600
}

// Initialize globals.
int DELAY_SECONDS = 1; // time between each read of the sensor in seconds
int AIR_VALUE = 1000; // Replace this value with sensor reading of air
int WATER_VALUE = 200; // Replace this value with sensor reading of water
int INTERVAL = 200; // Replace this with (AIR_VALUE - WATER_VALUE)/4
int DEBUG = 0; // Set this to 1 to call get_moisture_level()

/**
 * Sets a string encoding moisture level.
 * This function was inspired by the test code here:
 * https://www.dfrobot.com/wiki/index.php/Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 */
void get_moisture_level(int moisture_val, String &moisture_level) {
  if (moisture_val <= WATER_VALUE) {
    moisture_level = "Humidity: 100%";
  } else if (moisture_val <= (WATER_VALUE + INTERVAL)) {
    moisture_level = "Humidity: >75%";
  } else if (moisture_val <= (WATER_VALUE + 2*INTERVAL)) {
    moisture_level = "Humidity: >50%";
  } else if (moisture_val <= (WATER_VALUE + 3*INTERVAL)) {
    moisture_level = "Humidity: >25%";
  } else if (moisture_val <= (AIR_VALUE)) {
    moisture_level = "Humidity: >0%";
  } else {
    moisture_level = "Humidity: 0%";
  }
}

/**
 * Print sensor value.
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

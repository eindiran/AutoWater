/**
 * AutoWater.ino
 * Automate watering a plant using a solenoid valve
 * and a moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */

// Initialize globals.
int DEBUG = 1;
int DELAY_SECONDS = 5; // time between moisture checks
int AIR_VALUE = 1000; // Replace this value with sensor reading of air
int WATER_VALUE = 200; // Replace this value with sensor reading of water
int INTERVAL = 200; // Replace this with (AIR_VALUE - WATER_VALUE)/4
int DRYNESS_THRESHOLD = 425;
int SOLENOID_PIN = 4;
int WATER_TIME_MS = 450; // time to open SV in ms

/**
 * One-time setup.
 */
void setup() {
  Serial.begin(9600); // set the baud rate
  pinMode(SOLENOID_PIN, OUTPUT); // Prep the SV's pin.
}

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
 * Puts a normally-closed solenoid valve into its open
 * state for num_seconds, then closes it.
 */
void nc_turn_solenoid(int num_seconds) {
  int num_ms = num_seconds * 1000;
  if (DEBUG) {
    // Poor-man's printf
    Serial.print("Opening solenoid valve for "); Serial.println(num_seconds);
  }
  digitalWrite(SOLENOID_PIN, HIGH); // Switched magnet on; open
  delay(num_ms);
  digitalWrite(SOLENOID_PIN, LOW); // Switched magnet off; closed
  if (DEBUG) {
    Serial.println("Solenoid valve closed.");
  }
}

/**
 * Water our plant based on the moisture sensor reading.
 */
void water_plant(int moisture_val) {
  if (moisture_val > DRYNESS_THRESHOLD) {
    if (DEBUG) {
      Serial.println("Moisture beneath threshold: watering plant.");
    }
    nc_turn_solenoid(WATER_TIME_MS);
  } else if (DEBUG) {
    Serial.println("Moisture level above threshold: not watering plant.");
  }
}

/**
 * Print sensor value.
 */
void print_sensor_value(int val) {
  Serial.print("Moisture Sensor Value:\t"); Serial.println(val);
}

/**
 * Main loop.
 */
void loop() {
  int moisture_val; // reading from moisture sensor
  moisture_val = analogRead(0); // connect sensor to Analog 0
  print_sensor_value(moisture_val);
  if (DEBUG) {
    // if DEBUG != 0 print human-readable moisture level
    String moisture_level;
    get_moisture_level(moisture_val, moisture_level);
    Serial.println(moisture_level);
  }
  if (DEBUG == 2) {
    // if DEBUG == 2, check sensor w/o watering
    delay(DELAY_SECONDS * 1000);
    return;
  }
  water_plant(moisture_val);
  delay(DELAY_SECONDS * 1000);
}


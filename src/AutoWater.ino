/**
 * AutoWater.ino
 * Automate watering a plant using a solenoid valve
 * and a moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */

// Initialize globals.
int DEBUG = 1;
int DELAY_SECONDS = 15; // time between moisture checks
int DRYNESS_THRESHOLD = 425;
int SOLENOID_PIN = 4;
int WATER_TIME = 4; // time to open SV in seconds

/**
 * One-time setup.
 */
void setup() {
  Serial.begin(9600); // set the baud rate
  pinMode(SOLENOID_PIN, OUTPUT); // Prep the SV's pin.
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
    nc_turn_solenoid(WATER_TIME);
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
  if (DEBUG) {
    print_sensor_value(moisture_val);
    if (DEBUG > 1) {
      // if DEBUG > 1, check sensor w/o watering
      delay(DELAY_SECONDS * 1000);
      return;
    }
  }
  water_plant(moisture_val);
  delay(DELAY_SECONDS * 1000);
}


/**
 * AutoWater.ino
 * Automate watering a plant using a solenoid valve
 * and a moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */

/** Initialize globals */
const int DELAY_SECONDS = 5;   // Time between moisture checks
const int AIR_VALUE = 1000;    // Replace this value with sensor reading of air
const int WATER_VALUE = 200;   // Replace this value with sensor reading of water
const int INTERVAL = 200;      // Replace this with (AIR_VALUE - WATER_VALUE)/4
const int DRY_THRESH = 425;    // The moisture value beneath which you water
const int SOLENOID_PIN = 7;    // Arduino pin tied to the SV
const int WATER_TIME_MS = 450; // Time to open the SV in ms
const int DEBUG = 1;           // 0,1,2 toggle verboseness off-low-high
                               // 3 and > turn off watering, but preserve verboseness

/**
 * setup() --> One-time setup tasks go here.
 * Opening up the serial port, set the baud rate to 9600 and prep the SV's pin.
 */
void setup() {
  Serial.begin(9600);
  pinMode(SOLENOID_PIN, OUTPUT);
}

/**
 * get_moisture_level() --> Sets a string encoding moisture level.
 * Uses ranges / buckets to define moisture level. These buckets
 * allow you to determine to a coarse degree how moist it is.
 */
void get_moisture_level(int moisture_val, String &moisture_level) {
  switch (moisture_val) {
    // This special form of `case` syntax is supported by gcc and therefore by Arduino
    // It allows you to specify a range; `case A ... B` is true whenever the value being
    // switched on is between A and B.
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
 * moisture_percentage() --> Returns an int representing the humidity
 * percentage. It is calculated based on the range of the baseline values
 * for AIR_VALUE and WATER_VALUE.
 */
int moisture_percentage(int moisture_val) {
  int moisture_range = AIR_VALUE - WATER_VALUE;
  return ((moisture_val - WATER_VALUE) * 100) / moisture_range;
}

/**
 * get_moisture_percentage() -->  sets a string encoding the moisture level 
 * as an exact percentage. The sensor may drift, so this percentage can appear to
 * "float" around.
 */
void get_moisture_percentage(int moisture_val, String &moisture_level) {
  int moisture_pcent_val = moisture_percentage(moisture_val);
  moisture_level = "Humididty: " + String(moisture_pcent_val) + "%";
}

/**
 * nc_turn_solenoid() --> Puts a normally-closed solenoid valve
 * into its open state for num_seconds, then closes it.
 */
void nc_turn_solenoid(int num_seconds) {
  int num_ms = num_seconds * 1000;
  if (DEBUG) {
    Serial.print("Opening solenoid valve for "); Serial.println(num_seconds);
  }
  digitalWrite(SOLENOID_PIN, HIGH); // Switched magnet on; open
  delay(num_ms);
  digitalWrite(SOLENOID_PIN, LOW);  // Switched magnet off; closed
  if (DEBUG) {
    Serial.println("Solenoid valve closed.");
  }
}

/**
 * water_plant() --> Water the plant based on the moisture sensor readings.
 */
void water_plant(int moisture_val) {
  if (moisture_val > DRY_THRESH) {
    if (DEBUG) {
      Serial.println("Moisture beneath threshold: watering plant.");
    }
    nc_turn_solenoid(WATER_TIME_MS);
  } else if (DEBUG) {
    Serial.println("Moisture level above threshold: not watering plant.");
  }
}

/**
 * print_sensor_value() --> Print the exact sensor value. Takes a single
 * int as input.
 */
void print_sensor_value(int val) {
  Serial.print("Moisture Sensor Value:\t"); Serial.println(val);
}

/**
 * loop() --> Main loop of the program.
 * (1) Read moisture sensor.
 * (2) Print out information about the sensor if necessary.
 * (3) If the moisture level is beneath the dryness threshold,
 *     we now try watering the plant via water_plant().
 * (3) Wait a reasonable period of time before checking the sensor
 *     again.
 */
void loop() {
  int moisture_val;             // reading from moisture sensor
  moisture_val = analogRead(0); // connect sensor to Analog 0
  print_sensor_value(moisture_val);
  if (DEBUG == 1) {
    // Print human-readable moisture levels, as buckets
    String moisture_level;
    get_moisture_level(moisture_val, moisture_level);
    Serial.println(moisture_level);
  } else if (DEBUG > 1) {
    // Print human-readable moisture levels, as percentages
    String moisture_level;
    get_moisture_percentage(moisture_val, moisture_level);
    Serial.println(moisture_level);
  } else if (DEBUG > 2) {
    // Check sensor, without actually activating the SV
    delay(DELAY_SECONDS * 1000);
    return;
  }
  // If your DEBUG was > 2, you expect to skip this step.
  water_plant(moisture_val);
  delay(DELAY_SECONDS * 1000);
}

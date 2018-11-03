/**
 * MoistureSensorTest.ino
 * Run this code to test the setup of the moisture sensor.
 * Author: eindiran <eindiran@uchicago.edu>
 */

/** Initialize globals */
const int DELAY_SECONDS = 1; // Time between each read of the sensor in seconds
const int AIR_VALUE = 1000;  // Replace this value with sensor reading of air
const int WATER_VALUE = 200; // Replace this value with sensor reading of water
const int INTERVAL = 200;    // Replace this with (AIR_VALUE - WATER_VALUE)/4
const int DEBUG = 2;         // Set this to 1 to call get_moisture_level()
                             // Set it to 0 to not print info re: moisture level

/**
 * setup() --> One time setup; opens serial port and sets baud rate to 9600.
 */
void setup() {
  Serial.begin(9600);
}

/**
 * get_moisture_level() --> Sets a string encoding moisture level as a bucketed range.
 * These buckets allow you determine to coarse degree how moist it is and are expressed
 * as a quartile of the range.
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
 * print_sensor_value() --> Print the exact sensor value. Takes a single
 * int as input.
 */
void print_sensor_value(int moisture_val) {
  Serial.print("Moisture Sensor Value:\t"); Serial.println(moisture_val);
}

/**
 * loop() --> Main loop of the program.
 * (1) Read the moisture sensor.
 * (2) Either report the moisture level as a bucketed range or as a percentage.
 * (3) Wait a reasonable period before checking the sensor again.
 *
 * The behavior of the program wrt the DEBUG global variable is listed below:
 *     if DEBUG == 0, don't report anything
 *     elif DEBUG == 1, use buckets to report humidity
 *     elif DEBUG > 1, use percentages instead
 */
void loop() {
  int moisture_val;
  moisture_val = analogRead(0); // connect sensor to Analog 0
  print_sensor_value(moisture_val);
  if (DEBUG == 1) {
    String moisture_level;
    get_moisture_level(moisture_val, moisture_level);
    Serial.println(moisture_level);
  } else if (DEBUG > 1) {
    String moisture_level;       
    get_moisture_percentage(moisture_val, moisture_level);
    Serial.println(moisture_level);
  }
  delay(DELAY_SECONDS * 1000);
}

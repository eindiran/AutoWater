/**
 * SolenoidTest.ino
 * Run this code to test the setup of the solenoid valve.
 * Author: eindiran <eindiran@uchicago.edu>
 */

/** Initialize globals */
const int DEBUG = 1;         // If this is on, the system will be more verbose
const int OPEN_SECONDS = 1;  // Number of seconds to open the solenoid valve for
const int DELAY_SECONDS = 1; // The time between runs in loop()
const int SOLENOID_PIN = 7;  // The pin value on the Arduino used for the sv

/**
 * setup() --> One-time setup steps:
 * open serial port, set baud rate to 9600, prep solenoid's pin.
 */
void setup() {
  Serial.begin(9600);
  pinMode(SOLENOID_PIN, OUTPUT);
}

/**
 * nc_turn_solenoid() --> Open a NC Solenoid valve:
 * Puts a normally closed solenoid valve into its open
 * state for num_seconds, then closes it.
 */
void nc_turn_solenoid(int num_seconds) {
  int num_ms = num_seconds * 1000;
  if (DEBUG) {
    Serial.print("Opening solenoid valve for "); Serial.print(num_seconds); Serial.println(" second(s).");
  }
  digitalWrite(SOLENOID_PIN, HIGH); // Switched magnet on; open
  delay(num_ms);
  digitalWrite(SOLENOID_PIN, LOW);  // Switched magnet off; closed
  if (DEBUG) {
    Serial.println("Solenoid valve closed.");
  }
}

/**
 * loop() --> Opens the solenoid for OPEN_SECONDS
 * then waits for DELAY_SECONDS, ad infinitum, until the Arduino
 * is otherwise interfered with.
 */
void loop() {
  nc_turn_solenoid(OPEN_SECONDS); // turn on for OPEN_SECONDS
  delay(DELAY_SECONDS * 1000);
}

int DEBUG = 1;
int solenoidPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
}

/**
 * Open a NC Solenoid valve:
 * Puts a normally closed solenoid valve into its open
 * state for num_seconds, then closes it.
 */
void nc_turn_solenoid(int num_seconds) {
  int num_ms = num_seconds * 1000;
  if (DEBUG) {
    // Poor-man's printf
    Serial.print("Opening solenoid valve for "); Serial.print(num_seconds); Serial.println(".");
  }
  digitalWrite(solenoidPin, HIGH); // Switched magnet on; open
  delay(num_ms);
  digitalWrite(solenoidPin, LOW); // Switched magnet off; closed
  if (DEBUG) {
    Serial.println("Solenoid valve closed.");
  }
}

void loop() {
  nc_turn_solenoid(1); // turn on for 1s
  delay(1000);
}

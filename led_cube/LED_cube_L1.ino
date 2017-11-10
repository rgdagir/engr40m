// Starter code to blink every LED using the simplest possible iteration
// through anode and cathode pins.
// ENGR 40M - Raul Gallo Dagir - TA: Matthew Meza

// Define arrays for the anode (+) and cathode (-) wire pins
// Your pins will probably be different.
// Remember that analog pins (A0, A1, ...) can also act as digital
// LED Cube Test Code
const byte ANODE_PINS[8] = {17, 16, 15, 14, 13, 12, 19, 18};
const byte CATHODE_PINS[8] = {11, 10, 9, 8, 7, 6, 5, 4};

void setup() {
  // Make all of the anode (+) and cathode (-) wire pins outputs
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
  }
  // turn everything off
  for (byte i = 0; i < 8; i++) {
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
}

void loop() {
  //turn the anodes on, one by one
  for (byte aNum = 0; aNum < 8; aNum++) {
    digitalWrite(ANODE_PINS[aNum], LOW);
    // for every anode driven to on (LOW), we iterate through the cathodes, lighting up all LEDs individually
    for (byte cNum = 0; cNum < 8; cNum++) {
      digitalWrite(CATHODE_PINS[cNum], LOW);
      // delay to blink the LEDs
      delay(100);
      // drives the cathode off so that the entire row won't be lit altogether by the end of the loop
      digitalWrite(CATHODE_PINS[cNum], HIGH);
    }
    // turns anode off, prepares to restart the for loop on a different anode
    digitalWrite(ANODE_PINS[aNum], HIGH);
  }
}


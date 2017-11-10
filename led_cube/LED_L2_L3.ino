/* LED cube test code
 *
 * Reads (x,y,z) co-ordinates from the Serial Monitor and toggles the state of
 * the LED at that co-ordinate. The co-ordinates are specified as "x y z", e.g.
 * "1 2 2", followed by a newline. Invalid co-ordinates are rejected.
 *
 * You need to fill in all the places marked TODO.
 *
 * == Setting up the Serial Monitor ==
 * The Serial Monitor must be configured (bottom-right corner of the screen) as:
 *   - Newline (for the line ending)
 *   - Baud rate 115200
 *
 * ENGR 40M
 * July 2017
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires. Hint: if you order these
// intelligently, it will make your mapping getLEDState() function a lot
// simpler!
const byte ANODE_PINS[8] = {17, 16, 15, 14, 13, 12, 19, 18};
const byte CATHODE_PINS[8] = {11, 10, 9, 8, 7, 6, 5, 4};
byte b;

void setup()
{
  // Make all of the anode (+) wire and cathode (-) wire pins outputs
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
  }
  //  turn "off" all the LEDs (hint: you'll need a for loop)
  for (byte i = 0; i < 8; i++) {
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
  // Initialize serial communication
  // (to be read by Serial Monitor on your computer)
  Serial.begin(115200);
  Serial.setTimeout(100);
}

/* Function: getLEDState
 * ---------------------
 * Returns the state of the LED in a 4x4x4 pattern array, each dimension
 * representing an axis of the LED cube, that corresponds to the given anode (+)
 * wire and cathode (-) wire number.
 *
 * This function is called by display(), in order to find whether an LED for a
 * particular anode (+) wire and cathode (-) wire should be switched on.
 */
inline byte getLEDState(byte pattern[4][4][4], byte aNum, byte cNum)
{
  //  fill this in to return the value in the pattern array corresponding
  // to the anode (+) wire and cathode (-) wire number (aNum and cNum) provided.
  int x = aNum % 4; // the remainder of the division of the anode's number by 4 will determine its x value
  int y = cNum % 4; // the remainder of the division of the cathode's number by 4 will determine its y value
  int z;
  // the following if clauses determine the z position of the LED by evaluating the range of the anode's and the cathode's numbers
  if (aNum < 4 && cNum < 4){
    z = 0;
  } else if (aNum < 4 && cNum > 3) {
    z = 1;
  } else if (aNum > 3 && cNum > 3) {
    z = 2;
  } else if (aNum > 3 && cNum <4) {
    z = 3;
  }
  
  return pattern[x][y][z];
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
 
void display(byte pattern[4][4][4], byte b)
{
  for (byte aNum = 0; aNum < 8; aNum++) { // iterate through anode (+) wires
    // Set up all the cathode (-) wires first
    for (byte cNum = 0; cNum < 8; cNum++) { // iterate through cathode (-) wires
      byte value = getLEDState(pattern, aNum, cNum); // look up the value
      //  Activate the cathode (-) wire if `value` is > 0, otherwise deactivate it
      if (value > 0) {
        digitalWrite(CATHODE_PINS[cNum], LOW);
      } else {
        digitalWrite(CATHODE_PINS[cNum], HIGH);
      }
    }

    // Activate the anode (+) wire (without condition)
    digitalWrite(ANODE_PINS[aNum], LOW);
    
    //  Wait a short time
    delayMicroseconds(100*b);

    //  We're now done with this row, so deactivate the anode (+) wire
    digitalWrite(ANODE_PINS[aNum], HIGH);
  }
}

void loop(){
  static byte ledPattern[4][4][4]; // 1 for on, 0 for off

  byte x = 0;
  byte y = 0;
  byte z = 0;
  static char message[60];

  if (Serial.available()) {
    // Parse the values from the serial string
    x = Serial.parseInt();
    y = Serial.parseInt();
    z = Serial.parseInt();

    // Check for input validity
    if (Serial.read() != '\n') {
      Serial.println("invalid input - check that line ending is set to \"Newline\"; input must be three numbers");
      return;
    }
    if (x < 0 || x > 3 || y < 0 || y > 3 || z < 0 || z > 3) {
      sprintf(message, "x = %d, y = %d, z = %d -- indices out of bounds", x, y, z);
      Serial.println(message);
      return;
    }

    // Print to Serial Monitor to give feedback about input
    sprintf(message, "x = %d, y = %d, z = %d", x, y, z);
    Serial.println(message);

    // Toggle the LED state
    ledPattern[x][y][z] = !ledPattern[x][y][z];
  }

  // This function gets called every loop
  display(ledPattern, 15);
}


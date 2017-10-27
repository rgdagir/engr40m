// setting up pins

const int rightPMOS = 2;
const int leftPMOS = 3;
const int toggleSwitch = 18;
const int limitSwitch = 14;
const int buzzerPin = 9 ;
int toggleState = 0;
int limitState = 0;
int freq = 0;
int timer = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(rightPMOS, OUTPUT);
  pinMode(leftPMOS, OUTPUT);
  pinMode(toggleSwitch, INPUT_PULLUP);
  pinMode(limitSwitch, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever, alterating the 4 methods of interacting with the useless box:
void loop() {
  modeStandard();
  modeMario();
  modeSlowPeek();
  modeStoppin();
}

// standard mode
void modeStandard(){
   while (toggleState == LOW) { // code that runs whenever the toggle switch is leaning forward
    forward();                 // finger goes forward
    checkSwitches();           // check whether the switches are in the same configuration
  }
  while (toggleState == HIGH && limitState == LOW) { // code that runs whenever the toggle is off (leaning back) and the limit switch is not pressed
    reverse();                                      // finger goes reverse
    checkSwitches();                                // check whether the switches are in the same configuration
  }
  while (toggleState == HIGH && limitState == HIGH) { // code that runs whenever the toggle and the limit switch are both off (finger is retracted and pressing the limit switch
    stopper();                                        // finger stops moving
    checkSwitches();                                  // check whether the switches are in the same configuration
  }
}

// stoppin mode: finger goes forward and reverse stopping every 150 milliseconds. the finger is also synced with the beeping sound
void modeStoppin(){
  while (toggleState == LOW) { // code that runs whenever the toggle switch is leaning forward
    forwardStoppin();                 // finger goes forward
    checkSwitches();           // check whether the switches are in the same configuration
    buzzerLowFreq();          // buzzer beeps at a low frequency, synced with the finger
  }
  while (toggleState == HIGH && limitState == LOW) { // code that runs whenever the toggle is off (leaning back) and the limit switch is not pressed
    reverseStoppin();                                      // finger goes reverse
    checkSwitches();                                // check whether the switches are in the same configuration
    buzzerHighFreq();                     // buzzer beeps at a high frequency, synced with the finger
  }
  while (toggleState == HIGH && limitState == HIGH) { // code that runs whenever the toggle and the limit switch are both off (finger is retracted and pressing the limit switch
    stopper();                                        // finger stops moving
    checkSwitches();                                  // check whether the switches are in the same configuration
  }
}

void modeSlowPeek() {
  while (toggleState == LOW) { // code that runs whenever the toggle switch is leaning forward
    forwardSlow(); // finger goes forward slowly
    delay(300); 
    stopper(); // finger peeks out
    delay(100);
    checkSwitches();
    forwardSlow(); // goes forward again to hit the switch
    checkSwitches();           // check whether the switches are in the same configuration
  }
  while (toggleState == HIGH && limitState == LOW) { // code that runs whenever the toggle is off (leaning back) and the limit switch is not pressed
    reverseSlow();                                      // finger goes reverse slowly
    checkSwitches();                                // check whether the switches are in the same configuration
  }
  while (toggleState == HIGH && limitState == HIGH) { // code that runs whenever the toggle and the limit switch are both off (finger is retracted and pressing the limit switch
    stopper();                                        // finger stops moving
    checkSwitches();                                  // check whether the switches are in the same configuration
  }
}

void modeMario(){
  while (toggleState == LOW) { // code that runs whenever the toggle switch is leaning forward
    forward( );
    delay(250);
    stopper();
    marioTime();
    forward();
    delay(200);  // finger goes forward
    Serial.println("vamooooo");  // debug
  }
  while (toggleState == HIGH &&  limitState == LOW) { // code that runs whenever the toggle is off (leaning back) and the limit switch is not pressed
    reverseStoppin();                                      // finger goes reverse
    checkSwitches();                                // check whether the switches are in the same configuration
    buzzerHighFreq();
    Serial.println("volta cusaaao");            // debug
  }
  while (toggleState == HIGH && limitState == HIGH) { // code that runs whenever the toggle and the limit switch are both off (finger is retracted and pressing the limit switch
    stopper();                                        // finger stops moving
    checkSwitches();                                  // check whether the switches are in the same configuration
    Serial.println("a paradinhaaaaaa");   // debug
  }
}

void checkSwitches() {                        // function that checks switches. when the code goes inside the while loop, i dont know why, it stops checking the switches, so I made this function
  toggleState = digitalRead(toggleSwitch);    // read toggle switch
  limitState = digitalRead(limitSwitch);      // read limit switch
}

//function to move finger forward
void forward() {                
  digitalWrite(leftPMOS, HIGH);
  digitalWrite(rightPMOS, LOW);
}

// function to move finger backwards
void reverse() {
  digitalWrite(leftPMOS, LOW);
  digitalWrite(rightPMOS, HIGH);
}


// function to stop the finger
void stopper() {
  digitalWrite(leftPMOS, LOW);
  digitalWrite(rightPMOS, LOW);
}

void forwardStoppin() {
    forward();
    delay(150);
    stopper();
    delay(150);
}

void reverseStoppin() {
  reverse();
  delay(150);
  stopper();
  delay(150);
}      

void forwardSlow() {
  analogWrite(leftPMOS, 50);
  analogWrite(rightPMOS, 0);
}

void reverseSlow() {
  analogWrite(leftPMOS, 0);
  analogWrite(rightPMOS, 50);
}

void buzzerHighFreq(){
  tone(buzzerPin, 500); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  noTone(buzzerPin);     // Stop sound...
  delay(100);   
}

void buzzerLowFreq(){
  tone(buzzerPin, 300); // Send 1KHz sound signal...
  delay(150);        // ...for 1 sec
  noTone(buzzerPin);     // Stop sound...
  delay(150);   
}

// Mario Bros. song in 8-bit for the buzzer
void marioTime() {
  tone(buzzerPin,660,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,510,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,770,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(550);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(575);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,510,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(450);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(400);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,320,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(500);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,440,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,480,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(330);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,450,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(200);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(200);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,760,50);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,860,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,700,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,760,50);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(350);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,520,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,580,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,480,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(500);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,510,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(450);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(400);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,320,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(500);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,440,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,480,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(330);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,450,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(200);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(200);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,760,50);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,860,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,700,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,760,50);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(350);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,660,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,520,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,580,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,480,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(500);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,760,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,720,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,680,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,620,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,650,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,570,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(220);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,760,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,720,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,680,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,620,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,650,200);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,1020,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,1020,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,1020,80);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,760,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,720,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,680,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,620,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,650,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,430,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,570,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(420);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,585,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(450);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,550,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(420);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(360);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,380,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,500,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  tone(buzzerPin,760,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,720,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,680,100);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  tone(buzzerPin,620,150);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }
  delay(300);
  checkSwitches();
  if (toggleState == HIGH){
    return;
  }

  
}


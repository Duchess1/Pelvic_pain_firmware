#define OUTPUT_PIN 9
#define MODE_BUTTON 8
#define ENABLED HIGH

//TENS Modes
#define HAMMERING   0
#define ACUPUNCTURE 1
#define NARAPATHY   2
#define CUPPING     3
#define SCRAPING    4
#define MASSAGE     5

void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT); 
  pinMode(11,OUTPUT); 
  pinMode(10,OUTPUT); 
  pinMode(OUTPUT_PIN,OUTPUT); 
  pinMode(MODE_BUTTON,OUTPUT); 

  digitalWrite(12, HIGH); 
  digitalWrite(11, HIGH); 
  digitalWrite(10, HIGH); 
  digitalWrite(OUTPUT_PIN, HIGH); 
  digitalWrite(MODE_BUTTON, HIGH); 

  off(); 
  switchMode(SCRAPING); 
  delay(2000);
  switchMode(ACUPUNCTURE); 
  delay(2000);
  switchMode(MASSAGE); 
}

void switchMode(int mode) {
  // Turn device off and then on
  static int current_mode = HAMMERING;
  int delta = 0; 
  
  if (mode > current_mode) {
    delta = mode - current_mode; 
  }
  else if (mode < current_mode) {
    delta = mode + (6-current_mode); 
  }

  for (int i = 0; i < delta; i++) {
    digitalWrite(MODE_BUTTON, LOW); 
    delay(125); 
    digitalWrite(MODE_BUTTON, HIGH); 
    delay(125); 
  } 
  current_mode = mode;
}

void lowPower(void) {
  digitalWrite(12, LOW); 
  digitalWrite(11, HIGH); 
  digitalWrite(10, HIGH); 
  digitalWrite(OUTPUT_PIN, LOW); 
}
void mediumPower(void) {
  digitalWrite(12, LOW); 
  digitalWrite(11, LOW); 
  digitalWrite(10, HIGH); 
  digitalWrite(OUTPUT_PIN, LOW); 
}

void highPower(void) {
  digitalWrite(12, LOW); 
  digitalWrite(11, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(OUTPUT_PIN, LOW); 
}

void off(void) {
  digitalWrite(12, HIGH); 
  digitalWrite(11, HIGH); 
  digitalWrite(10, HIGH); 
  digitalWrite(OUTPUT_PIN, HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
 
//  lowPower(); 
//  delay(2000); 
//  mediumPower(); 
//  delay(2000); 
//  highPower(); 
//  delay(2000);`
}

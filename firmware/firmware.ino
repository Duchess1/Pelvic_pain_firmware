//IASP - number one pain research in the world 


#define PELVIS_PIN_ONE 12
#define PELVIS_PIN_TWO 11
#define PELVIS_OUTPUT_PIN 10
#define BACK_PIN_ONE 8
#define BACK_PIN_TWO 7
#define BACK_OUTPUT_PIN 6

#define ENABLED HIGH

//TENS Modes
#define HAMMERING   0
#define ACUPUNCTURE 1
#define NAPRAPATHY  2
#define CUPPING     3
#define SCRAPING    4
#define MASSAGE     5

//TENS BUTTONS
#define MODE_BUTTON     9
#define HZ_BUTTON       5
#define BUTTON_DELAY 120 

#define DEBUG 1

void setup() {
  Serial.begin(115200);
  
  pinMode(PELVIS_PIN_ONE,OUTPUT); 
  pinMode(PELVIS_PIN_TWO,OUTPUT); 
  pinMode(10,OUTPUT); 
  pinMode(PELVIS_OUTPUT_PIN,OUTPUT); 
  pinMode(MODE_BUTTON,OUTPUT); 
  pinMode(HZ_BUTTON,OUTPUT); 
  pinMode(BACK_PIN_TWO,OUTPUT); 
  pinMode(BACK_PIN_ONE,OUTPUT); 
  pinMode(BACK_OUTPUT_PIN,OUTPUT); 

  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, HIGH); 
  digitalWrite(PELVIS_OUTPUT_PIN, HIGH); 
  digitalWrite(MODE_BUTTON, HIGH); 
  digitalWrite(HZ_BUTTON, HIGH); 
  digitalWrite(BACK_PIN_TWO, HIGH); 
  digitalWrite(BACK_PIN_ONE, HIGH); 
  digitalWrite(BACK_OUTPUT_PIN, LOW); 


  off();
   
  delay(1500);
  deepMode(LOW); 
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
    delay(BUTTON_DELAY); 
    digitalWrite(MODE_BUTTON, HIGH); 
    delay(BUTTON_DELAY); 
  } 
  current_mode = mode;
}

void deepMode(int enabled) {

  static int current_state = LOW; 
  
  if (enabled != current_state) {
    digitalWrite(HZ_BUTTON, LOW); 
    delay(BUTTON_DELAY); 
    digitalWrite(HZ_BUTTON, HIGH); 
    delay(BUTTON_DELAY); 
    current_state = enabled; 
  }
}

void lowPower(void) {

  Serial.println("Low power"); 
  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, HIGH); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}
void mediumPower(void) {

  Serial.println("Medium power"); 
  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, LOW); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}

void highPower(void) {

  Serial.println("High power"); 
  digitalWrite(PELVIS_PIN_ONE, LOW); 
  digitalWrite(PELVIS_PIN_TWO, LOW); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}

void backLowPower(void) {

  Serial.println("Back low power"); 
  digitalWrite(BACK_PIN_ONE, LOW); 
  digitalWrite(BACK_PIN_TWO, LOW);
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void backMediumPower(void) {

  Serial.println("Back medium power"); 
  digitalWrite(BACK_PIN_ONE, LOW); 
  digitalWrite(BACK_PIN_TWO, HIGH);
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void backHighPower(void) {

  Serial.println("Back high power"); 
  digitalWrite(BACK_PIN_ONE, HIGH); 
  digitalWrite(BACK_PIN_TWO, HIGH); 
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void off(void) { 

  if (DEBUG) {
    Serial.println("Off"); 
  }
  lowPower(); 
  backLowPower();
  digitalWrite(PELVIS_OUTPUT_PIN, HIGH); 
  digitalWrite(BACK_OUTPUT_PIN, HIGH); 
  deepMode(LOW); 
}
void on(void) {
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
  digitalWrite(BACK_OUTPUT_PIN, HIGH); 
}

void effectTingling(int iterations) {
  off(); 
  switchMode(ACUPUNCTURE); 
  delay(1750);  

  for (int i = 0; i < iterations; i++) {
    on();
    delay(1000); 
    off(); 
    delay(2000); 
  }
}

//========================================
//          effectStab
//  Low power hammering for 3s.
//  High power stab for 500ms
//
//  Total: 3.5s
//========================================
void effectStab(void) {

  if (DEBUG) {
    Serial.println("Stabbing"); 
  }
  
  off(); 
  switchMode(HAMMERING); 
  lowPower(); 
  delay(3000); 
  highPower();
  delay(750); 
  lowPower(); 
}

void effectDeepStab(void) {

  if (DEBUG) {
    Serial.println("Deep stabbing"); 
  }
  off(); 
  deepMode(HIGH); 
  switchMode(HAMMERING); 
  highPower(); 
  delay(3750); 
}


//========================================
//          effectTearing
//========================================
void effectTearing(void) {

  if (DEBUG) {
    Serial.println("Tearing"); 
  }
  
  off(); 
  switchMode(NAPRAPATHY); 

  highPower(); 
  delay(10000); 

  deepMode(HIGH); 
  delay(7000); 

  mediumPower();
  delay(5000); 

  highPower();
  deepMode(HIGH); 
  delay(10000); 
}

//========================================
//      effectTwisting 
//  - Wringing out of stomach 
//  - Twisting abdomen
//  - Pins and needles 
//  - Intense pressure
//  - 
//========================================
void effectTwisting(void) {

  if (DEBUG) {
    Serial.println("Tearing"); 
  }
  
  off(); 
  switchMode(SCRAPING); 

  //Just back
  backHighPower();
  deepMode(HIGH); 
  delay(10000); 

  //Front and back
  mediumPower(); 
  delay(10000);

  //Just back
  off(); 
  backHighPower();
  deepMode(HIGH); 
  delay(10000);

  // Just front 
  backLowPower(); 
  highPower();
  delay(10000);  
}

//========================================
//          effectCattleProd
//   
//========================================
void effectCattleProd(void) {

  if (DEBUG) {
    Serial.println("Cattle prod"); 
  }
  
  off(); 
  switchMode(HAMMERING); 
  deepMode(LOW); 

 // Just front 
  backLowPower(); 
  highPower();
  delay(2000);  

  // off
  off(); 
  delay(5000); 
  
  // Just back
  backHighPower();
  delay(2000); 

  // off
  off(); 
  delay(5000); 

  //Front and back
  highPower(); 
  backHighPower(); 
  delay(5000);

  off();
}

//========================================
//          effectPeriodPain
//   High power accupuncture
//========================================
void effectPeriodPain(void) {

  if (DEBUG) {
    Serial.println("Period pain"); 
  }

  off(); 
  switchMode(ACUPUNCTURE); 
  highPower(); 
  delay(10000); 
  
  off(); 
  mediumPower(); 
  delay(5000); 
  
  highPower(); 
  delay(2500); 

  deepMode(HIGH); 
  delay(3000); 
  deepMode(LOW); 
}
  

//========================================
//          effectBluntStab
//========================================
void effectBluntStab(void) {

  if (DEBUG) {
    Serial.println("Blunt stab"); 
  }
  
  off(); 
  switchMode(ACUPUNCTURE); 
  
  lowPower(); 
  delay(1500); 
  
  mediumPower(); 
  deepMode(HIGH); 
  delay(1000); 
  
  lowPower(); 
  deepMode(LOW);  
}

void effectBackground(void) {

  off(); 
  switchMode(NAPRAPATHY); 
  deepMode(HIGH); 
  mediumPower();  
}

void effectDeepScraping(void) {

  if (DEBUG) {
    Serial.println("Deep scrape"); 
  }
  
  off(); 
  switchMode(SCRAPING); 
  deepMode(HIGH); 
  highPower(); 

  delay(10000); 
  off(); 
}

void effectSandwichPressure(void) {
  if (DEBUG) {
    Serial.println("Tearing"); 
  }
  
  off(); 
  switchMode(NAPRAPATHY); 

  backHighPower(); 
  highPower(); 
  delay(10000); 

  deepMode(HIGH); 
  delay(7000); 

  backMediumPower(); 
  mediumPower();
  delay(5000); 

  backHighPower(); 
  highPower();
  deepMode(HIGH); 
  delay(10000); 
}

void effectBackHammering(void) {

  if (DEBUG) {
    Serial.println("Back hammering"); 
  }
  off();
  
  backLowPower(); 
  deepMode(HIGH); 
  switchMode(HAMMERING); 
  backHighPower(); 
  delay(3750); 
}

void loop() {

  Serial.println("\n-----------------------------------------------------------------------------");
  Serial.println("Ready to begin\nPress any key, followed by return."); 
  while(Serial.available() < 1);

//  effectSandwichPressure(); 
//
//  effectBackHammering();

//  effectCattleProd(); 

  backLowPower(); 
  delay(5000); 
  
  backMediumPower(); 
  delay(5000); 
  
  backHighPower(); 
  delay(5000);

  while(1); 
  
  // Stab 3 times - 10.5 seconds
  for (int i = 0; i < 3; i++) {
    effectStab(); 
  }

  //varying degrees of period pain for 41 seconds
  effectPeriodPain(); 
  effectPeriodPain(); 

  //Tearing for 20.5 seconds
  effectTearing(); 

  //Deep stab for 3.5 seconds (one stab) 
  effectDeepStab(); 

  //Tearing for 20.5 seconds
  effectTearing(); 
 
  off(); 
  Serial.println("Done"); 
  while(1); 
}

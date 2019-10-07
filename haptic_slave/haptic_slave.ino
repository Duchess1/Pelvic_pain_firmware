#include <ArduinoJson.h>

#define PELVIS_PIN_ONE 12
#define PELVIS_PIN_TWO 11
#define PELVIS_OUTPUT_PIN 10
#define BACK_PIN_ONE 8
#define BACK_PIN_TWO 7
#define BACK_OUTPUT_PIN 6
#define HARD_POWER_PIN 4

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

unsigned long current_state_expiry = millis(); 
bool next_state_received = false; 
struct State {
  String mode;
  bool deep_mode;
  String front_power;
  String back_power;
  unsigned long period;
};

State next_state = State{0, false, "", "", 0};
State current_state = State{0, false, "", "", 0};
String current_mode_str = ""; 
int current_mode = HAMMERING;
int is_on = false; 

unsigned long fifteen_minutes = millis() + 900000; 

void setup() {

  Serial.begin(115200);

  // Wait for haptics to turn off
  delay(1000); 
  
  pinMode(PELVIS_PIN_ONE,OUTPUT); 
  pinMode(PELVIS_PIN_TWO,OUTPUT); 
  pinMode(10,OUTPUT); 
  pinMode(PELVIS_OUTPUT_PIN,OUTPUT); 
  pinMode(MODE_BUTTON,OUTPUT); 
  pinMode(HZ_BUTTON,OUTPUT); 
  pinMode(BACK_PIN_TWO,OUTPUT); 
  pinMode(BACK_PIN_ONE,OUTPUT); 
  pinMode(BACK_OUTPUT_PIN,OUTPUT); 
  pinMode(HARD_POWER_PIN, OUTPUT);

  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, HIGH); 
  digitalWrite(PELVIS_OUTPUT_PIN, HIGH); 
  digitalWrite(MODE_BUTTON, HIGH); 
  digitalWrite(HZ_BUTTON, HIGH); 
  digitalWrite(BACK_PIN_TWO, HIGH); 
  digitalWrite(BACK_PIN_ONE, HIGH); 
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
  digitalWrite(HARD_POWER_PIN, LOW);

  off();
  hardOff();     
}

void hardOff(void) {
   digitalWrite(HARD_POWER_PIN, HIGH);
   is_on = false;  
}

void hardOn(void) {

   if (is_on == false) {
    digitalWrite(HARD_POWER_PIN, LOW); 
    current_mode = HAMMERING; 
    delay(3000); 
    is_on = true; 
    fifteen_minutes = fifteen_minutes + 900000;
   } 
}

void switchMode(int mode) {
  // Turn device off and then on
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

  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, HIGH); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}
void mediumPower(void) {

  digitalWrite(PELVIS_PIN_ONE, HIGH); 
  digitalWrite(PELVIS_PIN_TWO, LOW); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}

void highPower(void) {

  digitalWrite(PELVIS_PIN_ONE, LOW); 
  digitalWrite(PELVIS_PIN_TWO, LOW); 
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
}

void backLowPower(void) {

  digitalWrite(BACK_PIN_ONE, LOW); 
  digitalWrite(BACK_PIN_TWO, LOW);
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void backMediumPower(void) {

  digitalWrite(BACK_PIN_ONE, LOW); 
  digitalWrite(BACK_PIN_TWO, HIGH);
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void backHighPower(void) {

  digitalWrite(BACK_PIN_ONE, HIGH); 
  digitalWrite(BACK_PIN_TWO, HIGH); 
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
}

void backOff(void) {
   digitalWrite(BACK_OUTPUT_PIN, HIGH);  
}

void frontOff(void) {
    digitalWrite(PELVIS_OUTPUT_PIN, HIGH); 
}

void off(void) { 

  lowPower(); 
  backLowPower();
  backOff(); 
  frontOff(); 
  deepMode(LOW); 
}
void on(void) {
  digitalWrite(PELVIS_OUTPUT_PIN, LOW); 
  digitalWrite(BACK_OUTPUT_PIN, LOW); 
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
  highPower(); 
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

  lowPower(); 
  delay(5000); 

  mediumPower(); 
  delay(5000); 

  highPower();
  delay(5000); 

  deepMode(HIGH); 
  delay(12000); 
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
  deepMode(HIGH); 

 // Just front 
  highPower();
  delay(5000);  

  // off
  off(); 
  delay(5000); 
  
  // Just back
  backHighPower();
  delay(5000); 

  // off
  off(); 
  delay(5000); 

  //Front and back  
  deepMode(LOW); 
  highPower(); 
  backHighPower(); 
  delay(5000);

  off();
}

//========================================
//          effectPeriodPain
//   High power acupuncture
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
  delay(8000); 
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

  backLowPower(); 
  mediumPower();
  delay(5000); 

  backMediumPower(); 
  highPower();
  deepMode(HIGH); 
  delay(10000); 

  off(); 
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
  off(); 
}

void loop() {

  // put your main code here, to run repeatedly:
  StaticJsonDocument<200> msg;
  String input = ""; 

  if (Serial.available() > 10 ) {

    input = Serial.readStringUntil('\n'); 

    DeserializationError error = deserializeJson(msg, input);
  
    // Test if parsing succeeded.
    if (error) {
      Serial.print("deserializeMsgPack() failed: ");
      Serial.println(error.c_str());
      return;
    }

    hardOn(); 
    
    next_state.mode         = msg["mode"].as<String>();
    next_state.deep_mode    = msg["deep_mode"];
    next_state.front_power  = msg["front_power"].as<String>();
    next_state.back_power   = msg["back_power"].as<String>();
    next_state.period       = msg["period"]; 
    
    next_state_received = true; 
  }

  // If our current state has expired
  if (next_state_received == true) {
    // Set mode based on input
    if (next_state.mode.indexOf("hammering") != -1) {
      switchMode(HAMMERING); 
    }
    else if (next_state.mode.indexOf("acupuncture") != -1) {
      switchMode(ACUPUNCTURE); 
    }
    else if (next_state.mode.indexOf("naprapathy") != -1) {
      switchMode(NAPRAPATHY); 
    }
    else if (next_state.mode.indexOf("cuping") != -1) {
      switchMode(CUPPING); 
    }
    else if (next_state.mode.indexOf("scraping") != -1) {
      switchMode(SCRAPING); 
    }
    else if (next_state.mode.indexOf("massage") != -1) {
      switchMode(MASSAGE); 
    }
    else if (next_state.mode.indexOf("setup") != -1) {
      hardOn();
      off(); 
      return; 
    }
    else {
      off(); 
      hardOff(); 
      return; 
    }

    current_mode_str = next_state.mode; 
  
    // Set deep mode
    if (next_state.deep_mode == true) {
      deepMode(HIGH); 
    }
    else {
      deepMode(LOW); 
    }

    // Set front power 
    if (next_state.front_power.indexOf("high") >= 0) {
      highPower(); 
    }
    else if (next_state.front_power.indexOf("medium") >= 0) {
      mediumPower(); 
    }
    else if (next_state.front_power.indexOf("low") >= 0) {
      lowPower(); 
    }
    else {
      frontOff(); 
    }

    // Set back power 
    if (next_state.back_power.indexOf("high") >= 0) {
      backHighPower(); 
    }
    else if (next_state.back_power.indexOf("medium") >= 0) {
      backMediumPower(); 
    }
    else if (next_state.back_power.indexOf("low") >= 0) {
      backLowPower(); 
    }
    else {
      backOff(); 
    }

    // Set period
    current_state_expiry = millis() + next_state.period;  
    
    // Set current state
    current_state.mode = next_state.mode; 
    current_state.deep_mode = next_state.deep_mode; 
    current_state.front_power = next_state.front_power; 
    current_state.back_power = next_state.back_power;
    current_state.period = next_state.period;

    next_state_received = false; 

    msg["mode"] = current_mode_str;
    msg["deep_mode"] = current_state.deep_mode;
    msg["front_power"] = current_state.front_power;
    msg["back_power"] = current_state.back_power;
    msg["period"] = current_state.period;

    input = "";
    serializeJson(msg, input);
    Serial.println(input);
  }
  else if (millis() > current_state_expiry) {
    off(); 
  }

  if (millis() > fifteen_minutes && is_on == true) {
    hardOff(); 
    delay(1000); 
    hardOn();
  }
}

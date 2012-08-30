/*
  ArduLamp
  Lamp manage by Arduino
  
 */

char buf;
int lamp_pin = 13;
int countdown;
boolean countdown_enable = false;
char current_command;
boolean waiting_data;

void setup() { 
  pinMode(lamp_pin, OUTPUT);
  Serial.begin(9600);
} 

/**
 * Parse command
 */
void parseCommand() {
    buf = Serial.read();
    Serial.println(buf); // debug
    // turn off
    if (buf == 'f') { 
      digitalWrite(lamp_pin, LOW);
      countdown_enable = false; // disable countdown because we have turned off now the lamp
    } 
    // turn on
    if (buf == 'n') { 
      digitalWrite(lamp_pin, HIGH);
    }
    // delayed turn off, but we need more data
    if (buf == 't') {
      // read time
      current_command = buf;
      waiting_data = true;
    }
}

/**
 * Parse data
 */
void parseData() {
  byte d = Serial.read();
  // delayed turn off
  if (current_command == 't') {
    countdown_enable = true;
    countdown = (int)d * 60;
  }
}

void loop() { 
  if (Serial.available() > 0) { 
    if (waiting_data) {
      parseData();
    } else {
      parseCommand();
    }
  }
  
  if (countdown_enable) {
    countdown--;
    if (countdown == 0) {
      countdown_enable = false;
      digitalWrite(lamp_pin, LOW);
    }
  }
  delay(1000);
} 

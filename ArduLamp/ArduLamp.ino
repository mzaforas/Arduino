/*
  ArduLamp
  Lamp manage by Arduino
  
 */

char buf;
int lamp_pin = 13;
int countdown;
boolean countdown_enable = false;

void setup() { 
  pinMode(lamp_pin, OUTPUT);
  Serial.begin(9600);
} 

void loop() { 
  if (Serial.available() > 0) { 
    buf = Serial.read();
    if (buf == 'f') { 
      digitalWrite(lamp_pin, LOW);
    } 
    if (buf == 'n') { 
      digitalWrite(lamp_pin, HIGH);
    }
    if (buf == 't') {
      countdown_enable = true;
      countdown = 600; // 10 minutos
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

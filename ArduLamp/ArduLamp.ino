/*
  ArduLamp
  Lamp manage by Arduino
  
 */

char buf;
int lamp_pin = 13;

void setup() { 
  pinMode(lamp_pin, OUTPUT);
  Serial.begin(9600);
} 

void loop() { 
  char buf;
  if (Serial.available() > 0) { 
    buf = Serial.read();
    if (buf == '0') { 
      digitalWrite(lamp_pin, LOW);
    } 
    if (buf == '1') { 
      digitalWrite(lamp_pin, HIGH);
    }
  }
} 

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
  if (Serial.available() > 0) { 
    buf = Serial.read();
    if (buf == 'f') { 
      digitalWrite(lamp_pin, LOW);
    } 
    if (buf == 'n') { 
      digitalWrite(lamp_pin, HIGH);
    }
  }
  delay(1000);
} 

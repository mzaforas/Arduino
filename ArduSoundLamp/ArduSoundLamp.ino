/*
  ArduLamp
  Lamp manage by Arduino
  
 */

//char buf;
int lamp_pin = 13;
//int countdown;
//boolean countdown_enable = false;
int sound = 0;
boolean turn_on = false; 

void setup() { 
  pinMode(lamp_pin, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
} 

void loop() { 
  int previous_sound = sound;
  sound = analogRead(5);
  
  if (previous_sound != sound) {
    Serial.println(sound); 
  }
  Serial.print("d: ");
  Serial.println(digitalRead(7)); 
  
  if (sound >= 30) {
    if (turn_on) {
      digitalWrite(lamp_pin, LOW);
      turn_on = false;
    } else {
      digitalWrite(lamp_pin, HIGH);
      turn_on = true;
    }
    delay(500);
  }
  delay(100);
} 

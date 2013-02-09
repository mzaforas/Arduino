/*
  Arduino Irrigation System
 Manuel Zaforas
 
 */

// CONSTANTS
int relay_pin = 13;
int period = 60 * 60; // every hour (in seconds)
int irrigation_time = 2000; // ms


int countdown;

void setup() { 
  pinMode(relay_pin, OUTPUT);
  Serial.begin(9600);
  countdown = period;
} 

void loop() { 
  countdown--;
  Serial.println(countdown);
  if (countdown == 0) {
    digitalWrite(relay_pin, HIGH);
    delay(irrigation_time);
    digitalWrite(relay_pin, LOW);
    countdown = period;
  }
  delay(1000);
} 


/*
  Arduino Irrigation System
 Manuel Zaforas
 
 */

// CONSTANTS
int relay_pin = 13;
int period = 6 * 60 * 60; // every hour (in seconds)
int irrigation_time = 10000; // ms


int countdown;

void setup() { 
  pinMode(relay_pin, OUTPUT);
  Serial.begin(9600);
  countdown = 0;
} 

void loop() { 
  Serial.println(countdown);
  if (countdown == 0) {
    digitalWrite(relay_pin, HIGH);
    delay(irrigation_time);
    digitalWrite(relay_pin, LOW);
    countdown = period;
  }
  countdown--;
  delay(1000);
} 


/*
 *
 */
 
int leds[] = {3, 4, 5, 6, 9, 10, 11};

void setup() {                
  int i;
  for (i=0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int i;
  for (i=0; i < sizeof(leds); i++) {
     digitalWrite(leds[i], HIGH);
     delay(3000);
     digitalWrite(leds[i], LOW);
  }
}

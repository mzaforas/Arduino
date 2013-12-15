/*
 */

#define NUM_LEDS 5
#define UPDATE_PERIOD 50

int leds[NUM_LEDS] = {5, 6, 9, 10, 11};
int current_status[NUM_LEDS] = {0, 0, 0, 0, 0};
long target_status[NUM_LEDS] = {0, 0, 0, 0, 0};
int delta[NUM_LEDS] = {0, 0, 0, 0, 0};
boolean updating = false; 
  
boolean update_status() {
  boolean wrote = false;
  int i;
  for (i=0; i < NUM_LEDS; i++) {
    if (current_status[i] != target_status[i]) {
      current_status[i] = current_status[i] + delta[i];
      analogWrite(leds[i], current_status[i]);
      wrote = true;
    }
  }
  return wrote;
}

void calculate_target() {
  int i;
  for (i=0; i < NUM_LEDS; i++) {
    current_status[i] = target_status[i]; // Set current to supposed reached target
    long first_target = random(0,2);
    if (first_target == 1) {
      first_target = 255;
    }
    target_status[i] = first_target;
    if (target_status[i] > current_status[i]) {
      delta[i] = 1;
    } else {
      delta[i] = -1;
    }
    Serial.print(target_status[i]);
    Serial.print(" ");
    Serial.println(delta[i]);
  }
}

void setup() {
  Serial.begin(9600);
  
  randomSeed(analogRead(0));  

  int i;
  for (i=0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {

  if (updating) {
    updating = update_status();
    delay(UPDATE_PERIOD);
  } else {
    Serial.println("Calculate target");
    calculate_target();
    updating = true;
  }
}

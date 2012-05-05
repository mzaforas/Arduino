/*
  LedOddLamp (LOL)
  Remote Led Lamp Manager
  
  |~6  |~9  |~10 |~11
  |2   |~3  |4   |~5
  
 */

/* MODOS */
#define APAGADO '0'
#define ENCENDIDO_TODO '1'
#define ENCENDIDO_ABAJO '2'
#define ENCENDIDO_ARRIBA '3'
#define APAGADO_PROGRAMADO '4'
#define TEST 't'

char modo = TEST;
int top_pins[] = {6,9,10,11};
int bottom_pins[] = {2,3,4,5};
//int all_pins[] = {2,3,4,5,6,9,10,11};
int all_pins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13}; // debug!
int pwm_pins[] = {3,5,6,9,10,11};
int all_fade[] = {0,0,0,0,0,0,0,0};
int total_pins;
int total_pwm_pins = 6;

/**
 * setup
 */
void setup() {     
  Serial.begin(9600);  
  // initialize the digitals pins as an output.
  total_pins = sizeof(all_pins) / sizeof(int);
  int i;
  for (i=0; i<total_pins; i++) {
    pinMode(all_pins[i],OUTPUT);
  }
}

/**
 * loop
 */
void loop() {
  switch (modo) {
    case APAGADO:
      apagar();
      break;
    case ENCENDIDO_TODO:
      encender();
      break;
    case TEST:
      test();
      break;
    default:
      apagar();
  }
  delay(1000);              // wait for a second
}

/**
 * serial event
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte as integer:
    modo = (char)Serial.read(); 
    Serial.print(">> recibido: ");
    Serial.println(modo);
  }
}

/**
 * apagar
 */
void apagar() {
  Serial.println(">> apagar");
  int i;
  for (i=0; i<total_pins; i++) {
    digitalWrite(all_pins[i],LOW);
  }  
}

/**
 * encender
 */
void encender() {
  Serial.println(">> encender");
  for (int i=0; i<total_pins; i++) {
    digitalWrite(all_pins[i],HIGH);
  }  
}

/**
 *
 */
void test() {
  for (int i=0; i<total_pins; i++) {
    digitalWrite(all_pins[i],HIGH);
    delay(1000);
    digitalWrite(all_pins[i],LOW);
  }  

  for (int i=0; i<total_pins; i++) {
    digitalWrite(all_pins[i],HIGH);
    delay(1000);
  }  
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    for (int i=0; i<total_pwm_pins; i++) {
      analogWrite(pwm_pins[i], fadeValue);
    }
  // wait for 30 milliseconds to see the dimming effect    
  delay(50);                            
  }

  for(int fadeValue = 255 ; fadeValue > 0; fadeValue -=5) { 
    for (int i=0; i<total_pwm_pins; i++) {
      analogWrite(pwm_pins[i], fadeValue);
  }
  // wait for 30 milliseconds to see the dimming effect    
  delay(50);                            
  } 
}

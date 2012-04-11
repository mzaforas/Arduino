#include <SerialLCD.h>
#include <SoftwareSerial.h>

// initialize the library
SerialLCD slcd(11,12);

void setup() {
  // set up
  slcd.begin();
  // Print a message to the LCD.
  slcd.print("Hello World!");
}

void loop() {
  // Turn off the display:
  slcd.noDisplay();
  delay(500);
  
  // Turn on the display:
  slcd.display();
  delay(500);
}


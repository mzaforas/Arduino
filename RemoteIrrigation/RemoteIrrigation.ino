/*
 Remote TCP Arduino Irrigation System
 Manuel Zaforas
*/
 
#include <SPI.h>
#include <Ethernet.h>

int TCP_PORT = 1234;
int RELAY_PIN = 2;
int PERIOD = 6 * 60 * 60; // every 6 hour (in seconds)
int DEFAULT_IRRIGATION_TIME = 10; // seconds

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };
EthernetServer server(TCP_PORT);
int countdown;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  countdown = 0;
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  server.begin();
}

void loop()
{
  /* TCP triggered irrigation */
  int irrigation_time = 0;
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        int n = client.read();
        if (n == 0) {
          break;
        } else {
          irrigation_time = n;
          Serial.print("Irrigation requested: ");
          Serial.print(irrigation_time);
          Serial.println(" seconds");
        }
      }
    }
    client.stop();
    irrigate(irrigation_time);
    countdown = PERIOD;
  }
  
  /* Default periodic irrigation */
  Serial.print("Countdown to next irrigation: ");
  Serial.println(countdown);
  if (countdown == 0) {
    irrigate(DEFAULT_IRRIGATION_TIME);
    countdown = PERIOD;
  }
  countdown--;
  delay(1000);
}

/**
 * Open relay N seconds
 */
void irrigate(int irrigation_time) {
  Serial.print("Irrigating start: ");
  Serial.print(irrigation_time);
  Serial.println(" seconds");
  digitalWrite(RELAY_PIN, HIGH);
  int sleep_time = irrigation_time * 1000;
  delay(sleep_time);
  digitalWrite(RELAY_PIN, LOW);
}

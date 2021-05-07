/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};

int ledpin = 3;


void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
  {
    // some boards need to wait to ensure access to serial over USB
  }
  // initialize the transceiver on the SPI bus
  if (!radio.begin()) 
  {
    Serial.println(F("radio hardware is not responding!!"));
    while(1){} // hold in infinite loop
  }
  
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(ledpin, LOW);
}

void loop() 
{
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  digitalWrite(ledpin, HIGH);
  delay(100);
  digitalWrite(ledpin, LOW);
  Serial.println(text);  
  delay(1000);
}

/*
 * Andre Cleaver
 * May 7th, 2021
 * NRF24L01 Receiver
 * 
 * Modified from * by Dejan Nedelkovski, www.HowToMechatronics.com
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

/*
 * Arduino Uno
 * CE  - 
 * CSN -
 * SCK - 13
 * MO  - 11
 * MI  - 12  
 * IRO - N/A
 * 
 * Arduino Nano
 * If using nano, you might have to switch processor to ATmega328P (Old Bootloader)
 * CE  - 
 * CSN -
 * SCK - 13
 * MO  - 11
 * MI  - 12  
 * IRO - N/A
 * 
 * Layout of NRF24L01
 * ==============
 * |     Vcc Gnd |
 * |     CSN CE  |
 * |     MO  SCK | 
 * |     IRO MI  |
 * ==============
 */

RF24 radio(7, 8); // CE, CSN

// Let these addresses be used for the pair
uint8_t address[][6] = {"Dre01", "Dre02"};

int ledpin = 4; //Using LED to indicate a transmitted message

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
    Serial.println(F("Radio hardware is not responding. Possibly not recieving enough power..."));
    while(1){} // hold in infinite loop
  }
  Serial.println("SimpleTx Starting");

  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(ledpin, LOW);

  //printf_begin();             // needed only once for printing details
  //radio.printDetails();       // (smaller) function that prints raw register values
}

void loop() 
{
  const char text[] = "Hello from GroveBoard!";
  radio.write(&text, sizeof(text));
  digitalWrite(ledpin, HIGH);
  delay(100);
  digitalWrite(ledpin, LOW);
  Serial.println(text);  
  delay(1000);
}

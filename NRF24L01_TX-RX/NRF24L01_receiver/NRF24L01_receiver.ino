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

RF24 radio(7, 8); //Assign pins CE and CSN on the NRF24L01 to the Arduino Board
char data[50] = "";

// Set the address
uint8_t address[][6] = {"Dre01", "Dre02"};

int ledpin = 4; //Using LED to indicate a received message

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
    Serial.println(F("Radio hardware is not responding. Possibly not receiving enough power..."));
    while(1){} // hold in infinite loop
  }
  Serial.println("SimpleRx Starting");

  radio.openReadingPipe(1,address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  
  //printf_begin();             // needed only once for printing details
  //radio.printDetails();       // (smaller) function that prints raw register values
}

void loop() 
{
  uint8_t pipe;
  if (radio.available(&pipe)) 
  {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    digitalWrite(ledpin, HIGH-digitalRead(ledpin));   // Toggle Relay
    Serial.println(text);
  }
}

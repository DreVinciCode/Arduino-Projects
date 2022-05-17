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

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  4;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

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
  digitalWrite(ledPin, LOW);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void TransmitSignal()
{
  const char text[] = "Hello from GroveBoard!";
  radio.write(&text, sizeof(text));
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  Serial.println(text);  
  delay(1000);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) 
  {
    TransmitSignal();
  } 
  else 
  {
    digitalWrite(ledPin, LOW);
  }
}

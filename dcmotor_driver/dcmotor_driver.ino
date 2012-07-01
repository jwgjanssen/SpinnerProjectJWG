//Project 11 - Drive a DC Motor
#include <JeeLib.h>

Port Potmeter (1);
Port Transistor (2);

    // connected to the base of the transistor
int potValue = 0;         // value returned from the potentiometer

void setup() {
  Serial.begin(57600);
  Potmeter.mode(INPUT);
  Transistor.mode(OUTPUT);
}

void loop() {
  // read the potentiometer, convert it to 0 - 255:
  potValue = Potmeter.anaRead() / 4;
  // use that to control the transistor:
  Transistor.anaWrite(potValue);
  Serial.println(potValue);
  delay(250);
}

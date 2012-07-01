/*
* Stepper sketch
*
* stepper is controlled from the serial port.
* a numeric value followed by '+' or '-' steps the motor
*
*
* http://www.arduino.cc/en/Reference/Stepper
*/

#include <JeeLib.h>
//#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 48

Port SteppercoilA1 (1);
Port SteppercoilA3 (2);
Port SteppercoilB1 (3);
Port SteppercoilB3 (4);

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//Stepper stepper(STEPS, 4, 5, 6, 7);  // = JeeNode P1D, P2D, P3D, P4D

int steps = 0;

void setup()
{
  //stepper.setSpeed(30);  // set the speed of the motor to 30 RPMs
  Serial.begin(57600);
  SteppercoilA1.mode(OUTPUT);
  SteppercoilA3.mode(OUTPUT);
  SteppercoilB1.mode(OUTPUT);
  SteppercoilB3.mode(OUTPUT);
}

//Switching sequence Uni-polar drive
// step  A1    A3    B1    B3    A2/B2     CCW  CW
//  1    -                 -       +        A    |
//  2    -           -             +        |    |
//  3          -     -             +        |    |
//  4          -           -       +        |    V


void loop()
{
  while(1) {
    SteppercoilA1.digiWrite(1); SteppercoilA3.digiWrite(0); SteppercoilB1.digiWrite(0); SteppercoilB3.digiWrite(1);
    delay(10);
    SteppercoilA1.digiWrite(1); SteppercoilA3.digiWrite(0); SteppercoilB1.digiWrite(1); SteppercoilB3.digiWrite(0);
    delay(10);
    SteppercoilA1.digiWrite(0); SteppercoilA3.digiWrite(1); SteppercoilB1.digiWrite(1); SteppercoilB3.digiWrite(0);
    delay(10);
    SteppercoilA1.digiWrite(0); SteppercoilA3.digiWrite(1); SteppercoilB1.digiWrite(0); SteppercoilB3.digiWrite(1);
    delay(10);
  }


  /*if ( Serial.available()) {
    char ch = Serial.read();
    
    if(ch >= '0' && ch <= '9'){       // is ch a number?
      steps = steps * 10 + ch - '0';  // yes, accumulate the value
    }
    else if(ch == '+'){
      stepper.step(steps);
      steps = 0;
    }
    else if(ch == '-'){
      stepper.step(steps * -1);
      steps = 0;
    }
    else if(ch == 's'){
      stepper.setSpeed(steps);
      Serial.print("Setting speed to ");
      Serial.println(steps);
      steps = 0;
    }
  }*/
}


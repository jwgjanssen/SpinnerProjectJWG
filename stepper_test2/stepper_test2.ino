#include <Stepper.h>

//How many steps does your motor have
#define STEPS 48

//Start new Stepper class with 48 steps (STEPS defined above) 
//Motor is connected to pins 4, 5, 6 & 7 (=Port 1D, 2D, 3D & 4D on JeeNode)
Stepper stepper(STEPS, 4, 5, 6, 7);

//Create starting position for motor / pot
int previous = 0;

void setup()
{
  //How fast will we try to move the motor
  //If your motor stutters, its too fast so just lower the value
  stepper.setSpeed(180);
}

void loop()
{
  //Read analog 0 (pot) and map it to the range of the motor (=Port 1A on JeeNode)
  int val = map(analogRead(0), 0, 1023, 24, 0);
  //Move motor based off of last recorded position
  stepper.step(val - previous);
  //Store current position 
  previous = val;
}

// Test around calculations of reed pulses of spinning bike
// Last modification: 16mrt2012, Jos Janssen.

#include <JeeLib.h>
#include <Metro.h>

#define DEBUG 1

Port reed_relay (1);
Port pulse_led (2);
int reedData, reedState;
int onceDone = 0;

Metro sampleMetro = Metro(1000);

long rotationMs = 0;
long prevMs = 0; // timestamp of last pulse
long nextMs = 0; // timestamp of newest pulse

int hmh = 0;
//int wheel_diameter_mm = 2100; // = 2,100 meter
int wheel_diameter_mm = 728; // = 0,728 meter



void flashd(Port light) {
    light.digiWrite(1);
    delay(20);
    light.digiWrite(0);
}


void setup() {
    #if DEBUG
      Serial.begin(57600);
      Serial.println("\n[Showing reed-relay data]");
    #endif
    reed_relay.mode(INPUT);
    pulse_led.mode(OUTPUT);
}

  
void loop() {
    // take a reading from the reed-relay 
    reedData = reed_relay.digiRead();
    if ( reedData == 1 ) {
      reedState = 1;
    } else {
      reedState = 0;
      onceDone = 0;
    }
    if ((reedState == 1) && (onceDone == 0)) {
        nextMs = millis();
        rotationMs = nextMs - prevMs;             
        prevMs = nextMs;
        hmh = ((3600000/rotationMs) * wheel_diameter_mm) / 10000;
        flashd(pulse_led);
        onceDone = 1;
    }
    if ( sampleMetro.check() ) {
        #if DEBUG
          Serial.print(rotationMs);
          Serial.print("  =  ");
          Serial.print(hmh/100);
          Serial.print(",");
          Serial.print(hmh%100);
          Serial.println(" KM/h");
        #endif

    }
}

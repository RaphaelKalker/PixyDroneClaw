
#include "Detection.h"
#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include "Signature.h"
#include "Claw.h"


//Shape


//Some needed vars
Pixy pixy;
Claw claw;
Servo servo;

int timer = 1000;
const uint8_t frames = 25;
uint16_t blocks;
uint8_t len;
int i = 0;
uint8_t btnPin = 13;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting pixy\n");
  
  pixy.init();
  claw.initClaw();
}

void loop() {

  static int i = 0;
  blocks = pixy.getBlocks();
  len = sizeof(blocks);
  char buf[32];

  if (blocks && Detection::isReadyToScan()) {

    if (++i % frames == 0) {
      sprintf(buf, "Detected %d objects: \n", blocks);
      Serial.print(buf);

      //Print Informations about detected objects
      for (int j = 0; j < blocks; j++) {
        sprintf(buf, " block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();

        //confirm target based on centered object and size
        if (Detection::isObjectInRange(pixy.blocks[j])) {
			Serial.println("Object is in range");
			claw.engage();
			Serial.println("done");
        }
      }
    }
  }

  /*
  * get current block on screen and create a signature for comparison later
  */
  }






//pixy.setLED(r,g,b)
//pixy.setBrightness()





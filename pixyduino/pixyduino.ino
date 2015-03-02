#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include "Signature.h"
#include "Claw.h"
#include "Detection.h"

Pixy pixy;
Claw claw;
Servo servo;

int timer = 1000;
const uint8_t frames = 25;
uint16_t blocks;
uint8_t len;

void setup() {
  Serial.begin(9600);
  
  pixy.init();
  claw.initClaw();

  Serial.println("Start detection... \n");
}

void loop() {

  static int i = 0;
  blocks = pixy.getBlocks();
  len = sizeof(blocks);
  char buf[32];

  if (blocks && claw.isReady()) {
    if (++i % frames == 0) {
      sprintf(buf, "Detected %d objects: \n", blocks);
      Serial.print(buf);

      //Print Informations about detected objects
      for (int j = 0; j < blocks; j++) {
        sprintf(buf, " block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();

        //confirm target based on some thresholds
        if (Detection::isObjectInRange(pixy.blocks[j])) {
			Serial.println("Object is in range");
			claw.engage();
			Serial.println("done");
        }
      }
    }
  }
  else {
	  if (claw.getState() == claw.OPEN)
	  {
		  Serial.println("did not go to loop");
	  }
	  
	  
  }

  /*
  * get current block on screen and create a signature for comparison later
  */
  //TODO
  }

//pixy.setLED(r,g,b)
//pixy.setBrightness()





#include "UltraSonicSensor.h"
#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include "Signature.h"
#include "Claw.h"
#include "Detection.h"
#include "UltraSonicSensor.h"

Pixy pixy;
Claw claw;
Servo servo;
UltraSonicSensor ultraSonic;

int timer = 1000;
const uint8_t frames = 25;
uint16_t blocks;
uint8_t len;

void setup() {
	Serial.begin(9600);

	pixy.init();
	claw.initClaw();
	claw.testClaw(Claw::OPEN);
//	Detection::init();
	ultraSonic.init();

	Serial.println("Start detection... \n");
}

void loop() {

	if (Detection::handleBtnPressed(2)) {
		//		claw.toggleClaw();
	}

	static int i = 0;
	blocks = pixy.getBlocks();
	len = sizeof(blocks);
	char buf[32];



	//  Detection::handlePixyBlocks();
//	ultraSonic.printDistance();

	if (blocks && claw.isReady()) {
		if (++i % frames == 0) {
			sprintf(buf, "Detected %d objects: \n", blocks);
			Serial.print(buf);

			for (int j = 0; j < blocks; j++) {
				sprintf(buf, " block %d: ", j);
				Serial.print(buf);
				pixy.blocks[j].print();

				if (Detection::isObjectCentered(pixy.blocks[j]))
				{
					if (ultraSonic.isAboveGround())
					{
						
					}

					Serial.println("Object is in range");
					claw.engage();
					Serial.println("done");
				}
			}
		}
	} else {


	}
}




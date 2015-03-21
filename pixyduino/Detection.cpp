#include "Detection.h"
#include "Claw.h"
//
//
boolean Detection::isObjectCentered(Block block) {

	/*
	* check if item is centered based on the some target thresholds for the object's size
	* this should ignore false positives for objects of the wrong size
	*play around with the target values
	*/

	if (block.x > TARGET_X1 && block.x < TARGET_X1 + block.width
		&& block.y > TARGET_Y1 && block.y < TARGET_Y1 + block.height) {
		char buffalo[128];
		sprintf(buffalo, "Object is centered -> Sig: %d, xLeft: %d, xRight: %d, yTop: %d, yBottom: %d",
			block.signature, block.x, block.x + block.width, block.y, block.y + block.height);
		Serial.println(buffalo);
		return true;
	}
	return false;
	//  return block.width > targetWidth || block.height > targetHeight;
}
//
//	void Detection::handlePixyBlocks() {
//
//		static int i = 0;
//		blocks = pixy.getBlocks();
//		len = sizeof(blocks);
//		char buf[32];
//
//		if (blocks && claw.isReady()) {
//			if (++i % frames == 0) {
//				sprintf(buf, "Detected %d objects: \n", blocks);
//				Serial.print(buf);
//
//				//Print Informations about detected objects
//				for (int j = 0; j < blocks; j++) {
//					sprintf(buf, " block %d: ", j);
//					Serial.print(buf);
//					pixy.blocks[j].print();
//
//					//confirm target based on some thresholds
//					if (Detection::isObjectInRange(pixy.blocks[j])) {
//						Serial.println("Object is in range");
//						claw.engage();
//						Serial.println("done");
//					}
//				}
//			}
//		} else {
//
//
//		}
//	}
//
boolean Detection::handleBtnPressed(uint8_t btnPin) {
	if (digitalRead(btnPin) == HIGH) {
		Serial.println("Pressed");
	}
}
//
//
//

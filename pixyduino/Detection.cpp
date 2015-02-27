#include "Detection.h"
#include "Claw.h"


	boolean Detection::isObjectInRange(Block block) {

		/*
		* check if item is centered based on the some target thresholds for the object's size
		* this should ignore false positives for objects of the wrong size
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


	boolean Detection::isReadyToScan(){
		return 9 == Claw::OPEN;
	}


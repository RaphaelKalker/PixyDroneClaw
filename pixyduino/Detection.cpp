#include "Detection.h"
#include "Claw.h"
//
//
boolean Detection::isObjectCentered(Block block) {

	/*
	* check if item is centered based on the some target thresholds for the object's size
	* this should ignore false positives for objects of the wrong size
	*play around with the target values
	* block.x = CENTER X
	* block.y = CENTER Y
	*servo code for robot use 
	//X_CENTER - pixy.blocks[trackedBlock].x;
	//pixy.blocks[trackedBlock].y - Y_CENTER
	*/

	if (block.x > TARGET_X1 && block.x < TARGET_X1 + block.width*SCALING_FACTOR +10
		&& block.y > TARGET_Y1 && block.y < TARGET_Y1 + block.height*SCALING_FACTOR +10) {
		char buffalo[128];
		sprintf(buffalo, "Object is centered -> Sig: %d, xCenter: %d, xRight: %d, yTop: %d, yBottom: %d",
			block.signature, block.x, block.x + block.width, block.y, block.y + block.height);
		Serial.println(buffalo);
		return true;
	}
	return false;
}

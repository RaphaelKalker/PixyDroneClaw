#ifndef _DETECTION_h
#define _DETECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include <Pixy.h>
#else
	#include "WProgram.h"
#endif

class Detection {
	protected:
	static const uint8_t targetWidth = 150;
	static const uint8_t targetHeight = 150;
	static const uint8_t TARGET_X1 = 160;
	static const uint8_t TARGET_X2 = 300;
	static const uint8_t TARGET_Y1 = 100;
	static const uint8_t TARGET_Y2 = 300;
	static const float SCALING_FACTOR = 1.0;

	public:
	static boolean isObjectCentered(Block block);
	static void init();
};

#endif


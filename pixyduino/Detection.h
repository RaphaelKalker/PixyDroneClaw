#ifndef _DETECTION_h
#define _DETECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include <Pixy.h>
	#include <SPI.h>
	#include <Servo.h>
	#include "Signature.h"
	#include "Claw.h"
	#include "Detection.h"
#else
	#include "WProgram.h"
#endif

class Detection {
	protected:
	static const uint8_t targetWidth = 150;
	static const uint8_t targetHeight = 150;
	static const uint8_t TARGET_X1 = 150;
	static const uint8_t TARGET_X2 = 300;
	static const uint8_t TARGET_Y1 = 100;
	static const uint8_t TARGET_Y2 = 300;
	Pixy pixy;
//	static const int timer = 1000;
//	static const uint8_t frames = 25;
//	static uint16_t blocks;
//	static uint8_t len;
//	static Pixy pixy;
//	static Claw claw;
//	static Servo servo;

	public:
	static boolean isObjectCentered(Block block);
//	static void handlePixyBlocks();
	static boolean handleBtnPressed(uint8_t btnPin);
	void handlePixy();
	static void init();
};

#endif


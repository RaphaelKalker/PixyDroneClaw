#include <Pixy.h>

#ifndef _SIGNATURE_h
#define _SIGNATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Signature
{
 public:
	uint16_t x1 = 150;
	uint16_t x2 = 300;
	uint16_t y1 = 100;
	uint16_t y2 = 300;
	uint16_t width;
	uint16_t height;

	Signature (Block *block);

	void calibrate(Block *block);
};

#endif
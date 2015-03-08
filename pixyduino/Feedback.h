// Feedback.h

#ifndef _FEEDBACK_h
#define _FEEDBACK_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <Servo.h>
#else
#include "WProgram.h"
#endif

class FeedbackClass {
	protected:
	uint16_t highPulseWidth;
	uint16_t lowPulseWidth;
	uint16_t highPulseFeedback;
	uint16_t lowPulseFeedback;
	uint8_t angleFrom;
	uint8_t angleTo;
	float angleRead; //in rads
	float angleWrite;
	uint16_t feedback; //the feedback reading that comes back from the servo


	//not used
	int h;
	int t;
	int Button = 2;
	int e = 1;
	// int angle;
	int btwReadings = 20; //delay between readings
	int whlReading = 3; //delay time between analog readings of internal pot
	public:
	void init();
};

extern FeedbackClass Feedback;

#endif


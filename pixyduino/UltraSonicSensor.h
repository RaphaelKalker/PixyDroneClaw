// UltraSonicSensor.h

#ifndef _ULTRASONICSENSOR_h
#define _ULTRASONICSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class UltraSonicSensor {
	private:
	long microsecondsToInches(long microseconds);
	long microsecondsToCentimeters(long microseconds);
	uint8_t pingPin;
	enum PINS
	{
		VCC = 6,
		TRIG = 3,
		ECHO = 4,
		GRD = 5
	};
	boolean enableLogging;


	public:
	void init();
	void enableLog(boolean enableLoggingDistance);
	long getDistance();
	void printDistance();
	boolean isAboveGround();
};


#endif


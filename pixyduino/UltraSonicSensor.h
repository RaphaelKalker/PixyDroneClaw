// UltraSonicSensor.h

#ifndef _ULTRASONICSENSOR_h
#define _ULTRASONICSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class UltraSonicSensor {
	protected:
	long microsecondsToInches(long microseconds);
	long microsecondsToCentimeters(long microseconds);
	uint8_t pingPin;
	boolean enableLogging;


	public:
	void init(uint8_t pin);
	void enableLog(boolean enableLoggingDistance);
	long getDistance();
};


#endif


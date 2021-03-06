#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <Servo.h>
#include "ContinuousRotationServo.h"
#else
#include "WProgram.h"
#endif

class Claw {
	private:
	long const MAX_ROTATION_TIME = 1000;
	double const VMIN = .40;
	double const VMAX = 1.86;
	boolean test = false;
	uint8_t const MAX_ANGLE_READINGS = 5;

	ContinuousRotationServo servoContinuous;
	Servo servoRotational;

	enum ServoPin {
		pin10 = 10,
		pin2 = 2,
		pin9 = 9
	};

	// open and close are reversed due to orientation of motor
	// closed is set to 3 instead of 0 to avoid excess current draw.
	enum Position {
		open = 180,
		closed = 3
	};

	unsigned long mapAngleDelay(uint8_t angle);
	float closeClaw(uint8_t);

	public:
	enum State {
		OPEN,
		OPENING,
		CLOSED,
		CLOSING,
		UNKNOWN
	};

	State state;

	void initClaw();
	void setState(Claw::State s);
	Claw::State getState();
	boolean engage();
	boolean openClaw();
	boolean closeClaw();
	boolean isReady();
	void testClaw(State desiredState);
	uint16_t readAngle(uint16_t inputAngle);
	void calibrateVoltageToAngle(uint16_t inputAngle);
	void calibrate();
	void toggleClaw();

};
#endif





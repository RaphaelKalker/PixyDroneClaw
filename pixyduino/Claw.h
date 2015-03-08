#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include <Servo.h>
	#include "ContinuousRotationServo.h"
#else
	#include "WProgram.h"
#endif

class Claw
{
	private:
		boolean test = false;
		ContinuousRotationServo servoContinuous;
		Servo servoRotational;

		enum ServoPin {
			pin10 = 10,
			pin2 = 2,
			pin9 = 9
		};
		
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
};
#endif





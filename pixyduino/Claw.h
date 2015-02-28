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
		const uint8_t motorPin = 9;
		const uint8_t motorPinClose = 6;
		boolean test = false;
		Servo servo1;
                ContinuousRotationServo servo2;
                ContinuousRotationServo servo3;

		enum ServoPosition {
			position1 = 100,
			position2 = 160,
			position3 = 110,
			defaultPosition = 180,
                        spyderClose = 100,
                        jordanClose = 100
		};

		enum ServoPin {
			pin1 = 4,
			pin2 = 5,
			pin3 = 6
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
};
#endif





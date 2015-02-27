#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include <Servo.h>
#else
	#include "WProgram.h"
#endif

class Claw
{
	private:
		const uint8_t motorPin = 10;
		const uint8_t motorPinClose = 6;
		boolean test = false;
		Servo servo;
		
	 public:
		 enum State {
			 OPEN,
			 OPENING,
			 CLOSED,
			 CLOSING,
			 UNKNOWN
		 };

		static State state;
	 
		void initClaw();
		static void setState(Claw::State s);
		static Claw::State getState();
		
		boolean engage();
		boolean openClaw();
		boolean closeClaw();
};


#endif





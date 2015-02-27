#include <Arduino.h>
#include <Servo.h>
#include "Claw.h"	

	void Claw::initClaw() {
		Serial.println("Initializing Claw!");
		pinMode(motorPin, OUTPUT);
		pinMode(motorPinClose, OUTPUT);

		/*
		Setup the servo motor here
		*/

	}

	Claw::State Claw::getState() {
		return state;
	}
	 
	void Claw::setState(State s) {
		state = s;
	}

	boolean Claw::engage() {
		Serial.println("Engaging claw of fury....");
		//Claw::state = OPENING;
		//try to open claw if successful we should clench onto object
		if (openClaw()) {

			//this will delay until open, best to have fallback
			closeClaw();

			//reset the whole thing
			delay(1000);
			initClaw();
		}
		else {
			Serial.print("FAILURE");
		}
		return true;
	}

	boolean release() {
		Serial.println("Releasing claw of fury....");
		return true;
	}

	boolean Claw::openClaw() {
		if (test) {
			//state = OPEN;
			return false;
		}
		Serial.println("Opening claw...");
		//setState(OPENING);
		//digitalWrite(motorPin, HIGH);
		delay(1000);
		digitalWrite(motorPin, LOW);
		//setState(OPEN);

		/*if (state == OPEN) {
			return true;
		}*/

		return false;
	}

	boolean Claw::closeClaw() {
		if (test) {
			return true;
		}

		Serial.println("Closing claw...");
		//state = CLOSING;
		digitalWrite(motorPinClose, HIGH);
		delay(1000);
		//state = CLOSED;
		digitalWrite(motorPinClose, LOW);

		//if (state == CLOSED) {
		//	return true;
		//}

		return false;
	}
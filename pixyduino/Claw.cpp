#include <Arduino.h>
#include <Servo.h>
#include "Claw.h"	
#include "ContinuousRotationServo.h"

	void Claw::initClaw() {
		Serial.println("Initializing Claw!");
		pinMode(motorPin, OUTPUT);
		pinMode(motorPinClose, OUTPUT);

		/*
		Setup the servo motor here
		*/
		servo1.attach(Claw::pin1);
                servo2.begin(pin2);
                servo3.begin(pin3);

	}

	Claw::State Claw::getState() {
		return state;
	}
	 
	void Claw::setState(State s) {
		state = s;
	}

	boolean Claw::engage() {
		Serial.println("Engaging claw of fury....");
		
                //claw servo
                servo1.write(Claw::position3);

                //spyder servo
                servo2.rotate(Claw::spyderClose);

                //jordan servo
                servo3.rotate(Claw::jordanClose);

		//try to close claw if successful we shall proceed
		if (closeClaw()) {
			//switch off camera/conserve power?

			//reset the whole thing
			openClaw();
			delay(1000);
			initClaw();
		}
		else {
			Serial.print("could not close claw.");
			setState(UNKNOWN);
		}
		return true;
	}

	boolean release() {
		Serial.println("Releasing claw of fury....");
		return true;
	}

	boolean Claw::openClaw() {
		if (test) {
			setState(OPEN);
			return false;
		}
		//check if we can actually open

		Serial.println("Opening claw...");
		setState(OPENING);
		digitalWrite(motorPin, HIGH);
		delay(1000);
		digitalWrite(motorPin, LOW);
		setState(OPEN);

		//maybe it failed? we should handle that
		if (state != OPEN) {
			setState(UNKNOWN);
			return false;
		}

		return true;
	}

	boolean Claw::closeClaw() {
		if (test) {
			return true;
		}

		//Add servo logic here
		servo1.write(Claw::position1);
		delay(10*1000);
		servo1.write(defaultPosition);

		Serial.println("Closing claw...");
		state = CLOSING;
		digitalWrite(motorPinClose, HIGH);
		delay(1000);
		state = CLOSED;
		digitalWrite(motorPinClose, LOW);

		if (state == CLOSED) {
			return true;
		}

		return false;
	}

	boolean Claw::isReady() {
		return state == OPEN;
	}

#include <Arduino.h>
#include <Servo.h>
#include "Claw.h"	
#include "ContinuousRotationServo.h"

	void Claw::initClaw() {
		Serial.println("Initializing Claw!");

		/*
		Setup the servo motor here
		*/

//		servoContinuous.begin(10);
		servoRotational.attach(9);
//		servoRotational
		
	}

	Claw::State Claw::getState() {
		return state;
	}
	 
	void Claw::setState(State s) {
		state = s;
	}

	boolean Claw::engage() {
		Serial.println("Engaging claw of fury....");

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
		delay(1000);
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

		Serial.println("Closing claw...");
		state = CLOSING;

//		for (int i = 0; i < 100; i++)
//		{
//			servoContinuous.rotateLeft(100);
//			servoContinuous.delayServo(20); //expects new instructions after 20 microsends
//		}

		delay(1000);

		state = CLOSED;

		if (state == CLOSED) {
			return true;
		}

		return false;
	}

	boolean Claw::isReady() {
		return state == OPEN;
	}

	void Claw::testClaw(State desiredState)
	{
		if (servoRotational.attached())
		{
			Serial.println("You should have fucking opened the claw");
			delay(2000);
//			servoRotational.write(0);

		}
//		for (int i = 0; i < 100; i++)
//		{
//			servoContinuous.rotateLeft(i);
//			delay(20);
//		}

	}

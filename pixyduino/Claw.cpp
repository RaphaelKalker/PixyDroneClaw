#include <Arduino.h>
#include <Servo.h>
#include "Claw.h"	
#include "ContinuousRotationServo.h"




void Claw::initClaw() {
	Serial.println("Initializing Claw!");
	servoRotational.attach(9);
	openClaw();
}

Claw::State Claw::getState() {
	return state;
}

void Claw::setState(State s) {
	state = s;

	if (s == CLOSED)
	{
		delay(100);
	}
}

boolean Claw::engage() {
	Serial.println("Engaging claw of fury....");

	//try to close claw if successful we shall proceed
	if (closeClaw(-1)) {
		//switch off camera/conserve power?

		//reset the whole thing
		delay(8000);
		openClaw();

		initClaw();
	} else {
		Serial.print("could not close claw.");
		setState(UNKNOWN);
	}
	return true;
}

boolean Claw::openClaw() {
	Serial.println("Opening claw...");
	readAngle(-1);
	setState(OPENING);
	servoRotational.write(open);
	setState(OPEN);
	return true;
}

boolean Claw::closeClaw() {
//	
//	Serial.println("Closing claw...");
//	setState(CLOSING);
//	servoRotational.write(closed);
//	setState(CLOSING);
//	readAngle();
//	return true;
}

unsigned long Claw::mapAngleDelay(uint8_t angle)
{
	//TODO: create mapping for angle delay
	return map(angle, open, closed, 1, 1000);
}

float Claw::closeClaw(uint8_t desiredAngle) {
	Serial.println("Closing claw...");

	/* 
	* Simple close command, no need for feedback
	* This can be used for the override button
	*/
	if (desiredAngle != -1) {
		
		desiredAngle = closed;
//		servo.write(desiredAngle);

//		return readAngle();
	}

	/*
	* If desiredAngle is not -1, we shall proceed with the feedback approach
	* Continously try to close, but check the feedback voltage from the potentiometer.
	* If there is no change after a few readings we can assume that claw has attached 
	* itself on an object.
	*/

	
	setState(CLOSING);
	uint8_t angle1 = 0;
	uint8_t angle2 = 0;
	long elapsedTime = 0;
	servoRotational.write(desiredAngle);
	
	while (true)
	{
		angle1 = readAngle(-1);
		delay(20);
		angle2 = readAngle(-1);
		Serial.print("\nDifference in angle: ");
		Serial.print(angle1 - angle2);

		if (angle1 == angle2)
		{
			servoRotational.write(angle1);
			setState(CLOSED);
			return angle1;
		}
		else if (elapsedTime > MAX_ROTATION_TIME)
		{
			Serial.println("elapsed time has reached threshold");
		}
	}
}
		

boolean Claw::isReady() {
	return state == OPEN;
}

float Claw::readAngle(uint16_t inputAngle) {
	//Curve fit polynomial function
	
	int sensorValue = analogRead(A0);
	float voltage = sensorValue * (5 / 1023.0);
	uint16_t angle = 113.6*voltage - 44.6;
	Serial.print("Input Angle: ");
	Serial.print(inputAngle);
	Serial.print("\tFeedback: ");
	Serial.print(voltage);
	Serial.print("V");
	Serial.print("\tAngle: ");
	Serial.print(angle);
	Serial.print("\n");
	return voltage;
}

void Claw::calibrateVoltageToAngle(uint16_t inputAngle)
{
	int sensorValue = analogRead(A0);
	float voltage = sensorValue * (5 / 1023.0);
	uint16_t angle = 113.6*voltage - 44.6;
	Serial.print("Input Angle: ");
	Serial.print(inputAngle);
	Serial.print("\tFeedback: ");
	Serial.print(voltage);
	Serial.print("V");
	Serial.print("\tAngle: ");
	Serial.print(angle);
	Serial.print("\n");
}

void Claw::toggleClaw() {
	if (state == OPEN)
		closeClaw(-1);
	else if (state == CLOSED)
		openClaw();
	else
		Serial.println("Unknown state when pressing button");
}


void Claw::testClaw(State desiredState) {
	Serial.println("Testing Claw...");

	/* Test open close*/
//	for (int i = 0; i < 5; i++)
//	{
//		servoRotational.write(open);
//		delay(4000);
//		readAngle(open);
//		servoRotational.write(closed);
//		delay(4000);
//		readAngle(closed);
//	}

	int a = open;
	boolean up;
	boolean down;
	while (true)
	{
		delay(2000);
		closeClaw(a);
		delay(2000);
		calibrateVoltageToAngle(a);
		a += 5;

		if (a > 180)
		{
			break;
			
		}
	}
	a = 180;
	while (true) {
		delay(2000);
		servoRotational.write(a);
		delay(2000);
		calibrateVoltageToAngle(a);
		a -= 5;

		if (a < 0) {
			break;

		}

	}


//	servoRotational.write(0);
//	delay(4000);
//	readAngle();
//	int degrees = 0;
//	while (true) {
//		Serial.print("\nWriting");
//		Serial.print(degrees);
//		Serial.print(" degrees.   ");
//		servoRotational.write(degrees); //.4
//
//		delay(2000);
//		readAngle();
//
//		degrees += 30;
//		if (degrees > 180) {
//			degrees = 0;
//
//		}
//
//	}
	//		servoRotational.write(closed);
	//		if (servoRotational.attached())
	//		{
	//			Serial.println("You should have fucking opened the claw");
	//			int count = 0;
	//			while (false)
	//			{
	//				count++;
	//				servoRotational.write(180);
	//				delay(1000);
	//				servoRotational.write(3);
	//				delay(1000);
	//				servoRotational.write(open);
	//				if (count == 10)
	//				{
	//					break;
	//				}
	//
	//			}
	//			//delay(2000);
	//			//servoRotational.write(-90);
	//
	//		}
	//		for (int i = 0; i < 100; i++)
	//		{
	//			servoContinuous.rotateLeft(i);
	//			delay(20);
	//		}

}

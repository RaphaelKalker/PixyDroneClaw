#include <Arduino.h>
#include <Servo.h>
#include "Claw.h"	
#include "ContinuousRotationServo.h"




void Claw::initClaw() {
	Serial.println("Initializing Claw!");
	servoRotational.attach(9);
	openClaw();
	delay(3000);
	//testClaw(OPEN);
//	calibrate();
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
	delay(1000);
	Serial.println("OPEN");
	return true;
}

boolean Claw::closeClaw() {
	
	Serial.println("Closing claw...");
	setState(CLOSING);
	servoRotational.write(closed);
	setState(CLOSED);
	Serial.println("CLOSED");
	return true;
}

unsigned long Claw::mapAngleDelay(uint8_t angle)
{
	//TODO: create mapping for angle delay
	return map(angle, open, closed, 1, 1000);
}

float Claw::closeClaw(uint8_t desiredAngle) {
	

	/* 
	* Simple close command, no need for feedback
	* This can be used for the override button
	*/
	if (desiredAngle == -1) {
		
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
	Serial.print("\nClosing claw with angle: ");
	Serial.print(desiredAngle);
	servoRotational.write(desiredAngle);
	
	int count = 1;
	uint8_t diff = 0;
	uint8_t sums = 0;
	int samples = 0;
	while (count++ < 6)
	{
		angle1 = readAngle(desiredAngle);
		delay(1000);
		angle2 = readAngle(desiredAngle);
		Serial.print("\nDifference in angle: ");
		diff = abs(angle1 - angle2);
		Serial.print(diff);
		Serial.print("\n Correct Angle: ");
		Serial.print(angle1);

		//only consider differences less than 5
		if (diff < 5)
		{
			
			samples++;
			sums+= diff;
//			Serial.print("\nSamples: ");
//			Serial.print(samples);
		}
		
//
//		if (angle1 == angle2)
//		{
//			servoRotational.write(angle1);
//			setState(CLOSED);
//			return angle1;
//		}
//		else if (elapsedTime > MAX_ROTATION_TIME)
//		{
//			Serial.println("elapsed time has reached threshold");
//		}
	}
	Serial.print("\nSamples: ");
	Serial.print(samples);
	Serial.print("\nSums: ");
	Serial.print(sums);
	if (samples < 1)
	{
		//no samples taken, avoid dividing by zero.
	} 
	else
	{
		Serial.print("\n Offset was found to be: ");
		Serial.print(sums/samples);
		Serial.print("\n Correct Angle: ");
		Serial.print(angle1);
		int OFFSET = 25; //THERE IS SOME OFFSET SHIT GOING ON HERE
		servoRotational.write(angle1 - OFFSET);

	}
	setState(CLOSED);
	delay(1000);
	Serial.println("CLOSED");
	return angle1;
	
}
		

boolean Claw::isReady() {
	return state == OPEN;
}

uint16_t Claw::readAngle(uint16_t inputAngle) {
	//Curve fit polynomial function
	
	int sensorValue = analogRead(A0);
	float voltage = sensorValue * (5 / 1023.0);
	uint16_t angle = 113.6*voltage - 44.6;
//	Serial.print("Input Angle: ");
//	Serial.print(inputAngle);
//	Serial.print("\tFeedback: ");
//	Serial.print(voltage);
//	Serial.print("V");
//	Serial.print("\tAngle: ");
//	Serial.print(angle);
//	Serial.print("\n");
	return angle;
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

void Claw::calibrate()
{
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
}

void Claw::toggleClaw() {
	if (state == OPEN)
		closeClaw();
	else if (state == CLOSED)
		openClaw();
	else
		Serial.println("Unknown state when pressing button");
}


void Claw::testClaw(State desiredState) {
	Serial.println("Testing Claw...");
	closeClaw(-1);
//	int count = 100;
//	while (true)
//	{
//		count++;
//		delay(1000);
//		readAngle(150);
//		if (count > 150)
//		{
//			break;
//		}
//	}

	
}

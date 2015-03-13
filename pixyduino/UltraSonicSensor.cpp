#include "Arduino.h"
#include "UltraSonicSensor.h"

void UltraSonicSensor::init() {
	//	pinMode(VCC, OUTPUT);
	//	pinMode(GRD, OUTPUT);
}

void UltraSonicSensor::enableLog(boolean enableLoggingDistance) {
	this->enableLogging = enableLoggingDistance;
}

boolean UltraSonicSensor::isAboveGround()
{
	return getDistance() < 10;
}


long UltraSonicSensor::getDistance() {
	pinMode(TRIG, OUTPUT);
	digitalWrite(TRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(5);
	digitalWrite(TRIG, LOW);

	pinMode(ECHO, INPUT);
	long distance = microsecondsToCentimeters(pulseIn(ECHO, HIGH));

	delay(100);
	return distance;

}

void UltraSonicSensor::printDistance() {
	Serial.print("\nDistance: ");
	Serial.print(getDistance());
	Serial.print("cm");
}


long UltraSonicSensor::microsecondsToInches(long microseconds) {
	// According to Parallax's datasheet for the PING))), there are
	// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
	// second).  This gives the distance travelled by the ping, outbound
	// and return, so we divide by 2 to get the distance of the obstacle.
	// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
	return microseconds / 74 / 2;
}

long UltraSonicSensor::microsecondsToCentimeters(long microseconds) {
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}



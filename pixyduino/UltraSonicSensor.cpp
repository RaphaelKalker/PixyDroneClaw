#include "Arduino.h"
#include "UltraSonicSensor.h"

void UltraSonicSensor::init(uint8_t pin) {
	this->pingPin = pin;
	
}

void UltraSonicSensor::enableLog(boolean enableLoggingDistance)
{
	this->enableLogging = enableLoggingDistance;
}


long UltraSonicSensor::getDistance() {
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);
	pinMode(pingPin, INPUT);

	long distance = microsecondsToCentimeters(pulseIn(pingPin, HIGH));

	if (enableLogging) {
		Serial.println(distance);
	}
	delay(100);
	return distance;

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



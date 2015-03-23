#include "Arduino.h"
#include "UltraSonicSensor.h"

void UltraSonicSensor::init() {
//	pinMode(VCC, OUTPUT);
//	pinMode(GRD, OUTPUT);
//	pinMode(TRIG, OUTPUT);
}

void UltraSonicSensor::enableLog(boolean enableLoggingDistance) {
	this->enableLogging = enableLoggingDistance;
}

boolean UltraSonicSensor::isAboveGround()
{
	long distance = getDistance();
	//auto true if distance is 0 as in sensor is screwed
	return distance < 10 && distance > 0;
}


long UltraSonicSensor::getDistance() {
	long duration;

	// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	pinMode(3, OUTPUT);// attach pin 3 to Trig
	digitalWrite(3, LOW);
	delayMicroseconds(2);
	digitalWrite(3, HIGH);
	delayMicroseconds(5);
	digitalWrite(3, LOW);

	pinMode(4, INPUT);//attach pin 4 to Echo
	duration = pulseIn(4, HIGH);
	long distance = microsecondsToCentimeters(duration);

	delay(10);
	return distance;

}

void UltraSonicSensor::printDistance() {
	Serial.print("\nDistance: ");
	Serial.print(getDistance());
	delay(100);
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



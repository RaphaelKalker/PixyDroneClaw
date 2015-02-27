
#include <Arduino.h>
#include "Test.h"

Test *t;


/*
Turns on an LED on for one second, then off for one second, repeatedly.
*/

void setup()
{
	Serial.begin(9600);



	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(19, OUTPUT);
}


void loop()
{
	//Serial.println("Hello world!");

	t->printshit();
	// set the LED off
}

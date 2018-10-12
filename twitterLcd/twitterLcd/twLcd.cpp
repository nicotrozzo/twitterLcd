#include "twLcd.h"

#define MAX_SPEED	5
#define MIN_SPEED	1
#define DEFAULT_SPEED 3

twLcd::twLcd(basicLCD* dispPointer)
{
	currentSpeed = DEFAULT_SPEED;
	tickCount = 0;
	lcd = dispPointer;
	twitIndex = 0;

}


twLcd::~twLcd()
{


}

void twLcd::showAgain()
{


}
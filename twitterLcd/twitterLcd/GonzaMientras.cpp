#include "twLcd.h"

void twLcd :: showNextTwit()
{
	twitIndex++;
	tickCount = 0;
	currentTwit = list[twitIndex].text;
	currentTwitData = list[twitIndex].data;
}

void twLcd::showPreviousTwit()
{

}
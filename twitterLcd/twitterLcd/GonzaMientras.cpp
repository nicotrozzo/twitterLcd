#include "twLcd.h"

void twLcd :: showNextTwit()
{
	twitIndex++;								//aumento el twit por el que vamos
	showTwit();
}

void twLcd :: showPreviousTwit()
{
	twitIndex--;								//disminuyo la cuenta del twit por el que vamos
	showTwit();
}

void twLcd::showAgain()
{
	showTwit();
}

void twLcd::showTwit()
{
	tickCount = 0;								//Reinicio el timer
	currentTwit = list[twitIndex].text;
	currentTwitData = list[twitIndex].data;
}
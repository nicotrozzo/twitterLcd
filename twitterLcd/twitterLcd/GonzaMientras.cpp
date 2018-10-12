#include "twLcd.h"

void twLcd :: showNextTwit()
{
	if (twitIndex < totalTwits)
	{
		twitIndex++;								//aumento el twit por el que vamos
	}
	showTwit();
}

void twLcd::showAgain()
{
	showTwit();
}

void twLcd :: showPreviousTwit()
{
	if (twitIndex > 0)
	{
		twitIndex--;								//disminuyo la cuenta del twit por el que vamos
	}
	showTwit();
}

void twLcd::incSpeed()
{
	if (currentSpeed < MAX_SPEED)
	{
		currentSpeed++;
	}
}

void twLcd::decSpeed()
{
	if (currentSpeed == MIN_SPEED)
	{
		currentSpeed--;
	}
}

void twLcd::closeLcd()
{
	lcd->lcdClear;
}


void twLcd::showTwit()
{
	tickCount = 0;								//Reinicia el timer
	currentTwit = userName + ': - ' + list[twitIndex].text + ' ';
	currentTwitData = list[twitIndex].data;
	lcd->lcdClear;
	(*lcd) << currentTwitData.c_str();
	lcd->lcdSetCursorPosition[2][1];
	(*lcd) << currentTwit.c_str();
}



twLcd::~twLcd()
{
	
}
#include "twLcd.h"

#define MAX_SPEED	5
#define MIN_SPEED	1
#define DEFAULT_SPEED 3

twLcd::twLcd(basicLCD* dispPointer, unsigned char totalTwits_, vector<twit> list_)
{
	currentSpeed = DEFAULT_SPEED;
	tickCount = 0;
	lcd = dispPointer;
	totalTwits = totalTwits_;
	list = list_;
	parseText();							//falta parsear fecha y hora

	twitIndex = 0;
	showAgain();
}


void twLcd::showNextTwit()
{
	if (twitIndex < totalTwits)
	{
		twitIndex++;							//aumento el twit por el que vamos
	}
	showTwit();
}

void twLcd::showAgain()
{
	showTwit();
}

void twLcd::showPreviousTwit()
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
	if (currentSpeed > MIN_SPEED)
	{
		currentSpeed--;
	}
}

void twLcd::closeLcd()
{
	lcd->lcdClear();
}

void twLcd::showTwit()
{
	tickCount = 0;								//Reinicia el timer
	currentTwit = userName + ": - " + list[twitIndex].text + ' ';
	currentTwitData = list[twitIndex].data;
	lcd->lcdClear();
	(*lcd) << currentTwitData.c_str();
	lcd->lcdSetCursorPosition({ 2,1 });			//Llevo cursor a la posicion 1 de el segundo renglon
	(*lcd) << currentTwit.c_str();
}

void twLcd::parseText()
{
	for (unsigned char i = 0; i < totalTwits; i++)
	{
		for (unsigned char j = 0; j < list[i].text.size; j++)
		{
			switch (list[i].text[j])
			{
			case 'á':
			{
				list[i].text[j] = 'a';
				break;
			}
			case 'é':
			{
				list[i].text[j] = 'e';
				break;
			}
			case 'í':
			{
				list[i].text[j] = 'i';
				break;
			}
			case 'ó':
			{
				list[i].text[j] = 'o';
				break;
			}
			case 'ú':
			{
				list[i].text[j] = 'u';
				break;
			}
			case 'Á':
			{
				list[i].text[j] = 'A';
				break;
			}
			case 'É':
			{
				list[i].text[j] = 'E';
				break;
			}
			case 'Í':
			{
				list[i].text[j] = 'I';
				break;
			}
			case 'Ó':
			{
				list[i].text[j] = 'O';
				break;
			}
			case 'Ú':
			{
				list[i].text[j] = 'U';
				break;
			}
			case 'ñ':
			{
				list[i].text[j] = 'n';
				break;
			}
			case 'Ñ':
			{
				list[i].text[j] = 'N';
				break;
			}
			}
		}
	}
}

void twLcd::parseData()
{
	struct tm data;				//NO SE COMO SE HACE
	put_time(&data, "%D");
}

twLcd::~twLcd()
{
	closeLcd();
}
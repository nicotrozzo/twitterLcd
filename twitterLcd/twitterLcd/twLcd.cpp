#include "twLcd.h"

#define MAX_SPEED	5
#define MIN_SPEED	1
#define DEFAULT_SPEED 3
#define MAX_LINE_SIZE	16

twLcd::twLcd(basicLCD* dispPointer, unsigned char totalTwits_, string& userName_)
{
	currentSpeed = DEFAULT_SPEED;
	tickCount = 0;
	twitIndex = 0;
	totalTwits = totalTwits_;
	userName = userName_;
	showingTwits = false; //empieza mostrando una secuencia de caracteres en pantalla para indicar que el programa no se colgo, mas adelante mostrara los twits
	lcd = dispPointer;
	initDisplay();
}

void twLcd::initDisplay()
{
	lcd->lcdClear();	
	if (userName.size() <= MAX_LINE_SIZE+2)
	{
		*lcd << ('@'+userName+':').c_str();
	}
	else
	{
		*lcd << ('@' + userName.substr(0, MAX_LINE_SIZE - 2) + ':').c_str();
	}
	lcd->lcdSetCursorPosition({2,1});
	*lcd << '|';
}

void twLcd::startShowing(vector<twit> list_)
{
	list = list_;
	twitIndex = 0;
	tickCount = 0;
	offsetString = 0;
	parseText();							//falta parsear fecha y hora
	showingTwits = true;
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
	tickCount = 0;	//Reinicia el timer
	offsetString = 0;
	currentTwit = userName + ": - " + list[twitIndex].text + ' ';
	currentTwitData = list[twitIndex].data;
	lcd->lcdClear();
	(*lcd) << currentTwitData.c_str();
	lcd->lcdSetCursorPosition({ 2,1 });			//Llevo cursor a la posicion 1 de el segundo renglon
	(*lcd) << currentTwit.substr(offsetString,offsetString+MAX_LINE_SIZE).c_str();
}

bool twLcd::update()
{
	if (tickCount == currentSpeed)
	{
		if (showingTwits)
		{
			if (currentTwit.size() != offsetString)
			{
				offsetString++;
				lcd->lcdSetCursorPosition({ 2,1 });
				lcd->lcdClearToEOL();
				if ((currentTwit.size() - offsetString) <= MAX_LINE_SIZE)
				{
					(*lcd) << currentTwit.substr(offsetString, currentTwit.size()).c_str();
				}
				else
				{
					(*lcd) << currentTwit.substr(offsetString, offsetString + MAX_LINE_SIZE).c_str();
				}
			}
			else
			{
				showNextTwit();
			}
		}
		else
		{

		}
	}
	else
	{
		tickCount++;
	}
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
	tm data;				//NO SE COMO SE HACE
	put_time(&data, "%D");
}

twLcd::~twLcd()
{
	closeLcd();
}
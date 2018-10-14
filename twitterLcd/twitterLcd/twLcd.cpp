#include "twLcd.h"

#define MAX_SPEED	5
#define MIN_SPEED	1
#define DEFAULT_SPEED 3
#define MAX_LINE_SIZE	16

twLcd::twLcd(basicLCD* dispPointer, unsigned char totalTwits_, string& userName_) : loadingChars({ '-','/','|','\\' })
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
	update();
}

void twLcd::startShowing(vector<twit> list_)
{
	list = list_;
	twitIndex = 0;
	tickCount = 0;
	offsetString = 0;
	parseData();
	parseText();							
	showingTwits = true;
	showTwit();
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
	bool ret = false;
	if (showingTwits)
	{
		if (tickCount == currentSpeed)
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
				if (twitIndex < MAX_LINE_SIZE)
				{
					showNextTwit();
				}
				else
				{
					ret = true;
				}
			}
		}
		else
		{
			tickCount++;
		}
	}
	else
	{
		lcd->lcdSetCursorPosition({ 2,1 });
		*lcd << loadingChars[tickCount++];
		if (tickCount == 4)
		{
			tickCount = 0;
		}
	}
	return ret;
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
	tm data = {};				
	stringstream str(list.data);
	for (int i = 0; i < list.data.size(); i++)
	{
		if (list.data[i] == '+')
		{
			while (list.data[i] != ' ')
			{
				list.data.erase(i);					//borro la zona horaria del string
				i++;
			}
			list.data.erase(i);						//borro el espacio siguiente
		}
	}
	str >> get_time(&data, "%a %b %d %H:%M:%S %Y");
	char * d, *m, *y, *h, *min;
	itoa(data.tm_mday, d, 10);
	itoa(data.tm_mon+1, m, 10);
	itoa(data.tm_year + 1900, y, 10);				//en la estructura tm el año devuelve a partir del 1900
	itoa(data.tm_hour, h, 10);
	itoa(data.tm_min, min, 10);
	string day = d, year = y, month = m, hour = h, minute = min;
	year.erase(0, 1);								//dejo el año en formato YY
	if (data.tm_mday < 9)
	{
		day = '0' + day;
	}
	if ((data.tm_mon + 1) < 9)						//ya que en la estructura se guarda el mes del 0 al 11
	{
		month = '0' + month;
	}
	if (data.tm_hour < 9)
	{
		hour = '0' + hour;
	}
	if (data.tm_min < 9)
	{
		minute = '0' + minute;
	}
	list.data = day + '/' + month + '/' + year + " - " + hour + ':' + minute;
}

twLcd::~twLcd()
{
	closeLcd();
}
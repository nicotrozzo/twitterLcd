#pragma once
#include "basicLCD.h"
#include <vector>
#include <string>

using namespace std;

typedef struct
{
	string text;
	string data;
}twit;

class twLcd
{
public:
	twLcd(basicLCD * dispPointer,unsigned char totalTwits_, vector<twit> list_);
	void showNextTwit();
	void showAgain();
	void showPreviousTwit();
	void incSpeed();
	void decSpeed();
	bool update();
	void closeLcd();
	~twLcd();
private:
	unsigned char tickCount;
	unsigned char currentSpeed;
	string currentTwit;
	string currentTwitData;
	string textSendToDisplay;
	string userName;
	basicLCD * lcd;
	vector<twit> list;
	unsigned int twitIndex;
	unsigned int offsetString;
	void showTwit();
	unsigned char totalTwits;
	void parseText();
	void parseData();
};

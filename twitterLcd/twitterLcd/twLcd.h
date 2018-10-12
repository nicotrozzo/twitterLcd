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
	twLcd(basicLCD * dispPointer);
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
	basicLCD * lcd;
	vector<twit>& list;
	unsigned int twitIndex;
	unsigned int offsetString;
	void showTwit();
};

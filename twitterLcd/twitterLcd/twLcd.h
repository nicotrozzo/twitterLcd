#pragma once
#include "basicLCD.h"
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>


using namespace std;

typedef struct
{
	string text;
	string data;
}twit;

class twLcd
{
public:
	twLcd(basicLCD * dispPointer, unsigned char totalTwits_, string& userName_);
	void startShowing(vector<twit> list_);
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
	string userName;
	basicLCD * lcd;
	vector<twit> list;
	unsigned int twitIndex;
	size_t offsetString;
	unsigned char totalTwits;
	bool showingTwits;
	char loadingChars[4];
	void showTwit();
	void parseText();
	void parseData();
	void initDisplay();
};

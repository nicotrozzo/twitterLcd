#pragma once
#include "basicLCD.h"
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sstream>
#include "twitter.h"

using namespace std;

class twLcd
{
public:
	twLcd(basicLCD * dispPointer, string& userName_);
	void startShowing(vector<twit> list_, size_t totalTwits_);
	void showNextTwit();
	void showAgain();
	void showPreviousTwit();
	void incSpeed();
	void decSpeed();
	bool update();
	void closeLcd();
	void printError(const char*message);
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
	size_t totalTwits;
	bool showingTwits;
	char loadingChars[4];
	void showTwit();
	void parseText();
	void parseData();
	void initDisplay();
};
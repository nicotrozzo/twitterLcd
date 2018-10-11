#pragma once
#include "basicLCD.h"
#include <vector>
#include <string>
class twLcd
{
public:
	twLcd();
	void showNextTwit();
	void showAgain();
	void showPrevious();
	void incSpeed();
	void decSpeed();
	bool update();
	void closeLcd();
	~twLcd();
private:
	unsigned char tickCount;
	unsigned char currentSpeed;
	std::string currentTwit;
	std::string currentTwitInfo;
	basicLCD * lcd;
	vector<> &list;
	unsigned int currentTwit;
};




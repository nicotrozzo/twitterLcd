#pragma once
#include "basicLCD.h"
#include "phase1.h"

class hitachiLCD : public basicLCD
{
public:
	hitachiLCD(int iDevice);
	~hitachiLCD();
	virtual bool lcdInitOk();
	virtual FT_STATUS lcdGetError(); 
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const unsigned char c);
	virtual basicLCD& operator<<(const char * c);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();
	
private:
	FT_LCD display;
	bool initOk;
	bool validChar(const unsigned char c);

protected:
	virtual void lcdUpdateCursor();
};
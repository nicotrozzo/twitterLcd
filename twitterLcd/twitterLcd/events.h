#pragma once
#include <chrono>
#include "twLcd.h"

typedef enum { INVALID, KEY_A, KEY_R, KEY_S, KEY_Q, KEY_PLUS, KEY_MINUS }event_k; //ver de sacar de aca el timer total se cuando es por el timer en eventType
typedef enum { NO_EVENT, KEYBOARD_EVENT, TIMER_EVENT }eventType;
typedef enum { LOADING_TWITS, SHOWING_TWITS}stateType;

typedef struct
{
	void(*action) (void *);
	stateType nextState;
}celltype_n;

class events
{
public:
	events(/*WINDOW * window*/);
	~events();
	bool incomEvent();
	bool keyPressed();	
	eventType getEvent();
	event_k getKeyEvent();
	bool dispatcher(twLcd& lcdManager);
private:
	void fsmCycle(const event_k evento, void *userData);
	int key;		
	eventType evento;
	event_k keyEvent;
	//WINDOW *win;
	std::chrono::system_clock::time_point initial;		//iniciarlo con now() en el while donde esta el dispatcher
	stateType currentState;
	void checkKey();
	int getKey();
};

void noAction(void*);



#pragma once

typedef enum {KEY_A, KEY_R, KEY_S, KEY_Q, KEY_PLUS, KEY_MINUS, TIMER};
typedef enum { NO_EVENT, KEY_EVENT, TIMER_EVENT }eventType;
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
	int getKey();	//ver porque wgetch() devuelve int
private:
	int key;		//lo mismo que lo comentado arriba
	eventType evento;
	//WINDOW *win;
	std::chrono::system_clock::time_point initial;		//iniciarlo con now() en el while donde esta el dispatcher
};
#include "events.h"
#include "curses.h"
#include <ratio>
#include <chrono>
events::events(/*WINDOW * window*/)	//mandar stdsrc
{
	initscr();		//esto ponerlo en el main y que esto reciba un puntero a window y que sea el stdscr
	//win = window;
	keypad(stdscr, true);
	nodelay(stdscr, true);		//estas dos funciones hacen que getch() no sea bloqueante
	noecho();
}

bool events::incomEvent()
{
	std::chrono::duration< int, std::ratio<1, 1> > oneSec;
	if (keyPressed())
	{
		evento = KEY_EVENT;
		return true;
	}
	else if( (initial + 3 * oneSec) <= std::chrono::system_clock::now())
	{
		evento = TIMER_EVENT;
	}
	else
	{
		evento = NO_EVENT;
		return false;
	}
}

bool events::keyPressed()
{
	//key = wgetch(win);
	//key = getch();
	key = wgetch(stdscr);
	//return (key != ERR);
	if (key != ERR)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int events::getKey()
{
	return key;
}

events::~events()
{
	endwin();
}
#include "events.h"
#include "curses.h"
#include <ratio>
#include <chrono>


#define EVENT_COUNT	8	
#define STATE_COUNT	2

events::events(/*WINDOW * window*/)	//mandar stdsrc
{
	initscr();		//esto ponerlo en el main y que esto reciba un puntero a window y que sea el stdscr
	//win = window;
	keypad(stdscr, true);
	nodelay(stdscr, true);		//estas dos funciones hacen que getch() no sea bloqueante
	noecho();
	currentState = LOADING_TWITS;
}

bool events::incomEvent()
{
	std::chrono::duration< int, std::ratio<1> > oneSec(1);
	if (keyPressed())
	{
		evento = KEYBOARD_EVENT;
	}
	else if( (initial + 3 * oneSec) <= std::chrono::system_clock::now())
	{
		initial = std::chrono::system_clock::now();
		evento = TIMER_EVENT;
	}
	else
	{
		evento = NO_EVENT;
		return false;
	}
	return true;
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

void events::dispatcher(twLcd& lcdManager)
{
	if (currentState == LOADING_TWITS)
	{
		if (evento == KEYBOARD_EVENT)
		{
			if (keyEvent == KEY_Q)
			{
				lcdManager.closeLcd();
				currentState = SHOWING_TWITS;
			}
		}
		else if (evento == TIMER_EVENT)
		{
			lcdManager.update();
		}
		
	}
	else if (currentState == SHOWING_TWITS)
	{
		if (evento == KEYBOARD_EVENT)
		{
			switch (keyEvent)
			{
			case KEY_A:
				lcdManager.showPreviousTwit();
				break;
			case KEY_R:
				lcdManager.showAgain();
				break;
			case KEY_S:
				lcdManager.showNextTwit();
				break;
			case KEY_Q:
				//lcdManager.closeLcd();
				break;
			case KEY_PLUS:
				lcdManager.incSpeed();
				break;
			case KEY_MINUS:
				lcdManager.decSpeed();
				break;
			default:
				break;
			}
		}
		else if (evento == TIMER_EVENT)
		{
			lcdManager.update();
		}
	}
}

/*void events::fsmCycle(const event_k_t evento, void *userData)
{
	const celltype_n tableFsm[EVENT_COUNT][STATE_COUNT] = 
		//LOADING_TWITS					SHOWING_TWITS
	{
		//{ noAction, LOADING_TWITS },	{ noAction, SHOWING_TWITS },		//NO_EVENT
		{ noAction, LOADING_TWITS}, { }//KEY_A
	};

	(tableFsm[evento][currentState]).action(this);
	currentState = (tableFsm[evento][currentState].nextState);
}*/

void events::checkKey()
{ 
	if (evento == KEYBOARD_EVENT)
	{
		key = getKey();
		switch (key)
		{
		case 'r': case 'R':
			keyEvent = KEY_R;
			break;
		case 'a': case 'A':
			keyEvent = KEY_A;
			break;
		case 's': case 'S':
			keyEvent = KEY_S;
			break;
		case 'q': case 'Q':
			keyEvent = KEY_Q;
			break;
		case '+':
			keyEvent = KEY_PLUS;
			break;
		case '-':
			keyEvent = KEY_MINUS;
			break;
		default:
			keyEvent = INVALID;
			break;
		}
	}
}

eventType events::getEvent()
{
	return evento;
}

event_k events::geyKeyEvent()
{
	return keyEvent;
}

events::~events()
{
	endwin();
}
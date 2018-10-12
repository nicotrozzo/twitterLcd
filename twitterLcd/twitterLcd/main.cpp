#include "hitachiLCD.h"
#include "twUser.h"

#define DISPLAY 4

int main(int argc,char *argv[])
{
	twUser user(argv[1], atoi(argv[2]));
	if (user.getError().type == NO_TW_ERR)
	{
		user.getTwits();
	}
}

const char *user, unsigned int cant
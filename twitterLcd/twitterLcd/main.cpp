#include "hitachiLCD.h"
#include "twUser.h"
#include <boost/program_options.hpp>

#define DISPLAY 4
#define DEFAULT_AMOUNT_OF_TWITS 15

bool cmdLineParser(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	cmdLineParser(argc, argv);
	twUser user(argv[1], atoi(argv[2]));
	if (user.getError().type == NO_TW_ERR)
	{
		while (user.getTwits() != 0)
		{
			//dibujar en el lcd algo para que se vea que no se colgo
		}

	}
}

bool cmdLineParser(int argc, char *argv[])
{
	bool var = false;
	if (argc == 1)
	{
		*argv[2] = static_cast<char>(DEFAULT_AMOUNT_OF_TWITS);			//dudas aca
		var = true;
	}
	else if(argc == 2)
	{
		if (isdigit((char)(*argv[2])))
		{
			var = true;
		}
	}
}
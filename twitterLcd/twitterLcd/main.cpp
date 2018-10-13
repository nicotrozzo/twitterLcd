#include "hitachiLCD.h"
#include "twUser.h"
#include <boost/program_options.hpp>

#define DISPLAY 4

int main(int argc,char *argv[])
{
	cmdLineParser(argc, argv);
	twUser user(argv[1], atoi(argv[2]));
	if (user.getError().type == NO_TW_ERR)
	{
		user.getTwits();
		
	}
}

bool cmdLineParser(int argc, char *argv[])
{

}
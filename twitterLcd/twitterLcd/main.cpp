#include "basicLCD.h"
#include "hitachiLCD.h"
#include "twUser.h"
#include <boost/lexical_cast.hpp>


#define DISPLAY 4
#define DEFAULT_AMOUNT_OF_TWITS 15
#define DEVICE 5 //numero de lcd del grupo

bool cmdLineParser(int argc, char *argv[], string &userName, int &amountOfTwits);
basicLCD* getDisplay(void);

int main(int argc, char *argv[])
{
	string userName;
	int amountOfTwits;
	if (cmdLineParser(argc, argv, userName, amountOfTwits))
	{
		basicLCD* lcd = getDisplay(); 
		twUser user(userName.c_str(),amountOfTwits);
		if (user.getError().type == NO_TW_ERR)
		{
			while (user.getTwits() != 0)
			{
				//dibujar en el lcd algo para que se vea que no se colgo
			}

		}
	}
}

basicLCD* getDisplay(void)
{
	return new hitachiLCD(DEVICE);
}
/*Devuelve true si estan dadas las condiciones para continuar con el programa
Esto es, si solo se recibio el nombre de usuario o si ademas opcionalmente se envio un numero positivo 
para la cantidad de twits a mostrar.
De haber mas parametros estos son ignorados*/
bool cmdLineParser(int argc, char *argv[],string &userName, int &amountOfTwits)
{
	bool ret = false;
	if (argc > 1)
	{
		userName = argv[1];	//se toma como nombre de usuario cualquier cosa, si no era valido se sabra en la respuesta de twitter
		if (argc > 2)
		{
			string check = argv[2];
			try
			{
				amountOfTwits = boost::lexical_cast<int>(check);	//intenta pasar a un int el segundo parametro, si no puede habra una excepcion
				if (amountOfTwits > 0)	
				{
					ret = true;	//solo se continuara con el programa si enviaron una cantidad positiva de twits a mostrar
				}
				else
				{
					cout << "Ingrese un numero positivo para especificar la cantidad de twits a mostrar" << endl;
				}
			}
			catch (const boost::bad_lexical_cast&)
			{
				cout << "Ingrese un numero entero como segundo parametro para especificar cantidad de twits" << endl;
			}
		}
		else
		{
			amountOfTwits = 0;	//si no especifican cantidad de twits, se toma 0, y se interpretara luego como que se pide el default de Twitter
			ret = true; 
		}
	}
	else
	{
		cout << "Ingrese como parametro un nombre de usuario para buscar sus Twits" << endl;
		cout << "Opcionalmente puede agregar como segundo parametro la cantidad de twits a mostrar" << endl;
	}
	return ret;
}


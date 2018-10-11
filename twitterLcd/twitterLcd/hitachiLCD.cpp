#include "hitachiLCD.h"
//#define CLEAR_DISPLAY 0x01
//#define RETURN_HOME 0x02
#define EOL1 16
#define EOL2 32
#define SET_DDRAM_ADD(x) ((x) | (0x80))		//porque la instruccion pide ese bit en 1

using namespace std;

hitachiLCD::hitachiLCD(int iDevice) : display(iDevice)
{
	if ((display.getError()).type == NO_ERR)
	{
		initOk = true;
	}
	else
	{
		initOk = false;
	}
}


hitachiLCD::~hitachiLCD()
{
}

bool hitachiLCD::lcdInitOk()
{
	return initOk;
}

FT_STATUS hitachiLCD::lcdGetError()
{
	return display.getStatus();
}

bool hitachiLCD::lcdClear()
{
	bool val = false;
	if (display.lcdWriteIR(CLEAR_DISPLAY))
	{
		cadd = 1;
		val = true;
	}
	return val;
}

bool hitachiLCD::lcdClearToEOL()
{
	bool val;
	int count;
	cursorPosition initial = lcdGetCursorPosition();
	if (cadd <= EOL1)
	{
		for (count = cadd; count <= EOL1; count++)
		{
			val = display.lcdWriteDR(' ');						
		}
	}
	else
	{
		for (count = cadd; count >= EOL1 && count <= EOL2; count++)
		{
			val = display.lcdWriteDR(' ');						
		}
	}
	val = lcdSetCursorPosition(initial);
	return val;
}

basicLCD & hitachiLCD::operator<<(const unsigned char c)
{
	if (validChar(c))
	{
		if (cadd <= EOL2)
		{
			display.lcdWriteDR(c);
			cadd++;
			if (cadd == EOL2 + 1)
			{
				lcdSetCursorPosition({ 1,1 });	//vuelve al principio
			}
			else
			{
				lcdUpdateCursor();
			}
		}
	}
	else
	{
		cout << "Caracter no imprimible en el LCD" << endl;
	}
	return *this;
}

/*Debe recibir un puntero a un NULL TERMINATED const char *, de lo contrario no esta garantizado su funcionamiento
Si el string entero entra en el LCD, se imprime sin borrar lo que hubiera.
En caso que no entre, limpia el LCD e imprime en modo deslizante y al final queda en el LCD la ultima parte del texto
*/
basicLCD & hitachiLCD::operator<<(const char * c)
{
	size_t size = strlen(c);
	unsigned int nWritten;
	if ( size <= EOL2 )	//si el string entra entero en el display, lo escribe
	{
		if (size > EOL2 - cadd)	//si el string no entra con lo que tiene escrito, lo borra
		{
			lcdClear();
		}
		for (nWritten = 0; nWritten < size; nWritten++)	
		{
			*this << static_cast<const unsigned char>(c[nWritten]);
		} 
	}
	else  //si el string entero no entra en el display imprime los ultimos 32 caracteres
	{
		lcdClear();
		for (nWritten = 0; nWritten < EOL2 ; nWritten++)	
		{
			*this << static_cast<const unsigned char>(c[nWritten + size - EOL2]);
		}
	}
	return *this;
}

/*Devuelve false si el cursor esta en la primera linea*/
bool hitachiLCD::lcdMoveCursorUp()		
{
	bool val = false;
	if (cadd <= EOL2 && cadd > EOL1)
	{
		cadd -= EOL1;	
		lcdUpdateCursor();
		val = false;
	}
	return val;
}

/*Devuelve false si el cursor esta en la segunda linea*/
bool hitachiLCD::lcdMoveCursorDown()			
{
	bool val = false;
	if ( cadd <= EOL1 )
	{
		cadd += EOL1;
		lcdUpdateCursor();
		val = true;
	}
	return val;
}

/*Devuelve false si el cursor esta en la ultima posicion*/
bool hitachiLCD::lcdMoveCursorRight()			
{
	bool val = false;
	if (cadd < EOL2)
	{
		cadd++;
		lcdUpdateCursor();
		val = true;
	}
	return val;
}

/*Devuelve false si el cursor esta en la primera posicion*/
bool hitachiLCD::lcdMoveCursorLeft()			
{
	bool val = false;
	if (cadd > 1)
	{
		cadd--;
		lcdUpdateCursor();
		val = true;
	}
	return val;
}

/*Devuelve false si era una posicion invaldia para el cursor*/
bool hitachiLCD::lcdSetCursorPosition(const cursorPosition pos)		
{
	bool val = false;
	if ((pos.column >= 1) && (pos.column <= 32))
	{
		if (pos.row == 1)
		{
			cadd = pos.column;
			lcdUpdateCursor();
			val = true;
		}
		else if (pos.row == 2)
		{
			cadd = pos.column + 16;
			lcdUpdateCursor();
			val = true;
		}
	}
	return val;
}

cursorPosition hitachiLCD::lcdGetCursorPosition()
{
	cursorPosition pos;
	if (cadd <= EOL1)
	{
		pos.row = 1;
		pos.column = cadd;
	}
	else
	{
		pos.row = 2;
		pos.column = cadd - 16;
	}
	return pos;
}

/*Verifica que sea un caracter imprimible por el display*/
bool hitachiLCD::validChar(const unsigned char c)
{
	return ((c >= 0x20) && (c <= 0x7F)) || ((c >= 0xA0) && (c < 0xFF));
}

/*Informa al display el valor de cadd, en caso que cadd este fuera de los limites del display, no hace nada*/
void hitachiLCD::lcdUpdateCursor(void)
{
	if (cadd >= 1 && cadd <= EOL1)
	{
		display.lcdWriteIR(SET_DDRAM_ADD(cadd - 1));
	}
	else if ((cadd >= EOL1) && (cadd <= EOL2))
	{
		display.lcdWriteIR(SET_DDRAM_ADD((cadd-EOL1 + 0x40) - 1));
	}
}

#include "phase1.h"
#include <chrono>

#define CONNECTING_TIME 5

using namespace std;

FT_LCD::FT_LCD(int iDevice)
{
	BYTE temp;
	std::chrono::seconds MaxTime(CONNECTING_TIME);/*The display has a settling time after the physical connection so the attempt to connect
													will be done for a few seconds*/
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	status = !FT_OK;

	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		string description("EDA LCD ");
		description += iDevice + '0';
		description += " B";
		status = FT_OpenEx((void *)description.c_str(), FT_OPEN_BY_DESCRIPTION, &deviceHandler);

		if (status == FT_OK)
		{
			UCHAR Mask = 0xFF;	//Selects all FTDI pins.
			UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(deviceHandler, Mask, Mode) == FT_OK)	// Sets LCD as asynch bit mode. Otherwise it doesn't work.
			{
				temp = FUNCTION_SET_8BITS & MSN;
				//Finally executes the action "write to LCD"...
				if (lcdWriteNybble(temp))
				{
					Sleep(5);
					if (lcdWriteNybble(temp))
					{
						Sleep(1);
						if (lcdWriteNybble(temp))
						{
							Sleep(1);
							temp = (FUNCTION_SET_4BITS & MSN);
							if (lcdWriteNybble(temp))
							{
								Sleep(1);
								temp = FUNCTION_SET_4BITS;
								if (lcdWriteIR(temp) == true)
								{
									Sleep(1);
									temp = DISPLAY_OFF;
									if (lcdWriteIR(temp) == true) 
									{
										Sleep(1);
										temp = CLEAR_DISPLAY;
										if (lcdWriteIR(temp) == true)
										{
											Sleep(10);
											temp = ENTRY_MODE_SET;
											if (lcdWriteIR(temp) == true)
											{
												Sleep(2);
												temp = RETURN_HOME;
												if (lcdWriteIR(temp))
												{
													error.type = NO_ERR;
													error.detail = "Display inicialization OK";
												}
											}
										}
									}
								}
							}
						}
					}
				}
				if(status != FT_OK)
				{
					error.type = WRITE_ERR;
					error.detail = "Error writing to LCD";
				}
			}
			else
			{
				error.type = CONFIG_ERR;
				error.detail = "Couldn't configure LCD";
			}
		}
		else
		{
			error.type = OPEN_ERR;
			error.detail = "Couldn't open LCD";
		}
		current = std::chrono::system_clock::now();
	}
}

FT_LCD::~FT_LCD()
{
	FT_Close(deviceHandler);
}

bool FT_LCD::lcdWriteDR(BYTE valor)
{
	bool ret = false;
	BYTE temp = valor & MSN;	//me quedo con la parte alta del nybble
	temp = temp | LCD_RS_ON;		
	if (lcdWriteNybble(temp) == true)
	{
		temp = ((valor & LSN) << 4) & MSN;
		temp = temp | LCD_RS_ON;
		if (lcdWriteNybble(temp) == true)
		{
			error.type = NO_ERR;
			ret = true;
		}
	}
	if(!ret)
	{
		error.detail = "Error writing to LCD";
	}
	return ret;
}

bool FT_LCD::lcdWriteIR(BYTE valor)
{
	bool ret = false;
	BYTE temp = valor & MSN;
	temp = temp | LCD_RS_OFF;	//register select para IR
	if (lcdWriteNybble(temp) == true)
	{
		temp = ((valor & LSN) << 4) & MSN;
		temp = temp | LCD_RS_OFF;
		if (lcdWriteNybble(temp) == true)
		{
			error.type = NO_ERR;
			ret = true;
		}
	}
	if (!ret)
	{
		error.type = WRITE_ERR;
		error.detail = "Error writing to LCD";
	}
	return ret;
}

bool FT_LCD::lcdWriteNybble(BYTE valor)
{
	bool ret = false;
	BYTE temp = valor & (~LCD_E_ON);	//pongo el bit E en bajo nivel...  fijarse que pasa con el casteo entre int del define y el unsigned char, seria 0XFE
	status = FT_Write(deviceHandler, &temp, sizeof(BYTE), &sizeSent);
	if (status == FT_OK)
	{
		Sleep(1);
		temp = valor | LCD_E_ON;	//prendo el bit del enable
		status = FT_Write(deviceHandler, &temp, sizeof(BYTE), &sizeSent);
		if (status == FT_OK)
		{
			Sleep(3);
			temp = valor & (~LCD_E_ON);	//apago el enable para terminar de tomar el dato
			status = FT_Write(deviceHandler, &temp, sizeof(BYTE), &sizeSent);
			if (status == FT_OK)
			{
				Sleep(1);
				ret = true;
				error.type = NO_ERR;
			}
		}
	}
	if (!ret)
	{
		error.type = WRITE_ERR;
		error.detail = "Error writing to LCD";
	}
	return ret;
}

FT_STATUS FT_LCD::getStatus()
{
	return status;
}

lcdErr_t FT_LCD::getError()
{
	return error;
}
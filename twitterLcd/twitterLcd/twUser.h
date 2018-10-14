#pragma once
#include <iostream>
#include <curl/curl.h>
#include <exception>
#include <vector>
#include "twitter.h"

using namespace std;

typedef enum{NO_TW_ERR,CURL_START_ERR,TOKEN_ACCESS_ERR,CURL_EASY_PERF_ERR,NO_ELEMENT_TEXT,NONEXISTING_USER,NO_TWITS,UNEXPECTED_JSON}twErrType;

typedef struct
{
	string detail;
	twErrType type;
}twUserError;

class twUser
{
public:
	/*Recibe como primer parametro el usuario al que le debe solicitar los twits y
	como segundo parametro la cantidad de twits.*/
	twUser(const char *user, unsigned int cant = 0);
	/*getTwits:
	No bloqueante, llamar hasta que devuelva 0 para que reciba todo
	Al terminar, parsea los twits*/
	int getTwits();
	/*Toma lo que haya internamente guardado recibido de Twitter y lo parsea
	Se recomienda no utilizarla, sino llamar a getTwits() que los parsea al terminar de recibir el mensaje*/
	void parseTwits();
	twUserError getError();
	vector<twit> getTwitList();
	~twUser();

private:
	CURL * curl;
	CURLM * multiHandle;
	CURLcode res;
	string token;
	string readString;
	int stillRunning;
	twUserError err;
	vector<twit>twits;
	void setUpMulti(const char *user, unsigned int cant);
};


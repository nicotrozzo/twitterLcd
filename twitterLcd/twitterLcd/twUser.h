#pragma once
#include <iostream>
#include <curl/curl.h>
#include <exception>
#include <vector>

using namespace std;

typedef enum{NO_TW_ERR,CURL_START_ERR,TOKEN_ACCESS_ERR,CURL_EASY_PERF_ERR,NO_ELEMENT_TEXT}twErrType;

typedef struct
{
	string detail;
	twErrType type;
}twUserError;

class twUser
{
public:
	twUser();
	/*getTwits:
	Recibe cantidad de twits para solicitar al servidor
	En caso de recibir 0, se pide la cantidad por defecto que envie el servidor
	ATENCION: no bloqueante, llamar hasta que devuelva 0 para que reciba todo*/
	int getTwits(const char *user,unsigned int cant = 0);
	void parseTwits();
	twUserError getErr();
	~twUser();

private:
	CURL * curl;
	CURLM * multihandle;
	CURLcode res;
	string token;
	string readString;
	int stillRunning;
	twUserError err;
	void setUpMulti();
	vector<twit>twits;
};

 
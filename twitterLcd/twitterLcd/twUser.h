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

typedef struct
{
	string text;
	string data;
}twit;

class twUser
{
public:
	/*Recibe como primer parametro el usuario al que le debe solicitar los twits y
	como segundo parametro la cantidad de twits.*/
	twUser(const char *user, unsigned int cant = 0);
	/*getTwits:
	No bloqueante, llamar hasta que devuelva 0 para que reciba todo*/
	int getTwits();
	void parseTwits();
	twUserError getError();
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
	size_t myCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
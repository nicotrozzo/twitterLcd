#pragma once
#include <iostream>
#include <curl/curl.h>
#include <exception>
#include <vector>

using namespace std;

typedef enum{NO_TW_ERR,CURL_START_ERR,TOKEN_ACCESS_ERR,CURL_EASY_PERF_ERR,}twErrType;

typedef struct
{
	string detail;
	twErrType type;
}twUserError;

class twUser
{
public:
	twUser();
	bool getTwits(const char *user,unsigned int cant = 0);
	void parseTwits();
	twUserError getErr();
	~twUser();

private:
	CURL * curl;
	CURLM * multihandle;
	CURLcode res;
	string token;
	string query;
	string API_key;
	string API_SecretKey;
	string readString;
	int stillRunning;
	twUserError err;
};

 
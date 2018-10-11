#pragma once
#include <iostream>
#include <curl/curl.h>
#include <exception>
#include <vector>

using namespace std;

class twUser
{
public:
	twUser();
	bool getTwits(const char *user,unsigned int cant = 0);
	void parseTwits();
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
};

 
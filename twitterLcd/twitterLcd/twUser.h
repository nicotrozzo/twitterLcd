#pragma once
#include <iostream>
#include <curl/curl.h>
#include <exception>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class twUser
{
public:
	twUser();
	bool getTwits(int cant);
	void parseTwits();
	~twUser();

private:
	CURL * curl;
	CURLM * multihandle;
	CURLcode res;
	string token;
	string query;
	string API_Key;
	string API_secretKey;
	json twJson;
	int stillRunning;
};

 
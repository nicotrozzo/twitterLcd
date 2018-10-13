#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <string>

using namespace std;

int main(void)
{
	string a = "Thu Apr 06 15:28 : 43 + 0000 2017";
	tm t = {};
	istringstream ss("Thu Apr 06 15:28 : 43 + 0000 2017");
	ss.imbue(std::locale("de_DE.utf-8"));
	get_time(&t, "%D");
	cout << std::put_time(&t, "%c") << endl;
}
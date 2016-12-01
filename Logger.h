//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>

using namespace std;

class Log
{
private:
	std::streambuf * buf;
	std::ofstream of;

	void GetDateTime(char *strDateTime);
	long FileSize(char* filename);
public:
	Log(char* filename, int max_size=524228);
	~Log();
	void Write(char* logline);
	void Write(const char* logline, ...);
};
#endif

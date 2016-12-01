/**
 * The class purpose is to make the logging activity easier.
 *
 * Base idea: http://www.infernodevelopment.com/c-log-file-class-forget-debuggers
 *
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include "Logger.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/**
 * This helper funtcion receives the local date and time and convert it to
 * character array.
 * It creates the following date time string:
 * DD/MM/YYYY HH:mm:SS
 *
 * @param strDateTime | char*
 *
 * @since 03/11/2011
 *
 * @author Istvan Vig
 */
void Log::GetDateTime(char *strDateTime)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	sprintf(strDateTime, "%02d/%02d/%04d %02d:%02d:%02d",
		timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year+1900,
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

/**
 * This helper funtcion returns the size of a file given by its name.
 *
 * @param filename | char*
 * @return long
 *
 * @since 03/11/2011
 *
 * @author http://www.cplusplus.com/doc/tutorial/files/ and Istvan Vig
 */
long Log::FileSize(char* filename)
{
	long begin,end;
	ifstream myfile(filename);

	begin = myfile.tellg();
	myfile.seekg(0, ios::end);
	end = myfile.tellg();
	myfile.close();

	return (end-begin);
}

/**
 * Constructor.
 * If you specify the filename the object will use this file to write the
 * information to. If you pass an empty string to it the object will use the
 * std::cout to write the data to.
 * If you pass the max_size value then the function will rename the existing
 * log file. Renaming means it will add a new extension to it:
 * <OLDFILENAME>.old<RANDOM NUMBER> The random number is 100 to 999.
 * The value countered in bytes. If you do not pass any value the default is
 * 524228 bytes (512kb).
 *
 * @param filename | char*
 * @param max_size=524228 | int
 *
 * @since 03/11/2011
 */
Log::Log(char* filename, int max_size)
{
	if(filename!=NULL && strcmp(filename,"")!=0)
	{
		if(Log::FileSize(filename) > max_size)
		{
			char* newname = new char[strlen(filename)+64];
			char* random = new char[10];
			srand((unsigned)time(0));
			itoa((rand()%1000)+1, random, 10);

			// create the new file name using a random value
			strncpy(newname, filename, strlen(filename));
			strncat(newname, ".old", 4);
			strncat(newname, random, strlen(random));
			strncat(newname, "\0", 1);

			rename(filename, newname);

			// empty the file if its size is greater than the given max_size
			of.open(filename, ios::out);
			of.write("",0);
			of.close();

			delete [] random;
			delete [] newname;
		}
		of.open(filename, ios::out | ios::app);
		buf = of.rdbuf();
	}
	else
		buf = std::cout.rdbuf();
}
/**
 * Desctructor
 * It closes the log file.
 */
Log::~Log()
{
	if(of.is_open())
		of.close();
}

/**
 * It writes the given charachters to the output.
 *
 * @since 03/11/2011
 */
void Log::Write(char* logline)
{
	std::ostream out(buf);
	out << logline << endl;
}
/**
 * It writes the given charachters to the output using parameters.
 * You can use this function by the same way as the sprintf.
 * E.g.: Write("\tThis is an event #%d", intEventID).
 * The function adds a date time stamp at the beginnng of the log line.
 *
 * @since 03/11/2011
 */
void Log::Write(const char* logline, ...)
{
	std::ostream out(buf);
	va_list argList;
	char cbuffer[1024];
	char dt[64];

	Log::GetDateTime(dt);

	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);

	out << dt << "\t" << cbuffer << endl;

	out.flush();
}

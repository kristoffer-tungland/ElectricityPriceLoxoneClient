#include "loxoneTime.h"
#include <time.h>
#include <wtypes.h>

/* Loxone uses 1.1.2009 as refenrece in seconds, this delta is calculated since 1.1.1970 */
#define LOXONECURENTTIMEDELTA 1230768000

void sleep(int ms)
{
	Sleep(ms);
}

void sleeps(int s)
{
	int ms = s * 1000;
	Sleep(ms);
}

struct tm* gettimeinfo(int local)
{
	time_t rawtime;
	time(&rawtime);

	if (local == 0) {
		return gmtime(&rawtime);
	}
	else {
		return localtime(&rawtime);
	}
}

unsigned int getcurrenttime()
{
	time_t seconds;

	seconds = time(NULL);
	return seconds - LOXONECURENTTIMEDELTA;
}

int getyear(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);

	return timeinfo->tm_year + 1900;
}

int getmonth(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);

	return timeinfo->tm_mon + 1;
}

int getday(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);

	return timeinfo->tm_mday;
}

int gethour(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);

	return timeinfo->tm_hour;
}

int getminute(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);
	return timeinfo->tm_min;
}

int getsecond(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local);
	return timeinfo->tm_sec;
}

unsigned int gettimeval(int year, int month, int day, int hour, int minutes, int seconds, int local)
{
	struct tm utc;
	time_t tim;
	struct tm* utc_out;
	// Want to create a time_t value for UTC:
	// 01/10/2020 10:16:03
	// tm_year is time since 1900
	utc.tm_year = year - 1900;
	// Month is zero based, i.e. Jan is month 0
	utc.tm_mon = month - 1;
	utc.tm_mday = day;
	utc.tm_hour = hour;
	utc.tm_min = minutes;
	utc.tm_sec = seconds;
	utc.tm_isdst = 0;
	// Get time_t val for the UTC date/time
	tim = _mkgmtime(&utc);

	// Todo improve the use of local variable
	return tim - LOXONECURENTTIMEDELTA;
}

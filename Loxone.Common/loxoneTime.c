#include "inputMock.h"
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

struct tm* gettimeinfo(int local, unsigned int seconds)
{
	time_t rawtime = seconds;
	//time(&rawtime);

	if (local == 0) {
		return gmtime(&rawtime);
	}
	else {
		return localtime(&rawtime);
	}
}

unsigned int getcurrenttime()
{
	int mock = getcurrenttimemock();

	if (mock > 0) {
		return mock;
	}

	time_t seconds;

	seconds = time(NULL);
	return seconds - LOXONECURENTTIMEDELTA;
}

int getyear(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);

	return timeinfo->tm_year + 1900;
}

int getmonth(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);

	return timeinfo->tm_mon + 1;
}

int getday(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);

	return timeinfo->tm_mday;
}

int gethour(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);

	return timeinfo->tm_hour;
}

int getminute(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);
	return timeinfo->tm_min;
}

int getsecond(unsigned int time, int local)
{
	struct tm* timeinfo = gettimeinfo(local, time);
	return timeinfo->tm_sec;
}

unsigned int gettimeval(int year, int month, int day, int hour, int minutes, int seconds, int local)
{
	struct tm utc;
	// tm_year is time since 1900
	utc.tm_year = year - 1900;
	// Month is zero based, i.e. Jan is month 0
	utc.tm_mon = month - 1;
	utc.tm_mday = day;
	utc.tm_hour = hour;
	utc.tm_min = minutes;
	utc.tm_sec = seconds;
	utc.tm_isdst = -1;

	//struct tm utc = constructtm(year, month, day, hour, minutes, seconds);
	
	time_t tim;
	// Get time_t val for the UTC date/time
	tim = _mkgmtime(&utc);

	if (local == 0) {
		return tim - LOXONECURENTTIMEDELTA;
	}

	//struct tm* gm_time = gmtime(&tim);
	struct tm* lt = localtime(&tim);

	//struct tm localtime_tm = constructtm(lt->tm_year+1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	struct tm localtime_tm;

	// tm_year is time since 1900
	localtime_tm.tm_year = lt->tm_year;
	// Month is zero based, i.e. Jan is month 0
	localtime_tm.tm_mon = lt->tm_mon;
	localtime_tm.tm_mday = lt->tm_mday;
	localtime_tm.tm_hour = lt->tm_hour;
	localtime_tm.tm_min = lt->tm_min;
	localtime_tm.tm_sec = lt->tm_sec;
	localtime_tm.tm_isdst = -1;

	time_t local_time2 = _mkgmtime(&localtime_tm);

	int diff = local_time2 - tim;
	
	// Todo improve the use of local variable
	return tim - diff - LOXONECURENTTIMEDELTA;
}

struct tm constructtm(int year, int month, int day, int hour, int minutes, int seconds) {
	struct tm utc;

	// 01/10/2020 10:16:03
	// tm_year is time since 1900
	utc.tm_year = year - 1900;
	// Month is zero based, i.e. Jan is month 0
	utc.tm_mon = month - 1;
	utc.tm_mday = day;
	utc.tm_hour = hour;
	utc.tm_min = minutes;
	utc.tm_sec = seconds;
	utc.tm_isdst = -1;

	return utc;
}

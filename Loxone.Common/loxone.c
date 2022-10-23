#include <wtypes.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "loxone.h"

char* httpget(char* adress, char* page)
{
	char* price = "{\r\n  \"ScoreNow\": 22,\r\n  \"HourNow\": 8,\r\n  \"PriceNow\": 4.1345735,\r\n  \"PriceUnit\": \"NOK\/kWh\",\r\n  \"HourScores\": {\r\n    \"ScoreOfHour0\": 1,\r\n    \"ScoreOfHour1\": 4,\r\n    \"ScoreOfHour2\": 3,\r\n    \"ScoreOfHour3\": 2,\r\n    \"ScoreOfHour4\": 5,\r\n    \"ScoreOfHour5\": 6,\r\n    \"ScoreOfHour6\": 15,\r\n    \"ScoreOfHour7\": 21,\r\n    \"ScoreOfHour8\": 22,\r\n    \"ScoreOfHour9\": 18,\r\n    \"ScoreOfHour10\": 14,\r\n    \"ScoreOfHour11\": 11,\r\n    \"ScoreOfHour12\": 8,\r\n    \"ScoreOfHour13\": 9,\r\n    \"ScoreOfHour14\": 10,\r\n    \"ScoreOfHour15\": 7,\r\n    \"ScoreOfHour16\": 12,\r\n    \"ScoreOfHour17\": 17,\r\n    \"ScoreOfHour18\": 20,\r\n    \"ScoreOfHour19\": 24,\r\n    \"ScoreOfHour20\": 23,\r\n    \"ScoreOfHour21\": 19,\r\n    \"ScoreOfHour22\": 16,\r\n    \"ScoreOfHour23\": 13\r\n  },\r\n  \"HourPrices\": {\r\n    \"PriceOfHour0\": 0.88227224,\r\n    \"PriceOfHour1\": 1.0211757,\r\n    \"PriceOfHour2\": 0.9696734,\r\n    \"PriceOfHour3\": 0.91398954,\r\n    \"PriceOfHour4\": 1.0349437,\r\n    \"PriceOfHour5\": 1.8353221,\r\n    \"PriceOfHour6\": 3.5773277,\r\n    \"PriceOfHour7\": 4.0668554,\r\n    \"PriceOfHour8\": 4.1345735,\r\n    \"PriceOfHour9\": 3.7363222,\r\n    \"PriceOfHour10\": 3.4642262,\r\n    \"PriceOfHour11\": 2.4794593,\r\n    \"PriceOfHour12\": 2.2932346,\r\n    \"PriceOfHour13\": 2.4155147,\r\n    \"PriceOfHour14\": 2.4211237,\r\n    \"PriceOfHour15\": 2.2671266,\r\n    \"PriceOfHour16\": 2.623258,\r\n    \"PriceOfHour17\": 3.6836982,\r\n    \"PriceOfHour18\": 4.0540056,\r\n    \"PriceOfHour19\": 4.3685274,\r\n    \"PriceOfHour20\": 4.179141,\r\n    \"PriceOfHour21\": 3.889912,\r\n    \"PriceOfHour22\": 3.6065977,\r\n    \"PriceOfHour23\": 3.1162534\r\n  }\r\n}\0";
	char* result;
	int lenght = strlen(price) + 1;
	result = (char*)malloc(lenght);
	strncpy(result, price, lenght);

	return result;
}

int getinput(int port)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (port == 0)
		return timeinfo->tm_hour;
	else
		return timeinfo->tm_min;
}

char* strfind(const char* haystack, const char* needle, int offset)
{
	const char* res = strstr(haystack, needle);
	// if not found, return -1
	if (res == NULL)
		return -1;
	// else return the offset in haystack
	return res - haystack;
}

char* getinputtext(int port)
{
	char* price = "{\r\n  \"ScoreNow\": 22,\r\n  \"HourNow\": 8,\r\n  \"PriceNow\": 4.1345735,\r\n  \"PriceUnit\": \"NOK\/kWh\",\r\n  \"HourScores\": {\r\n    \"ScoreOfHour0\": 1,\r\n    \"ScoreOfHour1\": 4,\r\n    \"ScoreOfHour2\": 3,\r\n    \"ScoreOfHour3\": 2,\r\n    \"ScoreOfHour4\": 5,\r\n    \"ScoreOfHour5\": 6,\r\n    \"ScoreOfHour6\": 15,\r\n    \"ScoreOfHour7\": 21,\r\n    \"ScoreOfHour8\": 22,\r\n    \"ScoreOfHour9\": 18,\r\n    \"ScoreOfHour10\": 14,\r\n    \"ScoreOfHour11\": 11,\r\n    \"ScoreOfHour12\": 8,\r\n    \"ScoreOfHour13\": 9,\r\n    \"ScoreOfHour14\": 10,\r\n    \"ScoreOfHour15\": 7,\r\n    \"ScoreOfHour16\": 12,\r\n    \"ScoreOfHour17\": 17,\r\n    \"ScoreOfHour18\": 20,\r\n    \"ScoreOfHour19\": 24,\r\n    \"ScoreOfHour20\": 23,\r\n    \"ScoreOfHour21\": 19,\r\n    \"ScoreOfHour22\": 16,\r\n    \"ScoreOfHour23\": 13\r\n  },\r\n  \"HourPrices\": {\r\n    \"PriceOfHour0\": 0.88227224,\r\n    \"PriceOfHour1\": 1.0211757,\r\n    \"PriceOfHour2\": 0.9696734,\r\n    \"PriceOfHour3\": 0.91398954,\r\n    \"PriceOfHour4\": 1.0349437,\r\n    \"PriceOfHour5\": 1.8353221,\r\n    \"PriceOfHour6\": 3.5773277,\r\n    \"PriceOfHour7\": 4.0668554,\r\n    \"PriceOfHour8\": 4.1345735,\r\n    \"PriceOfHour9\": 3.7363222,\r\n    \"PriceOfHour10\": 3.4642262,\r\n    \"PriceOfHour11\": 2.4794593,\r\n    \"PriceOfHour12\": 2.2932346,\r\n    \"PriceOfHour13\": 2.4155147,\r\n    \"PriceOfHour14\": 2.4211237,\r\n    \"PriceOfHour15\": 2.2671266,\r\n    \"PriceOfHour16\": 2.623258,\r\n    \"PriceOfHour17\": 3.6836982,\r\n    \"PriceOfHour18\": 4.0540056,\r\n    \"PriceOfHour19\": 4.3685274,\r\n    \"PriceOfHour20\": 4.179141,\r\n    \"PriceOfHour21\": 3.889912,\r\n    \"PriceOfHour22\": 3.6065977,\r\n    \"PriceOfHour23\": 3.1162534\r\n  }\r\n}\0";
	char* result;
	int lenght = strlen(price) + 1;
	result = (char*)malloc(lenght);
	strncpy(result, price, lenght);

	return result;
}

void setoutputtext(int port, char value[])
{
	printf("\r\n\r\nText output: %d\r\n%s\r\n", port, value);
}

void setoutput(int output, float value)
{
	printf("%d = %f\r\n", output, value);
}

void sleep(int milliseconds)
{
	Sleep(milliseconds);
}
// ElectricityPriceLoxoneClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <wtypes.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

void setoutput(int output, int value)
{
	printf("%d = %d", output, value);
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


char* httpget(char adress, char page)
{
	return "{\r\n  \"ScoreNow\": 22,\r\n  \"HourNow\": 8,\r\n  \"PriceNow\": 4.1345735,\r\n  \"PriceUnit\": \"NOK\/kWh\",\r\n  \"HourScores\": {\r\n    \"ScoreOfHour0\": 1,\r\n    \"ScoreOfHour1\": 4,\r\n    \"ScoreOfHour2\": 3,\r\n    \"ScoreOfHour3\": 2,\r\n    \"ScoreOfHour4\": 5,\r\n    \"ScoreOfHour5\": 6,\r\n    \"ScoreOfHour6\": 15,\r\n    \"ScoreOfHour7\": 21,\r\n    \"ScoreOfHour8\": 22,\r\n    \"ScoreOfHour9\": 18,\r\n    \"ScoreOfHour10\": 14,\r\n    \"ScoreOfHour11\": 11,\r\n    \"ScoreOfHour12\": 8,\r\n    \"ScoreOfHour13\": 9,\r\n    \"ScoreOfHour14\": 10,\r\n    \"ScoreOfHour15\": 7,\r\n    \"ScoreOfHour16\": 12,\r\n    \"ScoreOfHour17\": 17,\r\n    \"ScoreOfHour18\": 20,\r\n    \"ScoreOfHour19\": 24,\r\n    \"ScoreOfHour20\": 23,\r\n    \"ScoreOfHour21\": 19,\r\n    \"ScoreOfHour22\": 16,\r\n    \"ScoreOfHour23\": 13\r\n  },\r\n  \"HourPrices\": {\r\n    \"PriceOfHour0\": 0.88227224,\r\n    \"PriceOfHour1\": 1.0211757,\r\n    \"PriceOfHour2\": 0.9696734,\r\n    \"PriceOfHour3\": 0.91398954,\r\n    \"PriceOfHour4\": 1.0349437,\r\n    \"PriceOfHour5\": 1.8353221,\r\n    \"PriceOfHour6\": 3.5773277,\r\n    \"PriceOfHour7\": 4.0668554,\r\n    \"PriceOfHour8\": 4.1345735,\r\n    \"PriceOfHour9\": 3.7363222,\r\n    \"PriceOfHour10\": 3.4642262,\r\n    \"PriceOfHour11\": 2.4794593,\r\n    \"PriceOfHour12\": 2.2932346,\r\n    \"PriceOfHour13\": 2.4155147,\r\n    \"PriceOfHour14\": 2.4211237,\r\n    \"PriceOfHour15\": 2.2671266,\r\n    \"PriceOfHour16\": 2.623258,\r\n    \"PriceOfHour17\": 3.6836982,\r\n    \"PriceOfHour18\": 4.0540056,\r\n    \"PriceOfHour19\": 4.3685274,\r\n    \"PriceOfHour20\": 4.179141,\r\n    \"PriceOfHour21\": 3.889912,\r\n    \"PriceOfHour22\": 3.6065977,\r\n    \"PriceOfHour23\": 3.1162534\r\n  }\r\n}";
}


enum OutputPorts
{
	ScoreNow,        // AQ1
	HourNow,            // AQ2
	PriceNow             // AQ3
};

int GetIntValue(char* result, char* name, int def)
{
	int value = def;

	int pos = strfind(result, name, 0);

	if (pos > 0)
	{
		char* stemp = calloc(1, 10);
		int lenName = strlen(name);

		strncpy(stemp, result + pos + lenName, 5);

		value = atoi(stemp);

		free(stemp);
		stemp = 0;
	}

	printf("%s = %d", name, value);

	return value;
}
int main() {

	while (TRUE)
	{
		char* host = "electricitypriceapi.azurewebsites.net";
		char* page = "/api/PriceScoreToday?area=no2&currency=NOK";

		char* result = httpget(host, page);

		printf("%s", result);

		if (result != 0)
		{
			int scoreNow = GetIntValue(result, "\"ScoreNow\":", -100);

			if (scoreNow != -100)
			{
				setoutput(ScoreNow, scoreNow);
			}

			int priceNow = GetIntValue(result, "\"PriceNow\":", -100);

			if (priceNow != -100)
			{
				setoutput(PriceNow, priceNow);
			}

			free(result);
		}

		// Slow the loop down 10 minutes
		int sleepTime = 10 * 60 * 1000;
		//sleep(sleepTime);
	}

	return 0;
}

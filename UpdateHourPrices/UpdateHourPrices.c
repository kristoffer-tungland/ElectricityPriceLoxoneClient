#include "../Loxone.Common/loxone.h"
#include <wtypes.h>
#include <stdio.h>
#include <string.h>

// Copy script from here

enum OutputPorts
{
	ScoreNow,        // AQ1
	HourNow,            // AQ2
	PriceNow             // AQ3
};

int getHourNow()
{
	return getinput(0);
}

int getMinuteNow()
{
	return getinput(1);
}

float readvalue(char* result, char* name)
{
	float value = -100;

	int pos = strfind(result, name, 0);

	printf("strfind: %d", pos);

	if (pos > 0)
	{
		char* stemp = calloc(1, 10);
		int lenName = strlen(name);
		printf("lenName: %d", lenName);

		strncpy(stemp, result + pos + lenName, 9);

		printf("stemp: %s", stemp);

		value = atof(stemp);

		free(stemp);
		stemp = 0;
	}

	printf("%s = %f\r\n", name, value);

	return value;
}

int main() {

	int lastHour = -1;
	int retry = 0;

	while (TRUE)
	{
		int hourNow = getHourNow();
		int minuteNow = getMinuteNow();

		if (lastHour != hourNow || retry == 1)
		{
			lastHour = hourNow;
			retry = 0;

			char* scores = getinputtext(0);

			printf("%s", scores);

			setoutput(HourNow, hourNow);

			char scoreOfHour[80];
			sprintf(scoreOfHour, "\"ScoreOfHour%d\": ", hourNow);

			float score = readvalue(scores, scoreOfHour);

			if (score != -100)
			{
				setoutput(ScoreNow, score);
			}
			else
			{
				retry = 1;
			}

			char* prices = getinputtext(1);

			char priceOfHour[80];
			sprintf(priceOfHour, "\"PriceOfHour%d\": ", hourNow);

			float price = readvalue(prices, priceOfHour);

			if (price != -100)
			{
				setoutput(PriceNow, price);
			}
			else
			{
				retry = 1;
			}
		}

		// Slow the loop down 1 minutes
		int sleepTime = 1 * 60 * 1000;
		sleep(sleepTime);
	}

	return 0;
}

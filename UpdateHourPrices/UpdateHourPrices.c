#include "../Loxone.Common/loxone.h"
#include "../Loxone.Common/loxoneExtended.h"
#include "../Loxone.Common/loxoneHttp.h"
#include "../Loxone.Common/loxoneTime.h"
#include "../Loxone.Common/loxoneSps.h"

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

// Delete main
int main() {
// Delete main

int lastHour = -1;
int retry = 0;

unsigned int time = getcurrenttime();
int year = getyear(time, 1);
int month = getmonth(time, 1);
int day = getday(time, 1);
int hour = gethour(time, 1);
unsigned int customtime = gettimeval(2022, 10, 29, 13, 27, 0, 1);

char* response = httpget("https://electricitypriceapi.azurewebsites.net", "/api/AveragePrices?area=no2&currency=NOK&format=xml");

char* average = getxmlvalue(response, 0, "Today");

float input0 = getinput(0);

printf("%f", input0);

setlogtext(average);

free(response);
free(average);

while (TRUE)
{
	int hourNow = gethour(time, 1);
	int minuteNow = getminute(time, 1);

	if (lastHour != hourNow || retry == 1)
	{
		lastHour = hourNow;
		retry = 0;

		char* scores = getinputtext(0);

		printf("%s", scores);

		setoutput(HourNow, hourNow);

		char scoreOfHour[20];
		sprintf(scoreOfHour, "\"ScoreOfHour%d\": ", hourNow);

		float score = readvalue(scores, scoreOfHour);

		free(scores);

		if (score != -100)
		{
			setoutput(ScoreNow, score);
		}
		else
		{
			retry = 1;
		}

		char* prices = getinputtext(1);

		char priceOfHour[20];
		sprintf(priceOfHour, "\"PriceOfHour%d\": ", hourNow);

		float price = readvalue(prices, priceOfHour);

		free(prices);

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

// Delete main end
}
// Delete main end

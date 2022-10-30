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
	ScoreNow			= 0, // AQ1
	PriceNow			= 1, // AQ2
	AverageToday		= 2, // AQ3
	AverageMonth		= 3, // AQ4
	AverageLast31Days	= 4, // AQ5
};

enum Days {
	Today,
	Tomorrow
};

char* getRequest(char* endpoint)
{
	char* host = "electricitypriceapi.azurewebsites.net";

	char* result = httpget(host, endpoint);

	if (result != 0) {
		return result;
	}

	return 0;
}

char* getAveragePrices(char* area, char* currency)
{
	char endpoint[60];
	sprintf(endpoint, "/api/AveragePrices?area=%s&currency=%s&format=xml", area, currency);
	return getRequest(endpoint);
}

char* getTodaysPrice(char* area, char* currency)
{
	char endpoint[60];
	sprintf(endpoint, "/api/PriceScoreToday?area=%s&currency=%s&format=xml", area, currency);
	return getRequest(endpoint);
}

char* getTomorowsPrice(char* area, char* currency)
{
	char endpoint[60];
	sprintf(endpoint, "/api/PriceScoreTomorrow?area=%s&currency=%s&format=xml", area, currency);
	return getRequest(endpoint);
}

void setOutputFromXml(char* xml, char* name, int output) {
	char* strvalue = getxmlvalue(xml, 0, name);
	float value = -1;

	if (strvalue != NULL) {
		value = atof(strvalue);
	}

	free(strvalue);

	setoutput(output, value);
}

void setVirtualOutputFromXml(char* xml, char* name, char* output) {
	char* strvalue = getxmlvalue(xml, 0, name);
	float value = -1;

	if (strvalue != NULL) {
		value = atof(strvalue);
	}

	free(strvalue);

	setio(output, value);
}

void setVirtualOutputs(char* xml, char* prefix, int day) {
	char* daystr;

	if (day == Today) {
		daystr = "Today";
	}
	else {
		daystr = "Tomorrow";
	}
	
	for (int i = 0; i < 24; i++) {
		char name[20];
		sprintf(name, "%s%d", prefix, i);

		char outputName[30];
		sprintf(outputName, "%s%d%s", prefix, i, daystr);

		setVirtualOutputFromXml(xml, name, outputName);
	}
}

void updateOutputs(char* prefix, int hourNow, char* xmlToday, char* xmlTomorrow, int output) {
	char name[20];
	sprintf(name, "%s%d", prefix, hourNow);
	
	setOutputFromXml(xmlToday, name, output);

	setVirtualOutputs(xmlToday, prefix, Today);
	setVirtualOutputs(xmlTomorrow, prefix, Tomorrow);
}

void updateAverage(char* xml) {
	char averageToday[20] = "Today";
	setOutputFromXml(xml, averageToday, AverageToday);

	char averageTodayMonth[20] = "Month";
	setOutputFromXml(xml, averageTodayMonth, AverageMonth);

	char averageLast31days[20] = "Last31Days";
	setOutputFromXml(xml, averageLast31days, AverageLast31Days);
}

void printOutPutInformation() {
	setoutputtext(0, "\
ScoreNow		= 0, // AQ1\r\n\
PriceNow		= 1, // AQ2\r\n\
AverageToday		= 2, // AQ3\r\n\
AverageMonth		= 3, // AQ4\r\n\
AverageLast31Days	= 4, // AQ5");
}

// Delete main
int main() {
// Delete main

int lastHour = -1;

printOutPutInformation();

char* area = "no2";
char* currency = "NOK";

int todayRefreshed = 0;
int averageRefreshed = 0;

char* todaysPrice = getTodaysPrice(area, currency);
if (todaysPrice != 0) {
	todayRefreshed = 1;
	setlogtext(todaysPrice);
}
char* averagePrices = getAveragePrices(area, currency);
if (averagePrices != 0) {
	averageRefreshed = 1;
	setlogtext(averagePrices);
}

unsigned int time = getcurrenttime();
int hourNow = gethour(time, 1);

char* tomorowsPrice = 0;

if (hourNow > 14) {
	tomorowsPrice = getTomorowsPrice(area, currency);

	if (tomorowsPrice != 0) {
		setlogtext(tomorowsPrice);
	}
}

while (TRUE)
{
	unsigned int time = getcurrenttime();
	hourNow = gethour(time, 1);
	int minuteNow = getminute(time, 1);

	if (hourNow > 23 && minuteNow > 58)
	{
		free(tomorowsPrice);
		tomorowsPrice = 0;
		todayRefreshed = 0;
		averageRefreshed = 0;
	}

	if (hourNow > 14 && tomorowsPrice == 0)
	{
		free(tomorowsPrice);
		tomorowsPrice = getTomorowsPrice(area, currency);
		if (tomorowsPrice != 0) {
			setlogtext(tomorowsPrice);
		}
	}

	if (hourNow == 23 && minuteNow > 30 && todayRefreshed == 0 && tomorowsPrice != 0)
	{
		free(todaysPrice);
		todaysPrice = tomorowsPrice;
		setlogtext(todaysPrice);
		todayRefreshed = 1;
	}

	if (hourNow == 0 && todayRefreshed == 0)
	{
		free(todaysPrice);
		todaysPrice = getTodaysPrice(area, currency);
		if (todaysPrice != 0) {
			setlogtext(todaysPrice);
			todayRefreshed = 1;
		}
	}

	if (hourNow == 23 && minuteNow > 30 && averageRefreshed == 0)
	{
		free(averagePrices);
		averagePrices = getAveragePrices(area, currency);

		if (averagePrices != 0) {
			setlogtext(averagePrices);
			averageRefreshed = 1;
		}
	}

	if (lastHour != hourNow)
	{
		lastHour = hourNow;

		updateOutputs("ScoreOfHour", hourNow, todaysPrice, tomorowsPrice, ScoreNow);
		updateOutputs("PriceOfHour", hourNow, todaysPrice, tomorowsPrice, PriceNow);
		updateAverage(averagePrices);
	}

	// Slow down for 1 second
	sleeps(1);
}

// Delete main end
}
// Delete main end

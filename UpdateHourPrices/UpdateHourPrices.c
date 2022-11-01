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
	AverageWeek			= 3, // AQ4
	AverageMonth		= 4, // AQ5
	AverageLast7Days	= 5, // AQ6
	AverageLast31Days	= 6, // AQ7
};

void printOutPutInformation() {
	setoutputtext(0, "\
OUTPUTS:\r\n\
Score now			AQ1\r\n\
Price now			AQ2\r\n\
Average today			AQ3\r\n\
Average this week		AQ4\r\n\
Average this month		AQ5\r\n\
Average last 7 days		AQ6\r\n\
Average last 31 days		AQ7\r\n\
\r\n\
VIRTUAL OUTPUTS:\r\n\
ScoreOfHour[NN]Today\r\n\
ScoreOfHour[NN]Tomorrow\r\n\
");
}

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

float getValueFromXml(char* xml, char* name) {
	float value = -1;

	if (xml == NULL) {
		return value;
	}

	char* strvalue = getxmlvalue(xml, 0, name);

	if (strvalue != NULL) {
		value = atof(strvalue);
		free(strvalue);
		strvalue = NULL;
	}

	return value;
}

void setOutputFromXml(char* xml, char* name, int output) {
	float value = getValueFromXml(xml, name);
	setoutput(output, value);
}

void setVirtualOutputFromXml(char* xml, char* name, char* output) {
	float value = getValueFromXml(xml, name);
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

	char averageWeekMonth[20] = "Week";
	setOutputFromXml(xml, averageWeekMonth, AverageWeek);

	char averageTodayMonth[20] = "Month";
	setOutputFromXml(xml, averageTodayMonth, AverageMonth);

	char averageLast7days[20] = "Last7Days";
	setOutputFromXml(xml, averageLast7days, AverageLast7Days);

	char averageLast31days[20] = "Last31Days";
	setOutputFromXml(xml, averageLast31days, AverageLast31Days);
}

// Delete main
int main() {
// Delete main

int lastHour = -1;

printOutPutInformation();

char* area = "no2";
char* currency = "NOK";

int todayRefreshed = FALSE;
int todayCopied = FALSE;
int averageRefreshed = FALSE;

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

	if (hourNow == 23 && minuteNow > 58)
	{
		free(tomorowsPrice);
		tomorowsPrice = NULL;


		if (todayCopied == TRUE) {
			todayRefreshed == TRUE;
		}
		else {
			todayRefreshed = FALSE;
		}
		todayCopied = FALSE;

		averageRefreshed = FALSE;
	}

	if (hourNow >= 14 && hourNow < 23 && tomorowsPrice == NULL)
	{
		free(tomorowsPrice);
		tomorowsPrice = getTomorowsPrice(area, currency);
		if (tomorowsPrice != NULL) {
			setlogtext(tomorowsPrice);
		}
	}

	if (hourNow == 23 && minuteNow > 30 && tomorowsPrice != NULL)
	{
		free(todaysPrice);
		todaysPrice = malloc(strlen(tomorowsPrice) + 1);
		if (todaysPrice != NULL) {
			strcpy(todaysPrice, tomorowsPrice);
			setlogtext(todaysPrice);
			todayCopied = TRUE;
		}
	}

	if (hourNow == 0 && todayRefreshed == FALSE)
	{
		free(todaysPrice);
		todaysPrice = getTodaysPrice(area, currency);
		if (todaysPrice != NULL) {
			setlogtext(todaysPrice);
			todayRefreshed = TRUE;
		}
	}

	if (hourNow == 0 && averageRefreshed == FALSE)
	{
		free(averagePrices);
		averagePrices = getAveragePrices(area, currency);

		if (averagePrices != NULL) {
			setlogtext(averagePrices);
			averageRefreshed = TRUE;
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

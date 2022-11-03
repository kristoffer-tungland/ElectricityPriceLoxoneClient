#include "../Loxone.Common/loxone.h"
#include "../Loxone.Common/loxoneExtended.h"
#include "../Loxone.Common/loxoneHttp.h"
#include "../Loxone.Common/loxoneTime.h"
#include "../Loxone.Common/loxoneSps.h"

#include <wtypes.h>
#include <stdio.h>
#include <string.h>

// Copy script from here
enum InputPorts {
	PriceFactor = 0 // I1
};

enum OutputPorts {
	ScoreNow			= 0, // O1
	PriceNow			= 1, // O2
	AverageToday		= 2, // O3
	AverageWeek			= 3, // O4
	AverageMonth		= 4, // O5
	AverageLast7Days	= 5, // O6
	AverageLast31Days	= 6  // O7
};

void printOutPutInformation() {
	setoutputtext(0, "\
INPUTS:\r\n\
I1 - Price factor\r\n\
OUTPUTS:\r\n\
O1 - Score now\r\n\
O2 - Price now\r\n\
O3 - Average today\r\n\
O4 - Average this week\r\n\
O5 - Average this month\r\n\
O6 - Average last 7 days\r\n\
O7 - Average last 31 days\r\n\
\r\n\
\r\n\
VIRTUAL OUTPUTS:\r\n\
ScoreOfHour[NN]Today\r\n\
PriceOfHour[NN]Tomorrow\r\n\
ScoreOfHour[NN]Today\r\n\
PriceOfHour[NN]Tomorrow\r\n");
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

void setOutputFromXml(char* xml, char* name, int output, float factor) {
	float value = getValueFromXml(xml, name);
	if (value > 0) {
		value = value * factor;
	}
	
	setoutput(output, value);
}

void setVirtualOutputFromXml(char* xml, char* name, char* output, float factor) {
	float value = getValueFromXml(xml, name);
	if (value > 0) {
		value = value * factor;
	}
	setio(output, value);
}

void setVirtualOutputs(char* xml, char* prefix, int day, float factor) {
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

		setVirtualOutputFromXml(xml, name, outputName, factor);
	}
}

void updateOutputs(char* prefix, int hourNow, char* xmlToday, char* xmlTomorrow, int output, float factor) {
	char name[20];
	sprintf(name, "%s%d", prefix, hourNow);
	
	setOutputFromXml(xmlToday, name, output, factor);
	setVirtualOutputs(xmlToday, prefix, Today, factor);
	setVirtualOutputs(xmlTomorrow, prefix, Tomorrow, factor);
}

void updateAverage(char* xml, float factor) {
	char averageToday[20] = "Today";
	setOutputFromXml(xml, averageToday, AverageToday, factor);

	char averageWeekMonth[20] = "Week";
	setOutputFromXml(xml, averageWeekMonth, AverageWeek, factor);

	char averageTodayMonth[20] = "Month";
	setOutputFromXml(xml, averageTodayMonth, AverageMonth, factor);

	char averageLast7days[20] = "Last7Days";
	setOutputFromXml(xml, averageLast7days, AverageLast7Days, factor);

	char averageLast31days[20] = "Last31Days";
	setOutputFromXml(xml, averageLast31days, AverageLast31Days, factor);
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
	time = getcurrenttime();
	hourNow = gethour(time, 1);
	int minuteNow = getminute(time, 1);

	if (hourNow == 23 && minuteNow > 58)
	{
		free(tomorowsPrice);
		tomorowsPrice = NULL;


		if (todayCopied == TRUE) {
			todayRefreshed = TRUE;
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

	if (hourNow == 23 && minuteNow > 30 && tomorowsPrice != NULL && todayCopied == FALSE)
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

	if (hourNow == 0 && minuteNow > 1 && averageRefreshed == FALSE)
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

		float factor = getinput(PriceFactor);

		if (factor == 0) {
			factor = 1;
		}

		updateOutputs("ScoreOfHour", hourNow, todaysPrice, tomorowsPrice, ScoreNow, 1);
		updateOutputs("PriceOfHour", hourNow, todaysPrice, tomorowsPrice, PriceNow, factor);
		updateAverage(averagePrices, factor);
	}

	// Slow down for 1 second
	sleeps(1);
}

// Delete main end
}
// Delete main end
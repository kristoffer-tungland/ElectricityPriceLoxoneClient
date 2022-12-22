# Electricity Price Loxone Client

This is a pico C script developed for Loxone home automation system for use in program blocks. 
It reads electrical prices from an API and outputs the prices at the program blocks outputs and 
optional virtual outputs.

## Script

```c
// UpdateHourPrices/UpdateHourPrices.picoc

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
I1 - Price factor (optional) default=1\r\n\
OUTPUTS:\r\n\
O1 - Score now (between 1-24)\r\n\
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
PriceOfHour[NN]Tomorrow\r\n\
PriceOfHour[NN]Tomorrow\r\n\
ScoreIn[NN]Hours\r\n\
PriceIn[NN]Hours\r\n");
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

char* generateXmlName(char* prefix, int hour) {
	char* name;
	name = (char*)malloc(20);

	if (name != NULL) {
		sprintf(name, "%sOfHour%d", prefix, hour);
	}

	return name;
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
		char* name = generateXmlName(prefix, i);

		char outputName[30];
		sprintf(outputName, "%sOfHour%d%s", prefix, i, daystr);

		setVirtualOutputFromXml(xml, name, outputName, factor);
		free(name);
	}
}

void updateOutputs(char* prefix, int hourNow, char* xmlToday, char* xmlTomorrow, int output, float factor) {
	char* name = generateXmlName(prefix, hourNow);
	
	setOutputFromXml(xmlToday, name, output, factor);
	free(name);
	setVirtualOutputs(xmlToday, prefix, Today, factor);
	setVirtualOutputs(xmlTomorrow, prefix, Tomorrow, factor);
}


void updateAhedPrices(char* prefix, int hourNow, char* xmlToday, char* xmlTomorrow, float factor) {
	for (int i = 1; i < 13; i++) {
		int hour = i + hourNow;
		int tomorrow = FALSE;

		if (hour > 23) {
			hour = hour - 24;
			tomorrow = TRUE;
		}

		char* name = generateXmlName(prefix, hour);

		char outputName[30];
		sprintf(outputName, "%sIn%dHours", prefix, i);

		if (tomorrow == TRUE) {
			setVirtualOutputFromXml(xmlTomorrow, name, outputName, factor);
		}
		else {
			setVirtualOutputFromXml(xmlToday, name, outputName, factor);
		}

		free(name);
	}
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

int update(int lastHour, int hourNow, char* todaysPrice, char* tomorowsPrice, char* averagePrices)
{
	if (lastHour != hourNow)
	{
		float factor = getinput(PriceFactor);

		if (factor == 0) {
			factor = 1;
		}

		updateOutputs("Score", hourNow, todaysPrice, tomorowsPrice, ScoreNow, 1);
		updateOutputs("Price", hourNow, todaysPrice, tomorowsPrice, PriceNow, factor);
		updateAverage(averagePrices, factor);
		updateAhedPrices("Score", hourNow, todaysPrice, tomorowsPrice, 1);
		updateAhedPrices("Price", hourNow, todaysPrice, tomorowsPrice, factor);

		return TRUE;
	}

	return FALSE;
}


int lastHour = -1;

printOutPutInformation();

char* area = "no2";
char* currency = "NOK";

int todayRefreshed = FALSE;
int averageRefreshed = FALSE;

char* todaysPrice = getTodaysPrice(area, currency);
if (todaysPrice != 0) {
	setlogtext(todaysPrice);
}
char* averagePrices = getAveragePrices(area, currency);
if (averagePrices != 0) {
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

if (update(lastHour, hourNow, todaysPrice, tomorowsPrice, averagePrices) == TRUE)
{
	lastHour = hourNow;
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
		todayRefreshed = FALSE;
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

	if (hourNow >= 23 && minuteNow > 30 && minuteNow < 58 && todayRefreshed == FALSE)
	{
		free(todaysPrice);
		todaysPrice = getTomorowsPrice(area, currency);
		if (todaysPrice != NULL) {
			setlogtext(todaysPrice);
			todayRefreshed = TRUE;
		}
		else if (tomorowsPrice != NULL) {
			todaysPrice = (char*)malloc(strlen(tomorowsPrice) + 1);
			if (todaysPrice != NULL) {
				strcpy(todaysPrice, tomorowsPrice);
				setlogtext(todaysPrice);
				todayRefreshed = TRUE;
			}
		}
	}

	if (hourNow >= 23 && minuteNow > 30 && minuteNow < 58 && averageRefreshed == FALSE)
	{
		free(averagePrices);
		averagePrices = getAveragePrices(area, currency);

		if (averagePrices != NULL) {
			setlogtext(averagePrices);
			averageRefreshed = TRUE;
		}
	}

	if (update(lastHour, hourNow, todaysPrice, tomorowsPrice, averagePrices) == TRUE)
	{
		lastHour = hourNow;
	}

	// Slow down for 1 second
	sleeps(1);
}
```

## Electricity Price API
[https://electricitypriceapi.azurewebsites.net](https://electricitypriceapi.azurewebsites.net/api/swagger/ui)

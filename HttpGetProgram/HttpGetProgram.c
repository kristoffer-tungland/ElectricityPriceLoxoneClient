#include "../Loxone.Common/loxone.h"
#include <wtypes.h>
#include <stdio.h>
#include <string.h>

// Copy script from here

void setHourScores(char* result, int hourScorePos, int hourPricesPos)
{
	int lenght = hourPricesPos - hourScorePos;
	char hourScore[1000];

	strncpy(hourScore, result + hourScorePos, lenght);
	hourScore[lenght] = '\0';

	setoutputtext(0, hourScore);
}

void setHourPrices(char* result, int hourPricesPos)
{
	int resultLenght = strlen(result);
	int lenght = resultLenght - hourPricesPos;
	char hourPrice[1000];

	strncpy(hourPrice, result + hourPricesPos, lenght);
	hourPrice[lenght] = '\0';

	setoutputtext(1, hourPrice);
}


void splitOutputs(char* result)
{
	int hourScorePos = strfind(result, "\"HourScores\":", 0);
	int hourPricesPos = strfind(result, "\"HourPrices\":", 0);

	if (hourScorePos > 0 && hourPricesPos > 0)
	{
		setHourScores(result, hourScorePos, hourPricesPos);
		setHourPrices(result, hourPricesPos);
	}
}

void setCurrency(char* result)
{
	char* priceUnitKey = "\"PriceUnit\": \"";
	int priceUnitPos = strfind(result, priceUnitKey, 0);
	char* unit = "/kWh";
	int unitPos = strfind(result, unit, 0);

	if (priceUnitPos > 0 && unitPos > 0)
	{
		int priceUnitLenght = strlen(priceUnitKey);
		int unitLenght = strlen(unit);
		int lenght = (unitPos + unitLenght) - (priceUnitPos + priceUnitLenght);
		char priceUnit[8];

		strncpy(priceUnit, result + priceUnitPos + priceUnitLenght, lenght);
		priceUnit[lenght] = '\0';

		setoutputtext(2, priceUnit);
	}
}

void getPrice(char* endpoint)
{
	char* host = "electricitypriceapi.azurewebsites.net";

	char* result = httpget(host, endpoint);

	if (result != 0)
	{
		splitOutputs(result);
		setCurrency(result);
	}

	free(result);
}

void getTodaysPrice(char* area, char* currency)
{
	char endpoint[60];
	sprintf(endpoint, "/api/PriceScoreToday?area=%s&currency=%s", area, currency);
	getPrice(endpoint);
}

void getTomorowsPrice(char* area, char* currency)
{
	char endpoint[60];
	sprintf(endpoint, "/api/PriceScoreTomorrow?area=%s&currency=%s", area, currency);
	getPrice(endpoint);
}

int getHourNow()
{
	return getinput(0);
}

int getMinuteNow()
{
	return getinput(1);
}

// Delete main
int main() {
// Delete main

char* area = "no2";
char* currency = "NOK";

int refreshed = 0;

getTodaysPrice(area, currency);

while (TRUE)
{
	int hourNow = getHourNow();
	int minuteNow = getMinuteNow();

	if (refreshed == 1 && hourNow == 0)
	{
		refreshed = 0;
	}

	if (hourNow == 23 && minuteNow > 30 && refreshed == 0)
	{
		getTomorowsPrice(area, currency);
		refreshed = 1;
	}

	// Slow the loop down 10 minutes
	int sleepTime = 10 * 60 * 1000;
	sleep(sleepTime);
}

// Delete main end
}
// Delete main end

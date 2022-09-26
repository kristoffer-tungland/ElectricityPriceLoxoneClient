#include "../Loxone.Common/loxone.h"
#include <wtypes.h>
#include <stdio.h>
#include <string.h>

// Copy script from here

void setHourScores(char* result, int hourScorePos, int hourPricesPos)
{
	int lenght = hourPricesPos - hourScorePos;
	char* hourScore = calloc(1, lenght * sizeof(char));

	strncpy(hourScore, result + hourScorePos, lenght);

	printf("hourScore:\r\n%s\r\n", hourScore);

	setoutputtext(0, hourScore);

	free(hourScore);
	hourScore = 0;
}

void setHourPrices(char* result, int hourPricesPos)
{
	int resultLenght = strlen(result);
	int lenght = resultLenght - hourPricesPos;
	char* hourPrice = calloc(1, lenght * sizeof(char));

	strncpy(hourPrice, result + hourPricesPos, lenght);

	printf("hourPrice:\r\n%s\r\n", hourPrice);

	setoutputtext(1, hourPrice);

	free(hourPrice);
	hourPrice = 0;
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

void getPrice(char* endpoint)
{
	char* host = "electricitypriceapi.azurewebsites.net";

	char* result = httpget(host, endpoint);

	if (result != 0)
	{
		splitOutputs(result);
	}

	free(result);
}

void getTodaysPrice()
{
	char* endpoint = "/api/PriceScoreToday?area=no2&currency=NOK";
	getPrice(endpoint);
}

void getTomorowsPrice()
{
	char* endpoint = "/api/PriceScoreTomorrow?area=no2&currency=NOK";
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

int refreshed = 0;

getTodaysPrice();

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
		getTomorowsPrice();
		refreshed = 1;
	}

	// Slow the loop down 10 minutes
	int sleepTime = 10 * 60 * 1000;
	sleep(sleepTime);
}

// Delete main end
}
// Delete main end

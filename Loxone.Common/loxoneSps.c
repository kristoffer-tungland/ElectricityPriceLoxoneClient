#include "loxoneSps.h"
#include "inputMock.h"
#include "stringHelpers.h"

#include <stdio.h>
#include <string.h>
#include <wtypes.h>

void setlogtext(char* str)
{
	printf("Log text:\r\n%s\r\n\r\n", str);
}

float getio(char* str)
{
	return getiomock(str);
}

int setio(char* str, float value)
{
	printf("Output %s: %f\r\n", str, value);

	return 0;
}

int getinputevent()
{
	return getinputeventmock();
}

float getinput(int input)
{
	return getinputmock(input);
}

char* getinputtext(int input)
{
	char* inputtext = getinputtextmock(input);
	char* result;
	int lenght = strlen(inputtext) + 1;
	result = (char*)malloc(lenght);
	strlcpy(result, inputtext, lenght);

	return result;
}

void setoutput(int output, float value)
{
	printf("Output %d: %f\r\n", output, value);
}

void setoutputtext(int output, char* str)
{
	printf("Text output %d:\r\n%s\r\n\r\n", output, str);
}
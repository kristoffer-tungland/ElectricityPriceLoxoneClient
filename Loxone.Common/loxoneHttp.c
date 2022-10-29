#include "loxoneHttp.h"
#include "stringHelpers.h"
#include "inputMock.h"

#include <stdio.h>
#include <string.h>
#include <wtypes.h>

char* httpget(char* adress, char* page)
{
	char* price = httpgetmock(adress, page); 
	char* result;
	int lenght = strlen(price)+1;
	result = (char*)malloc(lenght);
	strlcpy(result, price, lenght);

	return result;
}

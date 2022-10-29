#include "../Loxone.Common/inputMock.h"

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

float getiomock(char* str)
{
	if		(strstr(str, "VI1") != NULL) { return 0.0f; } // VI1 Virtual input 1
	else if (strstr(str, "VI2") != NULL) { return 0.0f; } // VI2 Virtual input 2

	return 0.0f;
}

int getinputeventmock()
{
	return 0x02; // Input 2 has changed
}

float getinputmock(int input)
{
	if		(input ==  0) { return 0.0f; } // Input  1
	else if (input ==  1) { return 0.0f; } // Input  2
	else if (input ==  2) { return 0.0f; } // Input  3
	else if (input ==  3) { return 0.0f; } // Input  4
	else if (input ==  4) { return 0.0f; } // Input  5
	else if (input ==  5) { return 0.0f; } // Input  6
	else if (input ==  6) { return 0.0f; } // Input  7
	else if (input ==  7) { return 0.0f; } // Input  8
	else if (input ==  8) { return 0.0f; } // Input  9
	else if (input ==  9) { return 0.0f; } // Input 10
	else if (input == 10) { return 0.0f; } // Input 11
	else if (input == 11) { return 0.0f; } // Input 12
	else if (input == 12) { return 0.0f; } // Input 13

	return 0.0f;
}

char* getinputtextmock(int input)
{
	if		(input == 0) { return ""; } // Text input 1
	else if (input == 1) { return ""; } // Text input 2
	else if (input == 2) { return ""; } // Text input 3

	return NULL;
}

char* httpgetmock(char* adress, char* page) {
	if (strstr(page, "AveragePrices") != NULL) {
		return "\
<GetAveragePricesResult xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n\
	<Today>1.0248319</Today>\r\n\
	<Month>1.3136463</Month>\r\n\
	<Last31Days>1.4864025</Last31Days>\r\n\
	<PriceUnit>NOK/kWh</PriceUnit>\r\n\
</GetAveragePricesResult>";
	}

	return NULL;
}
#include "loxoneExtended.h"
#include "stringHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int batoi(char* str)
{
	char str1[100];

	int idx = 0, j, k = 0;

	// Iterate String until last
	// leading space character
	while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n')
	{
		idx++;
	}

	// Run a for loop from index until the original
	// string ends and copy the content of str to str1
	for (j = idx; str[j] != '\0'; j++)
	{
		str1[k] = str[j];
		k++;
	}

	// Insert a string terminating character
	// at the end of new string
	str1[k] = '\0';

	return atoi(str1);
}

char* getxmlvalue(char* str, int index, char* name)
{
	int len = 0, pos = 0;
	char openTag[100] = { 0 }; //Opening Tag
	char closeTag[100] = { 0 };//Closing Tag
	int posOpenTag = 0, posClosingTag = 0;
	//check enter buffer
	len = strlen(str);
	if (len <= 0)
	{
		return NULL;
	}
	//Create Opening Tag
	memset(openTag, 0, sizeof(openTag));
	strcpy(openTag, "<");
	strcat(openTag, name);
	strcat(openTag, ">");
	//Create Closing tag
	memset(closeTag, 0, sizeof(closeTag));
	strcpy(closeTag, "</");
	strcat(closeTag, name);
	strcat(closeTag, ">");
	//Get len of open and close tag
	const int lenOpenTag = strlen(openTag);
	const int lenCloseTag = strlen(closeTag);

	int indexCount = 0;
	//Get Opening tag position
	for (pos = 0; pos < len; pos++)
	{
		if (!memcmp(openTag, (str + pos), lenOpenTag))
		{
			if (indexCount != index)
			{
				indexCount = indexCount + 1;
				continue;
			}

			posOpenTag = pos;
			break;
		}
	}
	//Get closing tag position
	for (pos = posOpenTag; pos < len; pos++)
	{
		if (!memcmp(closeTag, (str + pos), lenCloseTag))
		{
			posClosingTag = pos;
			break;
		}
	}
	//get the tag value
	if ((posOpenTag != 0) && (posClosingTag != 0))
	{
		const int lenTagVal = posClosingTag - posOpenTag - lenOpenTag;
		const char* const pStartPosTagVal = str + posOpenTag + lenOpenTag;
		if (lenTagVal)
		{
			char* result;
			result = (char*)malloc(lenTagVal);
			strlcpy(result, pStartPosTagVal, lenTagVal);

			return result;
		}
	}
	return NULL;
}

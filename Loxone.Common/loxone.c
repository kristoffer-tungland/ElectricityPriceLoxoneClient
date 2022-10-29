#include <wtypes.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "loxone.h"


int strfind(const char* haystack, const char* needle, int offset)
{
	const char* res = strstr(haystack, needle);
	// if not found, return -1
	if (res == NULL)
		return -1;
	// else return the offset in haystack
	return res - haystack;
}

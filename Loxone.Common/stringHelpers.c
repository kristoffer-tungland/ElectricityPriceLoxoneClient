#include "stringHelpers.h"
#include <stdio.h>
#include <wtypes.h>

size_t strlcpy(char* dst, const char* src, size_t bufsize)
{
	size_t srclen = strlen(src);
	size_t result = srclen; /* Result is always the length of the src string */
	if (bufsize > 0)
	{
		if (srclen >= bufsize)
			srclen = bufsize - 1;
		if (srclen > 0)
			memcpy(dst, src, srclen);
		dst[srclen] = '\0';
	}
	return result;
}

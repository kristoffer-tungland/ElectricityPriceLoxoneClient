#pragma once
/* Works like the atoi standard C function with the exception that blanks at the beginning of parameter str are allowed. */
int batoi(char* str);

/* Returns the value of name in str, or a null pointer if name is not part of str. */
char* getxmlvalue(char* str, int index, char* name);
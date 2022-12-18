#pragma once
/* Writes the string contained in parameter str to the log window of Loxone Config. */
void setlogtext(char* str);

/* Returns the value of the specified virtual input or a virtual output */
float getio(char* str);

/* Sets the value of the specified virtual input or a virtual output. */
int setio(char* str, float value);

/* Returns a bitmask whitch contains the changes of inputs (bit 0 = first input of object, starts with
text inputs followed by analog inputs).

A return value of 0x02 for example means that input 2 has changed. (see example 1). */
int getinputevent();

/* Returns the value of the analog input specified in parameter input. (0 = first analog input) (see example 1). */
float getinput(int input);

/* Sets the specified analog output to the specified value. (0 = first analog output) (see example 1). */
char* getinputtext(int input);

/* Sets the specified text output to the string specified in parameter str. (0 = first text output) (see example 1). */
void setoutput(int output, float value);

/* Sets the specified text output to the string specified in parameter str. (0= first text output) (see example 1). */
void setoutputtext(int output, char* str);

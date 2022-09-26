#pragma once

void getPrice(char* endpoint);

int getinput(int port);

char* strfind(const char* haystack, const char* needle, int offset);

char* getinputtext(int port);

void setoutputtext(int port, char* value);

void setoutput(int output, float value);

void sleep(int milliseconds);

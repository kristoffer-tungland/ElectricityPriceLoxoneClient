#pragma once
/*Sleep in milliseconds*/
void sleep(int ms);

/*Sleep in seconds*/
void sleeps(int s);

/*Get UTC time in seconds since 1.1. 2009*/
unsigned int getcurrenttime();

int getyear(unsigned int time, int local);
int getmonth(unsigned int time, int local);
int getday(unsigned int time, int local);
int gethour(unsigned int time, int local);
int getminute(unsigned int time, int local);
int getsecond(unsigned int time, int local);
unsigned int gettimeval(int year, int month, int day, int hour, int minutes, int seconds, int local);
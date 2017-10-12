#ifndef _DEFS_H
#define _DEFS_H

// Button pins
#define LED 6
#define MBUT 4
#define UBUT 14
#define DBUT 22
#define RTC_INT 9

#define EVERY_SECOND
//#define EVERY_MINUTE
//#define SLEEP_PROCESSOR

#define MENU_MAIN_INDEX     0

const char months[12][10] PROGMEM = {
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December",
};

const char shortMonths[12][4] PROGMEM = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec",
};



#endif

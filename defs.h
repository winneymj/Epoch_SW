#ifndef _DEFS_H
#define _DEFS_H


#define SCK 19
#define MOSI 18
#define SS 23
#define EXTMODE 28


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
#define MENU_SUB_INDEX      1
#define MENU_SUB_SUB_INDEX  2
#define MENU_CHANNELS_INDEX 3



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

#ifndef _DATETIME_H
#define _DATETIME_H

#include <stdint.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#define SETTING_NOW_NONE  0
#define SETTING_NOW_10HOUR  1
#define SETTING_NOW_1HOUR 2
#define SETTING_NOW_10MIN 3
#define SETTING_NOW_1MIN  4

#define SETTING_NOW_DAY10 5
#define SETTING_NOW_DAY1 6
#define SETTING_NOW_MONTH 7
#define SETTING_NOW_YEAR10 8
#define SETTING_NOW_YEAR1 9

#define OPTION_DATE_INDEX 1
#define OPTION_TIME_INDEX 2


typedef struct{
  byte now;
  byte val;
}s_menuNowSetting;

const char months[12][4] PROGMEM = {
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
  "Dec"
};

inline byte time_dow(int y, byte m, byte d)
{
  static byte t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  y -= m < 3;
  byte dow = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;

  // 0 = Sunday, 1 = Monday, but Monday should be 0
  dow--;
  if(dow == 255) // Overflowed, must have been 0 which is Sunday
    dow = 6;
  return dow;
}

// leap year calulator expects year argument as years offset from 1970
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

// Forward declarations
void dateTimeDownFunc();
void dateTimeUpFunc();
void showDateStr();
void showTimeStr();
void saveTimeFunc();
void timeDraw();
void back();
void dateDraw();




#endif

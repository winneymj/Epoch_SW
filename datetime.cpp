#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <TimeLib.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <DS3232RTC.h>    // http://github.com/JChristensen/DS3232RTC
#include <RTCx.h>         // https://github.com/stevemarple/RTCx

#include "icons.h"
#include "resources.h"

extern Adafruit_SharpMem display;
extern WatchMenu *currentMenu;
extern DS3232RTC MyDS3232;

WatchMenu dateTimeMenu(display);


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

void selectDate()
{
#ifndef SLEEP_PROCESSOR
Serial.println("selectDate(): Enter");
#endif
}

void selectTime()
{
#ifndef SLEEP_PROCESSOR
Serial.println("selectTime(): Enter");
#endif
}

void makeDateStr(char* buff)
{
  char month[4] = {0};
  tmElements_t currTime;
  MyDS3232.read(currTime);

  strcpy_P(month, months[currTime.Month]);
//  sprintf_P(buff, PSTR("%3s%02hhu %s 20%02hhu"), "", currTime.Day, month, currTime.Year);
  sprintf_P(buff, PSTR("%3s%02u %s %02u"), "", currTime.Day, month, currTime.Year);
}

void showDateStr()
{
  char buff[21];
  makeDateStr(buff);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, 1, buff, NULL, selectDate); // Position 1
}

void makeTimeStr(char* buff)
{
  tmElements_t currTime;
  MyDS3232.read(currTime);

  sprintf_P(buff, PSTR("%6s%02u:%02u"), "", currTime.Hour, currTime.Minute);
}

void showTimeStr()
{
  char buff[12];
  makeTimeStr(buff);
//  setMenuOption(3, buff, NULL, selectTime);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, 3, buff, NULL, selectTime); // Position 3
}

void saveTimeFunc()
{
  
}

void dateTimeDownFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuDownFunc(): Enter");
#endif
  dateTimeMenu.downOption();
}

void dateTimeUpFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuUpFunc(): Enter");
#endif
  dateTimeMenu.upOption();
}

void timeFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("timeFunc(): Enter");
#endif
  dateTimeMenu.setTextSize(1);
  
  dateTimeMenu.initMenu(1);  // Create a menu system with ? menu rows
  dateTimeMenu.createMenu(MENU_MAIN_INDEX, 6, PSTR("  < TIME & DATE >"), MENU_TYPE_STR, dateTimeDownFunc, dateTimeUpFunc);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, 5, PSTR("Save"), NULL, saveTimeFunc); // Position 5

  // Point to date/time menu
  currentMenu = &dateTimeMenu;

  showDateStr();
  showTimeStr();

  display.fillRect(0, 64, 128, 128, WHITE); // Clear display
//    display.refresh();
//    bool animating = dateTimeMenu.updateMenu();
//    display.refresh();


  // Create copy of current time & date
//  memcpy(&timeDataSet, &timeData, sizeof(s_time));
//
//  setMenuInfo(OPTION_COUNT, PSTR("  < TIME & DATE >"), MENU_TYPE_STR, mSelect, mUp, mDown);

//  showTimeStr();
//  setMenuOption_P(5, PSTR("Save"), NULL, saveTimeDate);
//  setMenuOption_P(OPTION_EXIT, menuBack, NULL, back);
//
//  setPrevMenuOpen(&prevMenuData, mTimeDateOpen);
//
//  menuData.selected = 1;
//  
//  beginAnimation2(NULL);
#ifndef SLEEP_PROCESSOR
Serial.println("timeFunc(): Exit");
#endif
}


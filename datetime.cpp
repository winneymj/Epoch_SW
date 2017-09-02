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

typedef struct{
  byte now;
  byte val;
}s_menuNowSetting;


extern Adafruit_SharpMem display;
extern WatchMenu *currentMenu;
extern DS3232RTC MyDS3232;

s_menuNowSetting setting;
WatchMenu dateTimeMenu(display);
tmElements_t timeDataSet;

// Forward declarations
void dateTimeDownFunc();
void dateTimeUpFunc();
void showDateStr();


#define SETTING_NOW_NONE  0
#define SETTING_NOW_10HOUR  1
#define SETTING_NOW_1HOUR 2
#define SETTING_NOW_10MIN 3
#define SETTING_NOW_1MIN  4

#define SETTING_NOW_DATE10 5
#define SETTING_NOW_DATE1 6
#define SETTING_NOW_MONTH 7
#define SETTING_NOW_YEAR10 8
#define SETTING_NOW_YEAR1 9

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

bool time_isLeapYear(byte year)
{
  uint fullYear = year + 2000;
  return ((fullYear & 3) == 0 && ((fullYear % 25) != 0 || (fullYear & 15) == 0));
}

byte time_dow(int y, byte m, byte d)
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

void dateDraw()
{
  byte x;
  byte w = 5;
  switch(setting.now)
  {
    case SETTING_NOW_DATE10:
    x = 28;
    break;
  case SETTING_NOW_DATE1:
    x = 35;
    break;
  case SETTING_NOW_MONTH:
    x = 49;
    w = 17;
    break;
  case SETTING_NOW_YEAR10:
    x = 91;
    break;
  case SETTING_NOW_YEAR1:
    x = 98;
    break;
  default:
    x = 0;
//    return DISPLAY_DONE;
  }
  
  display.fillRect(x, 16, w, w, WHITE);
//  draw_clearArea(x, 16, w);
  
  char buff[4];
  if(setting.now != SETTING_NOW_MONTH)
    sprintf_P(buff, PSTR("%hhu"), setting.val);
  else
    strcpy_P(buff, months[setting.val]);

  dateTimeMenu.drawString(buff, true, x, 16);

//draw_string(buff, true, x, 16);
  
//  return DISPLAY_DONE;
}

byte getMaxValForSetting()
{
  byte max;
  switch(setting.now)
  {
    case SETTING_NOW_10HOUR:
      max = 2;
      break;
    case SETTING_NOW_1HOUR:
      max = 9;
      break;
    case SETTING_NOW_10MIN:
      max = 5;
      break;
    case SETTING_NOW_1MIN:
      max = 9;
      break;
    case SETTING_NOW_DATE10:
      max = 3;
      break;
    case SETTING_NOW_DATE1:
      max = 9;
      break;
    case SETTING_NOW_MONTH:
      max = 11;
      break;
    case SETTING_NOW_YEAR10:
      max = 9;
      break;
    case SETTING_NOW_YEAR1:
      max = 9;
      break;
    default:
      max = 9;
      break;
  }
  return max;
}

void timeDataUp()
{
  setting.val++;
  if(setting.val > getMaxValForSetting())
    setting.val = 0;
}

void timeDataDown()
{
  setting.val--;
  byte max = getMaxValForSetting();
  if(setting.val > max)
    setting.val = max;
}

void selectDate()
{
#ifndef SLEEP_PROCESSOR
Serial.println("selectDate(): Enter");
#endif
  dateTimeMenu.setDownFunc(timeDataUp);
  dateTimeMenu.setUpFunc(timeDataDown);
  dateTimeMenu.setDrawFunc(dateDraw);

  switch(setting.now)
  {
    case SETTING_NOW_NONE:
      setting.now = SETTING_NOW_DATE10;
      setting.val = timeDataSet.Day / 10;
      break;
    case SETTING_NOW_DATE10:
      {
        byte mod = timeDataSet.Day % 10;
        timeDataSet.Day = (setting.val * 10) + mod;
        setting.now = SETTING_NOW_DATE1;
        setting.val = mod;
      }
      break;
    case SETTING_NOW_DATE1:
      timeDataSet.Day = ((timeDataSet.Day / 10) * 10) + setting.val;
      if(timeDataSet.Day < 1)
        timeDataSet.Day = 1;
      else if(timeDataSet.Day > 31)
        timeDataSet.Day = 31;
      setting.now = SETTING_NOW_MONTH;
      setting.val = timeDataSet.Month;
      break;
    case SETTING_NOW_MONTH:
    {
      timeDataSet.Month = setting.val;
      byte maxDays = 31;
      byte mnth = timeDataSet.Month;
      if(mnth == 3 || mnth == 5 || mnth == 8 || mnth == 10)
        maxDays = 30;
      else if(mnth == 1)
        maxDays = time_isLeapYear(timeDataSet.Year) ? 29 : 28;
      if(timeDataSet.Day > maxDays)
        timeDataSet.Day = maxDays;
      setting.now = SETTING_NOW_YEAR10;
      setting.val = timeDataSet.Year / 10;
    }
      break;
    case SETTING_NOW_YEAR10:
      {
        byte mod = timeDataSet.Year % 10;
        timeDataSet.Year = (setting.val * 10) + mod;
        setting.now = SETTING_NOW_YEAR1;
        setting.val = mod;
      }
      break;
    default:
      timeDataSet.Year = ((timeDataSet.Year / 10) * 10) + setting.val;
      timeDataSet.Day = time_dow(timeDataSet.Year + 2000, timeDataSet.Month + 1, timeDataSet.Day);
      setting.now = SETTING_NOW_NONE;

      dateTimeMenu.setDownFunc(dateTimeDownFunc);
      dateTimeMenu.setUpFunc(dateTimeUpFunc);
      dateTimeMenu.setDrawFunc(NULL);
      
      break;
  }
  
  showDateStr();
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

  strcpy_P(month, months[timeDataSet.Month]);
//  sprintf_P(buff, PSTR("%3s%02hhu %s 20%02hhu"), "", currTime.Day, month, currTime.Year);
  sprintf_P(buff, PSTR("%3s%02u %s %02u"), "", timeDataSet.Day, month, timeDataSet.Year);
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
  tmElements_t currTime;
  MyDS3232.read(currTime);

  // Create copy of current time & date
  memcpy(&timeDataSet, &currTime, sizeof(tmElements_t));

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


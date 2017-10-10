#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <TimeLib.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <DS3232RTC.h>    // http://github.com/JChristensen/DS3232RTC
#include <RTCx.h>         // https://github.com/stevemarple/RTCx

#include "icons.h"
#include "datetime.h"
#include "cour8pt7b.h"

extern Adafruit_SharpMem display;
extern WatchMenu *currentMenu;
extern DS3232RTC MyDS3232;
extern WatchMenu menu;

s_menuNowSetting setting;
WatchMenu dateTimeMenu(display);
tmElements_t timeDataSet = {0};

#define YPOS    64

//------------------------------------------------------------
// Method is called when the date/time menu option is selected.
// It creates a new String type menu (as opposed to Icon).
//------------------------------------------------------------
void timeFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("timeFunc(): Enter");
#endif

  tmElements_t currTime;
  MyDS3232.read(currTime);

  // Create copy of current time & date
  memcpy(&timeDataSet, &currTime, sizeof(tmElements_t));

#ifndef SLEEP_PROCESSOR
Serial.print("timeFunc(): timeDataSet.Year=");
Serial.println(timeDataSet.Year, DEC);
#endif

  
  dateTimeMenu.initMenu(1);  // Create a menu system with ? menu rows
  dateTimeMenu.setTextSize(1);
  dateTimeMenu.setFont(&cour8pt7b);
  dateTimeMenu.createMenu(MENU_MAIN_INDEX, 4, PSTR("<DATE/TIME>"), MENU_TYPE_STR, dateTimeDownFunc, dateTimeUpFunc);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, OPTION_SAVE_INDEX, PSTR("Save"), NULL, saveTimeFunc); // Position 3 
  dateTimeMenu.createOption(MENU_MAIN_INDEX, OPTION_EXIT_INDEX, PSTR("Exit"), NULL, back); // Position 4

  showDateStr();
  showTimeStr();

  // Default to date selected
  dateTimeMenu.selectedOption(MENU_MAIN_INDEX, OPTION_DATE_INDEX); // Set the default selection to the date
  
  // Point to date/time menu
  currentMenu = &dateTimeMenu;

  display.fillRect(0, 64, 128, 128, WHITE); // Clear display

#ifndef SLEEP_PROCESSOR
Serial.println("timeFunc(): Exit");
#endif
}

void back()
{
#ifndef SLEEP_PROCESSOR
Serial.println("back()");
#endif
  // Point to top level menu
  currentMenu = &menu;
}

//-------------------------------------------------------------- 
// Method draws the selection highlight when changing the date.
// The character highlight is reversed so it can be seen
//-------------------------------------------------------------- 
void dateDraw()
{
#ifndef SLEEP_PROCESSOR
//Serial.println("dateDraw(): Enter");
#endif
  int16_t invert_start = -1;
  int16_t invert_length = 0;

  switch(setting.now)
  {
    case SETTING_NOW_DAY10:
      invert_start = 1;
      invert_length = 1;
      timeDataSet.Day = (setting.val * 10) + (timeDataSet.Day % 10);
Serial.print("timeDataSet.Day=");
Serial.println(timeDataSet.Day);
#ifndef SLEEP_PROCESSOR
//Serial.print("dateDraw(): setting.val=");
//Serial.println(setting.val);
//Serial.print("dateDraw(): timeDataSet.Day=");
//Serial.println(timeDataSet.Day);
#endif
      break;
    case SETTING_NOW_DAY1:
      invert_start = 2;
      invert_length = 1;
      timeDataSet.Day = ((timeDataSet.Day / 10) * 10) + setting.val;
Serial.print("timeDataSet.Day=");
Serial.println(timeDataSet.Day);
      break;
    case SETTING_NOW_MONTH:
      invert_start = 4;
      invert_length = 3;
      timeDataSet.Month = setting.val;
      break;
    case SETTING_NOW_YEAR10:
      invert_start = 8;
      invert_length = 1;
      timeDataSet.Year = (setting.val * 10) + timeDataSet.Year % 10;
      break;
    case SETTING_NOW_YEAR1:
      invert_start = 9;
      invert_length = 1;
      timeDataSet.Year = ((timeDataSet.Year / 10) * 10) + setting.val;
      break;
    default:
      // Remove inversion
      invert_start = -1;
      invert_length = 0;
  }
  
  showDateStr(invert_start, invert_length);
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
    case SETTING_NOW_DAY10:
      max = 3;
      break;
    case SETTING_NOW_DAY1:
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

//------------------------------
// Move the menu up on key press
//------------------------------
void timeDataUp()
{
  setting.val++;
  if(setting.val > getMaxValForSetting())
    setting.val = 0;
}

//--------------------------------
// Move the menu down on key press
//--------------------------------
void timeDataDown()
{
  setting.val--;
  byte max = getMaxValForSetting();
  if(setting.val > max)
    setting.val = max;
}

//----------------------------------------------------
// Method is called when the Middle button (select) is
// pressed on the date menu.
//----------------------------------------------------
void selectDate()
{
#ifndef SLEEP_PROCESSOR
Serial.println("selectDate(): Enter");
#endif
  // Set the up and down buttons, and drawing routine to new functions
  dateTimeMenu.setDownFunc(timeDataUp);
  dateTimeMenu.setUpFunc(timeDataDown);
  dateTimeMenu.setDrawFunc(dateDraw);

  switch(setting.now)
  {
    case SETTING_NOW_NONE:
      setting.now = SETTING_NOW_DAY10;
      setting.val = timeDataSet.Day / 10;
      break;
    case SETTING_NOW_DAY10:
      {
        byte mod = timeDataSet.Day % 10;
        timeDataSet.Day = (setting.val * 10) + mod;
        setting.now = SETTING_NOW_DAY1;
        setting.val = mod;
      }
      break;
    case SETTING_NOW_DAY1:
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
        maxDays = LEAP_YEAR(timeDataSet.Year) ? 29 : 28;
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
      timeDataSet.Wday = time_dow(timeDataSet.Year + 2000, timeDataSet.Month + 1, timeDataSet.Day);
      setting.now = SETTING_NOW_NONE;

      // Go back to menu after finishing the editing of the date.
      // TODO - Find a nicer way to do this................
      dateTimeMenu.setDownFunc(dateTimeDownFunc);
      dateTimeMenu.setUpFunc(dateTimeUpFunc);
      dateTimeMenu.setDrawFunc(NULL);
      
      break;
  }

  // Display the new date
  showDateStr();
}

//----------------------------------------------------
// Method is called when the Middle button (select) is
// pressed on the time menu.
//----------------------------------------------------
void selectTime()
{
#ifndef SLEEP_PROCESSOR
Serial.println("selectTime(): Enter");
#endif
  // Set the up and down buttons, and drawing routine to new functions
  dateTimeMenu.setDownFunc(timeDataUp);
  dateTimeMenu.setUpFunc(timeDataDown);
  dateTimeMenu.setDrawFunc(timeDraw);

  switch(setting.now)
  {
    case SETTING_NOW_NONE:
      setting.now = SETTING_NOW_10HOUR;
      setting.val = timeDataSet.Hour / 10;
      break;
    case SETTING_NOW_10HOUR:
      {
        byte mod = timeDataSet.Hour % 10;
        timeDataSet.Hour = (setting.val * 10) + mod;
        setting.now = SETTING_NOW_1HOUR;
        setting.val = mod;
      }
      break;
    case SETTING_NOW_1HOUR:
      timeDataSet.Hour = ((timeDataSet.Hour / 10) * 10) + setting.val;
      if(timeDataSet.Hour > 23)
        timeDataSet.Hour = 23;
      setting.now = SETTING_NOW_10MIN;
      setting.val = timeDataSet.Minute / 10;
      break;
    case SETTING_NOW_10MIN:
      {
        byte mod = timeDataSet.Minute % 10;
        timeDataSet.Minute = (setting.val * 10) + mod;
        setting.now = SETTING_NOW_1MIN;
        setting.val = mod;
      }   
      break;
    default:
      timeDataSet.Minute = ((timeDataSet.Minute / 10) * 10) + setting.val;
      if(timeDataSet.Minute > 59)
        timeDataSet.Minute = 59;
      setting.now = SETTING_NOW_NONE;

      // Go back to menu after finishing the editing of the date.
      // TODO - Find a nicer way to do this................
      dateTimeMenu.setDownFunc(dateTimeDownFunc);
      dateTimeMenu.setUpFunc(dateTimeUpFunc);
      dateTimeMenu.setDrawFunc(NULL);
      break;
  }

  // Update the time display
  showTimeStr();
}

//-------------------------------------------------------------- 
// Method draws the selection highlight when changing the time.
// The character highlight is reversed so it can be seen
//-------------------------------------------------------------- 
void timeDraw()
{
  int16_t invert_start = -1;
  int16_t invert_length = 0;

  switch(setting.now)
  {
    case SETTING_NOW_10HOUR:
      invert_start = 1;
      invert_length = 1;
      timeDataSet.Hour = (setting.val * 10) + timeDataSet.Hour % 10;
      break;
    case SETTING_NOW_1HOUR:
      invert_start = 2;
      invert_length = 1;
      timeDataSet.Hour = ((timeDataSet.Hour / 10) * 10) + setting.val;
      break;
    case SETTING_NOW_10MIN:
      invert_start = 4;
      invert_length = 1;
      timeDataSet.Minute = (setting.val * 10) + timeDataSet.Minute % 10;
      break;
    case SETTING_NOW_1MIN:
      invert_start = 5;
      invert_length = 1;
      timeDataSet.Minute = ((timeDataSet.Minute / 10) * 10) + setting.val;
      break;
  }

  showTimeStr(invert_start, invert_length);
}

//--------------------------------------------------------------
// Method creates the date string to me used for the menu string
//--------------------------------------------------------------
void makeDateStr(char* buff)
{
  char month[4] = {0};
  strcpy_P(month, months[timeDataSet.Month]);
  sprintf_P(buff, PSTR("%1s%02u %s %02u"), "", timeDataSet.Day, month, timeDataSet.Year);
}

void showDateStr()
{
  showDateStr(-1, 0); // No invert
}

//--------------------------------------------------------------
// Method creates the date menu option using the date passed in.
//--------------------------------------------------------------
void showDateStr(int16_t invert_start, int16_t invert_length)
{
  char buff[21];
  makeDateStr(buff);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, OPTION_DATE_INDEX, invert_start, invert_length, buff, NULL, selectDate); // Position 1
}

//--------------------------------------------------------------
// Method creates the time string to me used for the menu string
//--------------------------------------------------------------
void makeTimeStr(char* buff)
{
  sprintf_P(buff, PSTR("%1s%02u:%02u"), "", timeDataSet.Hour, timeDataSet.Minute);
}

void showTimeStr()
{
  showTimeStr(-1, 0);  
}

//--------------------------------------------------------------
// Method creates the time menu option using the date passed in.
//--------------------------------------------------------------
void showTimeStr(int16_t invert_start, int16_t invert_length)
{
  char buff[12];
  makeTimeStr(buff);
  dateTimeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_INDEX, invert_start, invert_length, buff, NULL, selectTime); // Position 2
}

//----------------------------------------
// Method handles down button pressed when 
// editing the date and time strings
//----------------------------------------
void dateTimeDownFunc()
{
  dateTimeMenu.upOption();
}

//----------------------------------------
// Method handles up button pressed when 
// editing the date and time strings
//----------------------------------------
void dateTimeUpFunc()
{
  dateTimeMenu.downOption();
}

//----------------------------------------------------------------
// Method to save the time when the Save menu option is selected.
// Changes the menu option to "Saved".
//----------------------------------------------------------------
void saveTimeFunc()
{
  MyDS3232.write(timeDataSet);

  // Change the option text to Saved
  dateTimeMenu.createOption(MENU_MAIN_INDEX, OPTION_SAVE_INDEX, PSTR("Saved"), NULL, saveTimeFunc); // Position 3 
}



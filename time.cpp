#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <TimeLib.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <DS3232RTC.h>    // http://github.com/JChristensen/DS3232RTC
#include <RTCx.h>         // https://github.com/stevemarple/RTCx

#include "defs.h"
#include "datetime.h"
#include "cour8pt7b.h"

extern Adafruit_SharpMem display;
extern WatchMenu *currentMenu;
extern DS3232RTC MyDS3232;
extern WatchMenu menu;
extern bool invert;

extern s_menuNowSetting setting;
WatchMenu timeMenu(display);
tmElements_t timeDataSet = {0};
eHR1224 hr1224;
eAMPM amPm;

//------------------------------------------------------------
// Method is called when the date/time menu option is selected.
// It creates a new String type menu (as opposed to Icon).
//------------------------------------------------------------
void timeFunc()
{
  tmElements_t currTime;
  MyDS3232.read(currTime);

  // Create copy of current time & date
  memcpy(&timeDataSet, &currTime, sizeof(tmElements_t));
  hr1224 = (MyDS3232.readRTC(RTC_HOURS) & _BV(HR1224)) ? HR12 : HR24; // Hr
  amPm = (MyDS3232.readRTC(RTC_HOURS) & _BV(AMPM)) ? HRPM : HRAM; // Morning/Afternoon

  timeMenu.initMenu(1);  // Create a menu system with ? menu rows
  timeMenu.setTextSize(1);
  timeMenu.setFont(&cour8pt7b);
  timeMenu.createMenu(MENU_MAIN_INDEX, 4, PSTR("<DATE/TIME>"), MENU_TYPE_STR, timeDownFunc, timeUpFunc);
  timeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_SAVE_INDEX, PSTR("Save"), NULL, saveTimeFunc);
  timeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_EXIT_INDEX, PSTR("Exit"), NULL, timeBack);
  timeMenu.invertDisplay(invert);

  showTimeStr();
  show1224HrStr();

  // Default to date selected
  timeMenu.selectedOption(MENU_MAIN_INDEX, OPTION_TIME_TIME_INDEX); // Set the default selection to the date
  
  // Point to date/time menu
  currentMenu = &timeMenu;

  display.fillRect(0, 64, 128, 128, invert ? BLACK : WHITE); // Clear display
}

void timeBack()
{
  // Point to top level menu
  currentMenu = &menu;
}

byte getMaxValForTimeSetting()
{
  byte max;
  switch(setting.now)
  {
    case SETTING_NOW_10HOUR:
      max = (hr1224 ==  HR12) ? 1 : 2;
      break;
    case SETTING_NOW_1HOUR:
      max = (hr1224 ==  HR12) ? 2 : 9;
      break;
    case SETTING_NOW_10MIN:
      max = 5;
      break;
    case SETTING_NOW_1MIN:
      max = 9;
      break;
    case SETTING_NOW_12HR:
    case SETTING_NOW_24HR:
      max = 1;
    case SETTING_NOW_AMHR:
    case SETTING_NOW_PMHR:
      max = 1;
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
  if(setting.val > getMaxValForTimeSetting())
    setting.val = 0;
}

//--------------------------------
// Move the menu down on key press
//--------------------------------
void timeDataDown()
{
  setting.val--;
  byte max = getMaxValForTimeSetting();
  if(setting.val > max)
    setting.val = max;
}

void select1224hr()
{
  // Set the up and down buttons, and drawing routine to new functions
  timeMenu.setDownFunc(timeDataUp);
  timeMenu.setUpFunc(timeDataDown);
  timeMenu.setDrawFunc(hr1224Draw);

  switch(setting.now)
  {
    case SETTING_NOW_NONE:
    {
      setting.val = hr1224;
      setting.now = SETTING_NOW_24HR;
      break;
    }
    default:
      hr1224 = (eHR1224)setting.val;
      setting.now = SETTING_NOW_NONE;

      // Go back to menu after finishing the editing of the date.
      // TODO - Find a nicer way to do this................
      timeMenu.setDownFunc(timeDownFunc);
      timeMenu.setUpFunc(timeUpFunc);
      timeMenu.setDrawFunc(NULL);
      break;
  }

  // Update the time mode
  show1224HrStr();
}

void hr1224Draw()
{
  hr1224 = (eHR1224)setting.val;
  
  show1224HrStr(1, 2);
}

//----------------------------------------------------
// Method is called when the Middle button (select) is
// pressed on the time menu.
//----------------------------------------------------
void selectTime()
{
  // Set the up and down buttons, and drawing routine to new functions
  timeMenu.setDownFunc(timeDataUp);
  timeMenu.setUpFunc(timeDataDown);
  timeMenu.setDrawFunc(timeDraw);

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
    case SETTING_NOW_1MIN:
      {
        timeDataSet.Minute = ((timeDataSet.Minute / 10) * 10) + setting.val;
        if(timeDataSet.Minute > 59)
        {
          timeDataSet.Minute = 59;
        }

        // If 12 hr clock then move on to AM/PM selection else end selection.
        if (hr1224 == HR12)
        {
          setting.now = SETTING_NOW_AMHR;
          setting.val = amPm;
        }
        else
        {
          setting.now = SETTING_NOW_NONE;
          // Go back to menu after finishing the editing of the date.
          // TODO - Find a nicer way to do this................
          timeMenu.setDownFunc(timeDownFunc);
          timeMenu.setUpFunc(timeUpFunc);
          timeMenu.setDrawFunc(NULL);
        }
      }   
      break;
    default:
      if (hr1224 == HR12)
      {
        amPm = (eAMPM)setting.val;
      }
      setting.now = SETTING_NOW_NONE;

      // Go back to menu after finishing the editing of the date.
      // TODO - Find a nicer way to do this................
      timeMenu.setDownFunc(timeDownFunc);
      timeMenu.setUpFunc(timeUpFunc);
      timeMenu.setDrawFunc(NULL);
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
    case SETTING_NOW_AMHR:
      invert_start = 7;
      invert_length = 2;
      amPm = (eAMPM)setting.val;
      break;
  }

  showTimeStr(invert_start, invert_length);
}

//--------------------------------------------------------------
// Method creates the time string to me used for the menu string
//--------------------------------------------------------------
void makeTimeStr(char* buff)
{
  switch(hr1224)
  {
    case HR12:
      sprintf_P(buff, PSTR("%1s%02u:%02u %2s"), "", timeDataSet.Hour, timeDataSet.Minute, (amPm == HRAM) ? "AM" : "PM");
    break;
    case HR24:
      sprintf_P(buff, PSTR("%1s%02u:%02u %2s"), "", timeDataSet.Hour, timeDataSet.Minute, "");
      break;
  }
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
  timeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_TIME_INDEX, invert_start, invert_length, buff, NULL, selectTime);
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void show1224HrStr()
{
  show1224HrStr(-1, 0);  
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void show1224HrStr(int16_t invert_start, int16_t invert_length)
{
  char buff[7] = {0};
  switch(hr1224)
  {
    case HR12:
      strcpy_P(buff, PSTR(" 12 hr"));
    break;
    case HR24:
      strcpy_P(buff, PSTR(" 24 hr"));
      break;
  }
  timeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_12HR_INDEX, invert_start, invert_length, buff, NULL, select1224hr);

  // Redraw the time string also, as we may have changed the 12/24 hr option.
  showTimeStr();
}

//----------------------------------------
// Method handles down button pressed when 
// editing the date and time strings
//----------------------------------------
void timeDownFunc()
{
  timeMenu.upOption();
}

//----------------------------------------
// Method handles up button pressed when 
// editing the date and time strings
//----------------------------------------
void timeUpFunc()
{
  timeMenu.downOption();
}

//----------------------------------------------------------------
// Method to save the time when the Save menu option is selected.
// Changes the menu option to "Saved".
//----------------------------------------------------------------
void saveTimeFunc()
{
  // Write the time.
  MyDS3232.write(timeDataSet);
  // Set the 12/24 hr option.  This is bit 6 of the Hr (0x02), 0=24hr, 1=12hr.
  byte hrRead = MyDS3232.readRTC(RTC_HOURS); // Hr

  // Set 12 or 24 hr
  switch(hr1224)
  {
    case HR12:
      hrRead |= _BV(HR1224); // Set bit 6
      switch(amPm)
      {
        case HRPM:
          hrRead |= _BV(AMPM); // Set bit 5
        break;
        case HRAM:
          hrRead &= ~_BV(AMPM); // Clear bit 5
        break;
      }
    break;
    case HR24:
      hrRead &= ~_BV(HR1224); // Clear bit 6
    break;
  }

  MyDS3232.writeRTC(RTC_HOURS, hrRead); // Set hrs with AM/PM/24Hr/12Hr

  // Change the option text to Saved
  timeMenu.createOption(MENU_MAIN_INDEX, OPTION_TIME_SAVE_INDEX, PSTR("Saved"), NULL, saveTimeFunc); // Position 3 
}



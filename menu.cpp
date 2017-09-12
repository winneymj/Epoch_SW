#include <stdint.h>
#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif
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

#define INACTIVITY 30000

// Font data for Arial 48pt

extern const uint8_t arialNarrow_48ptBitmaps[];
extern const FONT_CHAR_INFO arialNarrow_48ptDescriptors[];
extern const uint8_t calibri_48ptBitmaps_colon[];
extern const FONT_CHAR_INFO calibri_48ptDescriptors_colon[];
extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;
extern const GFXfont courier_10x15FontInfo;
extern volatile boolean rtcRead;
extern WatchMenu *currentMenu;
extern volatile uint8_t pinValM;
extern volatile uint8_t pinValD;
extern volatile uint8_t pinValU;
extern pFunc drawFunc;
extern void displayTime();

// Forward Declarations
void timeFunc();
void exitMenu();
void menuUpFunc();
void menuDownFunc();

// Locals
WatchMenu menu(display);
bool menuExit = false;

void initializeMenu()
{
#define NUM_MENUS           3
#define MENU_MAIN_INDEX     0
#define MENU_DATE_TIME_INDEX     1

  menu.setTextSize(1);
  menu.setFont(&courier_10x15FontInfo);
  
  menu.initMenu(1);  // Create a menu system with ? menu rows
  
  menu.createMenu(MENU_MAIN_INDEX, 2, PSTR("<MAIN MENU>"), MENU_TYPE_ICON, menuDownFunc, menuUpFunc); // 3 options
  menu.createOption(MENU_MAIN_INDEX, 0, PSTR("Date & Time"), menu_clockBitmaps, timeFunc);
  menu.createOption(MENU_MAIN_INDEX, 1, PSTR("Exit"), menu_exitBitmaps, exitMenu);
}

void displayMenu()
{
  // get the current time in millis
  long pressStart = millis();
    
  while(!menuExit)
  {
    delay(10);
    rtcRead = !rtcRead;

    display.fillRect(0, 64, 128, 128, WHITE);
    bool animating = currentMenu->updateMenu();
    display.refresh();

    while (animating)
    {
//        display.clearDisplayBuffer();
      display.fillRect(0, 64, 128, 128, WHITE);
      animating = currentMenu->updateMenu();
      display.refresh();
      delay(20);
    }
//#ifndef SLEEP_PROCESSOR
//  Serial.println("looping");
//#endif
 
    if (pinValM)
    {
      pinValM = false;
      pressStart = millis();    // Reset the idle as we had a keypress
      currentMenu->selectOption(); 
    }
    if (pinValD)
    {
      pinValD = false;
      pressStart = millis();    // Reset the idle as we had a keypress
      currentMenu->menuDown();
    }
      
    if (pinValU)
    {
      pinValU = false;
      pressStart = millis();  // Reset the idle as we had a keypress
      currentMenu->menuUp();
    }

    // See if inactive and get out.
    long inactiveTimer = millis() - pressStart;
    if (inactiveTimer > INACTIVITY)
    {
      exitMenu();
    }
  }// while

  // Exiting the menu so reset back to default.
  menu.resetMenu();
  menuExit = false;
}

void exitMenu()
{
#ifndef SLEEP_PROCESSOR
Serial.println("exitMenu(): Enter");
#endif
  // Clear down bottom of the screen
  display.fillRect(0, 64, 128, 128, WHITE);
//  display.refresh();

  // Exited the menu so go back to drawing the time etc.
  drawFunc = displayTime;

  // Set flag to make sure we exit the while loop.
  menuExit = true;
}

void menuDownFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuDownFunc(): Enter");
#endif
  menu.downOption();
}

void menuUpFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuUpFunc(): Enter");
#endif
  menu.upOption();
}



#include <stdint.h>
#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>

#include "defs.h"
#include "icons.h"
#include "menu.h"
#include "cour6pt7b.h"

// Externals
extern long keyPressTimeStamp;

// Locals
WatchMenu menu(display);
bool menuExit = false;

void initializeMenu()
{
  menu.initMenu(1);  // Create a menu system with ? menu rows
  menu.setTextSize(1);
  menu.setFont(&cour6pt7b);

  // Top level menu
  menu.createMenu(MENU_MAIN_INDEX, 3, PSTR("<MAIN MENU>"), MENU_TYPE_ICON, menuDownFunc, menuUpFunc);
  menu.createOption(MENU_MAIN_INDEX, OPT_DATE_TIME_INDEX, PSTR("Date & Time"), menu_clockBitmaps, timeFunc);
  menu.createOption(MENU_MAIN_INDEX, OPT_SETTINGS_INDEX, PSTR("Settings"), menu_settingsBitmaps, (uint8_t)MENU_SETTINGS_INDEX);
  menu.createOption(MENU_MAIN_INDEX, OPT_EXIT_INDEX, PSTR("Exit"), menu_exitBitmaps, exitMenu);

  // Create sub menu for settings
  menu.createMenu(MENU_SETTINGS_INDEX, 2, PSTR("<SETTINGS>"), MENU_TYPE_ICON, menuDownFunc, menuUpFunc);
  menu.createOption(MENU_SETTINGS_INDEX, OPT_INVERT_INDEX, PSTR("Invert"), menu_invertBitmaps, timeFunc);
  menu.createOption(MENU_SETTINGS_INDEX, OPT_SETTINGS_EXIT_INDEX, PSTR("Exit"), menu_exitBitmaps, (uint8_t)MENU_MAIN_INDEX);
}

//----------------------------------------------------------------
// Method display the main menu and enters a loop checking for key
// presses and passing them onto the menu display code.
// If no keys are pressed for the ACTIVITY_TIMEOUT then the loop
// exits.
//----------------------------------------------------------------
void displayMenu()
{
  // get the current time in millis
  long pressStart = millis();
    
  while(!menuExit)
  {
    delay(10);
    rtcRead = !rtcRead;

    // Clear bottom of screen
    display.fillRect(0, 64, 128, 128, WHITE);
    bool animating = currentMenu->updateMenu();
    display.refresh();

    while (animating)
    {
      // Clear bottom of screen
      display.fillRect(0, 64, 128, 128, WHITE);
      animating = currentMenu->updateMenu();
      display.refresh();
      delay(20);
    }
 
    if (pinValM)
    {
      int8_t buttonState = digitalRead(MBUT);
      // Button still pressed.
      if (buttonState)
      {
        pinValM = false;
        pressStart = millis();    // Reset the idle as we had a keypress
        currentMenu->selectOption(); 
      }
    }

    if (pinValD)
    {
      int8_t buttonState = digitalRead(DBUT);
      // Button still pressed.
      if (buttonState)
      {
        pinValD = false;
        pressStart = millis();    // Reset the idle as we had a keypress
        currentMenu->menuDown();
      }
    }
      
    if (pinValU)
    {
      int8_t buttonState = digitalRead(UBUT);
      // Button still pressed.
      if (buttonState)
      {
        pinValU = false;
        pressStart = millis();  // Reset the idle as we had a keypress
        currentMenu->menuUp();
      }
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
//Serial.println("exitMenu(): Enter");
#endif
  // Clear down bottom of the screen
  display.fillRect(0, 64, 128, 128, WHITE);

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



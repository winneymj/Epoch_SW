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

// Font data for Arial 48pt

extern const GFXfont arialNarrow_48ptFontInfo;
extern const GFXfont arialNarrow_48ptFontInfo_colon;
extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;



void displayTime(tmElements_t currTime)
{
//  // Clear the display buffer before writing to the display.
//  // Don't need to clear the display as the refresh will
//  // write it all.
//  display.clearDisplayBuffer();

  display.setTextSize(1);
  display.setFont(&arialNarrow_48ptFontInfo);
  display.setTextColor(BLACK, WHITE);

  
  char timeBuff[3] = {0};
  sprintf_P(timeBuff, PSTR("%02u"), currTime.Hour);

  int xpos = 4;
  display.setCursor(xpos, 10);
  display.print(timeBuff);
  display.setFont(&arialNarrow_48ptFontInfo_colon);
  display.print(':');
  display.setFont(&arialNarrow_48ptFontInfo);
  sprintf_P(timeBuff, PSTR("%02u"), currTime.Second);
  display.print(timeBuff);

  // Display the time.  Writes the entire buffer to the display
//  display.refresh();
}

void displayTime()
{
    // Get the time from the RTC
    tmElements_t currTime;
    MyDS3232.read(currTime);

    displayTime(currTime);
}


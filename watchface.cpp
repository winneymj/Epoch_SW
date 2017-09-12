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

extern const uint8_t arialNarrow_48ptBitmaps[];
extern const FONT_CHAR_INFO arialNarrow_48ptDescriptors[];
extern const uint8_t calibri_48ptBitmaps_colon[];
extern const FONT_CHAR_INFO calibri_48ptDescriptors_colon[];
extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;



int displayChar(uint8_t x, uint8_t y, uint8_t c)
{
  FONT_CHAR_INFO fDetails = arialNarrow_48ptDescriptors[c];

  const byte* bitmap = &arialNarrow_48ptBitmaps[fDetails.offset];
  display.drawBitmap(x, y, bitmap, fDetails.w, fDetails.h, BLACK);
  return fDetails.w + 2;
}
int displayColon(uint8_t x, uint8_t y)
{
  FONT_CHAR_INFO fDetails = calibri_48ptDescriptors_colon[0];

  const byte* bitmap = &calibri_48ptBitmaps_colon[fDetails.offset];
  display.drawBitmap(x, y, bitmap, fDetails.w, fDetails.h, BLACK);
  return fDetails.w + 2;
}

void displayTime(tmElements_t currTime)
{
  // Clear the display buffer before writing to the display.
  // Don't need to clear the display as the refresh will
  // write it all.
  display.clearDisplayBuffer();

  int xpos = 4;
  xpos += displayChar(xpos, 10, currTime.Hour / 10);
  xpos += displayChar(xpos, 10, currTime.Hour % 10);
  xpos += displayColon(xpos, 20);
//  xpos += displayChar(xpos, 10, currTime.Minute / 10);
//  xpos += displayChar(xpos, 10, currTime.Minute % 10);
  xpos += displayChar(xpos, 10, currTime.Second / 10);
  xpos += displayChar(xpos, 10, currTime.Second % 10);

  // Display the time.  Writes the entire buffer to the display
  display.refresh();
}

void displayTime()
{
    // Get the time from the RTC
    tmElements_t currTime;
    MyDS3232.read(currTime);

    displayTime(currTime);
}


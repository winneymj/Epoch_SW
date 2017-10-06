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

#include "arialn30pt7b.h"
#include "courbd6pt7b.h"

const char months[12][10] PROGMEM = {
  "Jan",
  "Feb",
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


extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;
extern void printCenterString(char *str);

void displayLongDate(tmElements_t currTime)
{
  display.setTextSize(1);
  display.setFont(&courbd6pt7b);
  display.setTextColor(BLACK, WHITE);

  char timeBuff[32] = {0};
  sprintf_P(timeBuff, PSTR("%s %u, %u"), months[currTime.Month], currTime.Day, currTime.Year + 2000);

  display.setCursor(64, 60);
  printCenterString(timeBuff);
}

void displayTime(tmElements_t currTime)
{
  display.setTextSize(1);
  display.setFont(&arialn30pt7b);
  display.setTextColor(BLACK, WHITE);
  
  char timeBuff[6] = {0};
  sprintf_P(timeBuff, PSTR("%02u:%02u"), currTime.Hour, currTime.Second);

  display.setCursor(4, 48);
  display.print(timeBuff);
}

void displayTime()
{
    // Get the time from the RTC
    tmElements_t currTime;
    MyDS3232.read(currTime);

    displayTime(currTime);
    displayLongDate(currTime);
}


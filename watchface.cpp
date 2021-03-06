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

#include "defs.h"
#include "arialn26pt7b.h"
#include "courbd6pt7b.h"

extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;
extern void printCenterString(char *str);
extern bool invert;
extern eTempConversion tempType = centigrade;

void displayLongDate(tmElements_t currTime)
{
  display.setTextSize(1);
  display.setFont(&courbd6pt7b);
  display.setTextColor(invert ? WHITE: BLACK, invert ? BLACK : WHITE);

  char timeBuff[32] = {0};
  sprintf_P(timeBuff, PSTR("%s %u, %u"), months[currTime.Month], currTime.Day, currTime.Year + 2000);

  display.setCursor(64, 60);
  printCenterString(timeBuff);
}

void displayTime(tmElements_t currTime)
{
  display.setTextSize(1);
  display.setFont(&arialn26pt7b);
  display.setTextColor(invert ? WHITE: BLACK, invert ? BLACK : WHITE);
  
  char timeBuff[6] = {0};
#ifdef EVERY_SECOND
  sprintf_P(timeBuff, PSTR("%02u:%02u"), currTime.Hour, currTime.Second);
#endif
#ifdef EVERY_MINUTE
  sprintf_P(timeBuff, PSTR("%02u:%02u"), currTime.Hour, currTime.Minute);
#endif

  display.setCursor(10, 49);
  display.print(timeBuff);
}

void displayTemp(float temp)
{
  display.setTextSize(1);
  display.setFont(&courbd6pt7b);
  display.setTextColor(invert ? WHITE: BLACK, invert ? BLACK : WHITE);

  display.setCursor(75, 8);
  char tempBuff[8] = {0};
  sprintf_P(tempBuff, PSTR("%d.%02d"), (int)temp, (int)(temp * 100.0) % 100);
  display.print(tempBuff);

  display.setFont(&cour6pt8bDegree);
  display.print((char)0xB0);

  display.setFont(&courbd6pt7b);
  display.print((tempType == fahrenheit) ? 'F' : 'C');
}

float CtoF(float temp)
{
  return (temp * 1.8) + 32;
}

void displayTime()
{
  // Get the time from the RTC
  tmElements_t currTime;
  MyDS3232.read(currTime);

  int initTemp = MyDS3232.temperature();
  float temp = initTemp / 4.0;

  // Clear down entire screen
  display.fillRect(0, 0, display.width(), display.height() / 2, invert ? BLACK : WHITE);

  displayTime(currTime);
  displayLongDate(currTime);
  displayTemp((tempType == fahrenheit) ? CtoF(temp) : temp);
}


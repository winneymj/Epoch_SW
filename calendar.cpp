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
#include <DS3232RTC.h>    // http://github.com/JChristensen/DS3232RTC

#include "calendar.h"
#include "datetime.h"
#include "cour6pt7b.h"
#include "courbd6pt7b.h"

extern Adafruit_SharpMem display;
extern DS3232RTC MyDS3232;

#define CAL_XPOS          6
#define CAL_YPOS          64
#define CAL_WIDTH         126
#define CAL_HEIGHT        64
#define CAL_CELL_WIDTH    16
#define CAL_CELL_HEIGHT   12
#define CAL_ROWS          5
#define CAL_COLUMNS       7
#define TEXT_OFFSET_X     3  
#define TEXT_OFFSET_Y     1  

const char dayOfWeek[7][2] PROGMEM = {
  "M",
  "T",
  "W",
  "T",
  "F",
  "S",
  "S"
};

const uint8_t dayInMonth[12] PROGMEM = {
  31, //Jan
  29, //Feb
  31, //Mar
  30, //Apr
  31, //May
  30, //June
  31, //July
  31, //Aug
  30, //Sept
  31, //Oct
  30, //Nov
  31, //Dec
};

void printCenterString(char *str)
{
//  Serial.print("printCenterString:'");
//  Serial.print(str);
//  Serial.println("'");
  int16_t tempX;
  int16_t tempY;
  uint16_t w;
  uint16_t h;
  // Get the string width
  display.getTextBounds(str, 0, 0, &tempX, &tempY, &w, &h);

//  Serial.print("w:");
//  Serial.println(w);
//  Serial.print("CursorX:");
//  Serial.println(display.getCursorX());

  int poX = display.getCursorX() - w / 2;
//  Serial.print("poX:");
//  Serial.println(poX);
  int poY = display.getCursorY();
  display.setCursor(poX, poY);
  display.print(str);
}

void displayCalendarGrid()
{
  // Rows
  for(int loop = 0; loop < CAL_ROWS + 1; loop++)
  {
    display.writeLine(CAL_XPOS, CAL_YPOS + (CAL_CELL_HEIGHT * loop), CAL_XPOS + (CAL_CELL_WIDTH * CAL_COLUMNS), CAL_YPOS + (CAL_CELL_HEIGHT * loop), BLACK);
  }
  
  // Columns
  for(int loop = 0; loop < CAL_COLUMNS + 1; loop++)
  {
    display.writeLine(CAL_XPOS + (CAL_CELL_WIDTH * loop), CAL_YPOS, CAL_XPOS + (CAL_CELL_WIDTH * loop), CAL_YPOS + (CAL_CELL_HEIGHT * CAL_ROWS) , BLACK);
  }
}

void displayDOW()
{
  display.setTextSize(1);
//  display.setFont(NULL);  // Default 5x7 font.
  display.setFont(&courbd6pt7b);
  display.setTextColor(BLACK, WHITE);

  for(int loop = 0; loop < CAL_COLUMNS; loop++)
  {
    uint8_t cellCenter = (CAL_XPOS + 1) + ((CAL_CELL_WIDTH + 1 )/ 2.0) + (CAL_CELL_WIDTH * loop);
    display.setCursor(cellCenter, CAL_YPOS + CAL_CELL_HEIGHT - 2);
    printCenterString((char *)dayOfWeek[loop]);
//    display.print(dayOfWeek[loop]);
  }
}

uint8_t daysMonth(tmElements_t currTime, uint8_t offset) // -1 previous month, 0 = current month
{
    // Goes back into previous month
    int8_t newMonth = currTime.Month + offset;
    
    int8_t prevMonth = newMonth < 0 ? 12 : newMonth > 12 ? 0 : newMonth;
    return dayInMonth[prevMonth];
}

uint8_t getCalendarStartDate()
{
  // Get the time from the RTC
  tmElements_t currTime; // TODO...make this global?
  MyDS3232.read(currTime);
  // Monday is 0
  uint8_t dow = time_dow(currTime.Year + 2000, currTime.Month + 1, currTime.Day);
  uint8_t dom = currTime.Day;
  // Calculate date on previous Monday, ie 0 (zero)
  int8_t lastMonDom = dom - dow; 
  uint8_t daysLastMonth = 0;
  
//  Serial.print("lastMonDom:");
//  Serial.println(lastMonDom);
  if (lastMonDom <= 0)
  {
    daysLastMonth = daysMonth(currTime, -1);
//    Serial.print("daysLastMonth:");
//    Serial.println(daysLastMonth);
  }

  if (daysLastMonth > 0)
  {
    lastMonDom = daysLastMonth + lastMonDom;
  }
//  Serial.print("dow:");
//  Serial.println(dow);
//  Serial.print("dom:");
//  Serial.println(dom);
//  Serial.print("lastMonDom:");
//  Serial.println(lastMonDom);
//  Serial.print("Month:");
//  Serial.println(currTime.Month);

  return lastMonDom;
}

void displayDates(tmElements_t currTime)
{
  display.setTextSize(1);
//  display.setFont(NULL);  // Default 5x7 font.
  display.setFont(&cour6pt7b);
  display.setTextColor(BLACK, WHITE);

  // Get the date to start printing in the top left of calendar, Last Monday.
  uint8_t startDate = getCalendarStartDate();

//  Serial.print("startDate:");
//  Serial.println(startDate);

  uint8_t col_index = 0;
  uint8_t daysForMonth = 0;
  uint8_t dom = currTime.Day;
    Serial.print("dom:");
    Serial.println(dom);
  // If dom is < 7 then possible to go back into previous month
  if (dom < 7)
  {
    daysForMonth = daysMonth(currTime, -1); // Previous month
  }
  else
  {
    daysForMonth = daysMonth(currTime, 0); // Current month
  }
  
  for(int row = 1; row < 5; row++)
  {
    for(int column = 1; column < 8; column++)
    {
      uint8_t cellCenter = CAL_XPOS + ((CAL_CELL_WIDTH + 1 )/ 2.0) + (CAL_CELL_WIDTH * (column - 1));
  //  Serial.print("cellCenter:");
  //  Serial.println(cellCenter);
      uint8_t xpos = cellCenter - 1;
      uint8_t ypos = CAL_YPOS + TEXT_OFFSET_Y + (CAL_CELL_HEIGHT * (row + 1)) - 3;
      display.setCursor(xpos, ypos);
      char weekStr[3] = {0};
      sprintf_P(weekStr, PSTR("%u"), startDate);

      // Invert
      if (startDate == dom)
      {
        display.setTextColor(WHITE, BLACK);
      }
      
      printCenterString(weekStr);

      // Invert back
      if (startDate == dom)
      {
        display.setTextColor(BLACK, WHITE);
      }
  
      startDate++;
      // Check if greater then end of month date and set to 1
      if (startDate > daysForMonth)
      {
        startDate = 1;
      }
    }
  }
}

void displayCalendar()
{
  // Get the time from the RTC
  tmElements_t currTime; // TODO...make this global?
  MyDS3232.read(currTime);
  
  displayDOW();
  displayDates(currTime);
  displayCalendarGrid();
}



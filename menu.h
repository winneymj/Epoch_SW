#ifndef _MENU_H
#define _MENU_H

#include <stdint.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define NUM_MENUS             3
#define MENU_MAIN_INDEX       0
#define MENU_DATE_TIME_INDEX  1

#define INACTIVITY 30000

extern Adafruit_SharpMem display;
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




#endif

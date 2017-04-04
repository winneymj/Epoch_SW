
#ifndef _ICONS_H
#define _ICONS_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #define WIRE_WRITE Wire.write
#else
 #include "WProgram.h"
  #define WIRE_WRITE Wire.send
#endif

#define NUM_MENUS           3
#define MENU_MAIN_INDEX     0
#define MENU_SUB_INDEX      1
#define MENU_SUB_SUB_INDEX  2
#define MENU_CHANNELS_INDEX 3


extern const uint8_t menu_stationBitmaps[];
//extern const uint8_t menu_alarmBitmaps[];
////extern const uint8_t menu_gamesBitmaps[];
//extern const uint8_t menu_wirelessBitmaps[];
//extern const uint8_t menu_exitBitmaps[];
//extern const uint8_t menu_speedBitmaps[];
//
//
//extern void setChannelsFunc();
//extern void setWifiFunc();
//extern void setDisplaySpeedFunc();
//
//extern void backtoSchedule();
//extern void alarmFunc();
//extern void initializeMenu();
//extern void drawMenu();
//extern void setDrawFunc(pFunc func);
//extern void buttons_update();
//extern void processButtons();
//extern void handleDefaultSelectOption();
//extern void setDefaultOptions();
//extern void setupButtons();
//extern void decideSelectOption(uint8_t button);
//extern void setMenuOptions();
//extern void runDrawFunc();
//static void displayUpOption();
//static void displayDownOption();
//static void displaySelectOption();
//extern void backToMenu();
//extern void drawSchedule();
//
//
//extern s_btn_ptr button_funcs;
//extern pFunc draw_func;
//
//// Define GPIO pins for the buttons
//#define PIN_UP        4
//#define PIN_SELECT    5
//#define PIN_DOWN      12
//
//#define BTN_UP_PRESSED      (digitalRead(PIN_UP) == 0)
//#define BTN_SELECT_PRESSED  (digitalRead(PIN_SELECT) == 0)
//#define BTN_DOWN_PRESSED    (digitalRead(PIN_DOWN) == 0)
//
//#define BTN_DEBOUNCE_TIME  10
//#define BTN_COUNT 3
//
//#define BTN_UP      0
//#define BTN_SELECT  1
//#define BTN_DOWN    2
//
//

#endif


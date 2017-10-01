
#ifndef _ICONS_H
#define _ICONS_H

#include <stdint.h>
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


extern const  uint8_t menu_clockBitmaps[];
extern const uint8_t menu_exitBitmaps[];

#endif


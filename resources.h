
#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <stdint.h>
#if ARDUINO >= 100
 #include "Arduino.h"
 #define WIRE_WRITE Wire.write
#else
 #include "WProgram.h"
  #define WIRE_WRITE Wire.send
#endif

struct FONT_CHAR_INFO
{
  uint8_t w;
  uint8_t h;
  uint16_t offset;

};

#endif


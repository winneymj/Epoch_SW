#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <Wire.h>
#include <RTCx.h>
#include <Button.h> // https://github.com/JChristensen/Button

#include "icons.h"
#include "resources.h"

#define SCK 19
#define MOSI 18
#define SS 23
#define EXTMODE 28
#define LED 6

#define MBUT 4
#define UBUT 14
#define DBUT 22
Button buttonMid(MBUT, true, true, 20);
Button buttonUp(UBUT, true, true, 20);
Button buttonDown(DBUT, true, true, 20);

#define BLACK 0
#define WHITE 1
#define INVERSE 2


Adafruit_SharpMem display(SCK, MOSI, SS);
WatchMenu menu(display);

RTCx DS3231M(RTCx::DS1307Address);
RTCx MCP7941(RTCx::MCP7941xAddress);

byte activeTime = 15; //how many sec until entering standby
unsigned long standbyTimer;
boolean active = false;

static bool toggle = false;
  

void mainFunc()
{
  // Clear the display
  display.clearDisplay();
  display.refresh();

  display.setTextColor(BLACK);
  display.setTextSize(1);

  display.print("Here1");
  display.refresh();
}

//void initializeMenu()
//{
//#define NUM_MENUS           3
//#define MENU_MAIN_INDEX     0
//
//  menu.setTextSize(0);
//  
//  menu.initMenu(1);  // Create a menu system with ? menu rows
//  
//  menu.createMenu(MENU_MAIN_INDEX, 2, PSTR("< MAIN MENU >")); // 3 options
////  menu.createMenu(MENU_SUB_INDEX, 3, PSTR("< SET TIME >")); // 3 options
////  menu.createMenu(MENU_SUB_SUB_INDEX, 2, PSTR("< SLEEP >")); // 2 options
//
//  menu.createOption(MENU_MAIN_INDEX, 0, PSTR("Channels"), menu_stationBitmaps, mainFunc);
//  menu.createOption(MENU_MAIN_INDEX, 1, PSTR("Wireless"), menu_wirelessBitmaps, mainFunc);
////  menu.createOption(MENU_MAIN_INDEX, 2, PSTR("Scroll Speed"), menu_speedBitmaps, setDisplaySpeedFunc);
////  menu.createOption(MENU_MAIN_INDEX, 3, PSTR("Exit"), menu_exitBitmaps, backtoSchedule);
//
////  menu.createOption(MENU_SUB_INDEX, 0, PSTR("2.1st Option"), menu_alarmBitmaps, alarmFunc);
////  menu.createOption(MENU_SUB_INDEX, 1, PSTR("2.2nd Option"), menu_alarmBitmaps, MENU_SUB_SUB_INDEX);
////  menu.createOption(MENU_SUB_INDEX, 2, PSTR("2.Exit Option"), menu_exitBitmaps, MENU_EXIT);
////
////  menu.createOption(MENU_SUB_SUB_INDEX, 0, PSTR("3.1st Option"), menu_wirelessBitmaps, alarmFunc);
////  menu.createOption(MENU_SUB_SUB_INDEX, 1, PSTR("3.Exit Option"), menu_exitBitmaps, MENU_EXIT);
//
//  //!!!! Remove this later after buttons implemented  !!!!!!!
////  handleDefaultSelectOption();
//  
//  // Setup the pins for the buttons
////  setupButtons();
//}

//Wake from Middle Button
void wake()
{
  noInterrupts();  // Disable interrupts
  standbyTimer = millis()+activeTime*1000; // reset Standby Timer
  toggle = !toggle;
//  digitalWrite(EXTMODE, LOW); // switch VCOM to software
  interrupts();  //Enable interrupts
}

void setup()
{
  Serial.begin(9600);
  while (!Serial); 

  Serial.println("before Wire.begin()");
  Wire.begin();
  Serial.println("after Wire.begin()");
  
  Serial.print("MCP7941 Address=");
  Serial.println(MCP7941.getAddress(), HEX);

  // Ensure the oscillator is running.
  MCP7941.startClock();
  Serial.println("MCP7941.startClock()");

  MCP7941.setSQW(RTCx::freq1Hz);
  Serial.println("MCP7941.setSQW()");

  // Ensure the oscillator is running.
  DS3231M.startClock();
  Serial.println("DS3231M.startClock()");

//  DS3231M.setSQW(RTCx::freq1Hz);
//  Serial.println("DS3231M.setSQW()");

  // Clear any existing alarms
  DS3231M.clearAlarm(RTCx::ALARM1);
  DS3231M.clearAlarm(RTCx::ALARM2);

  // Enable alarm 2 
  DS3231M.enableAlarm(RTCx::ALARM2, true);
  Serial.println("DS3231M.enableAlarm()");

  DS3231M.setAlarm(RTCx::once_per_min);

  pinMode(EXTMODE, OUTPUT); //VCOM Mode (h=ext l=sw)
  digitalWrite(EXTMODE, HIGH); // switch VCOM to external

  // start & clear the display
  display.begin();
  display.clearDisplay();

  // Initialise the display
//  initializeMenu();

  // Button setups
  pinMode(MBUT, INPUT_PULLUP); // Middle Button Pullup
  pinMode(UBUT, INPUT_PULLUP); // Up Button Pullup
  pinMode(DBUT, INPUT_PULLUP); // Down Button Pullup

  pinMode(EXTMODE, OUTPUT);
  digitalWrite(EXTMODE, LOW); // switch VCOM to software

    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);

  attachInterrupt(MBUT, wake, FALLING); // Middle Button Interrupt
  attachInterrupt(UBUT, wake, FALLING); // Middle Button Interrupt
  attachInterrupt(DBUT, wake, FALLING); // Middle Button Interrupt

  //standbyTimer = millis()+activeTime*1000;

  buttonMid.read();
  buttonUp.read();
  buttonDown.read();
}

// Font data for Arial 48pt

extern const uint8_t arialNarrow_48ptBitmaps[];
extern const FONT_CHAR_INFO arialNarrow_48ptDescriptors[];
extern const uint8_t calibri_48ptBitmaps_colon[];
extern const FONT_CHAR_INFO calibri_48ptDescriptors_colon[];

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

void loop(void) 
{
//  active = (millis()<=standbyTimer); //check if active
//  buttonMid.read(); //read Button
//  Serial.print("active=");
//  Serial.println(active);
//
//  if(buttonMid.wasPressed())
//  { //read Buttons
//    buttonMid.read(); //make sure wasPressed is not activated again
//    Serial.println("Mid button pressed");
//    Serial.print("standbyTimer=");
//    Serial.println(standbyTimer);
//  }
//  bool animating = menu.updateMenu();
//  // Screen must be refreshed at least once per second
//  display.refresh();
//  if (animating)
//  {
//    delay(20);
//    display.clearDisplay();
//  }
//  else
//  {
     delay(500);
//  }
  
  buttonMid.read();
  if (buttonMid.wasPressed())
  {
    Serial.println("Mid wasPressed");
  }

  buttonUp.read();
  if (buttonUp.wasPressed())
  {
    Serial.println("Up wasPressed");
  }

  buttonDown.read();
  if (buttonDown.wasPressed())
  {
    Serial.println("Down wasPressed");
  }

  pinMode(EXTMODE, OUTPUT); //VCOM Mode (h=ext l=sw)
  digitalWrite(EXTMODE, HIGH); // switch VCOM to external
  
//  Serial.println("Looping");
  int xpos = 5;
  xpos += displayChar(xpos, 10, 0);
  xpos += displayChar(xpos, 10, 4);
  xpos += displayColon(xpos, 15);
  xpos += displayChar(xpos, 10, 4);
  xpos += displayChar(xpos, 10, 4);

  digitalWrite(LED, (toggle == true) ? HIGH : LOW);

  display.refresh();

  uint8_t stat = DS3231M.getStatus();
  Serial.print("DS3231M.getStatus():");
  Serial.println(stat, HEX);

  if (stat & A2F) // See if alarm2 is triggered
  {
    Serial.print("Alarm2 triggered at now:");
    Serial.println(millis());
    DS3231M.clearStatusBit(A2F);
  }
}


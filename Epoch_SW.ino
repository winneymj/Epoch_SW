#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <TimeLib.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <Button.h> // https://github.com/JChristensen/Button
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC

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
#define RTC_INT 9

#define EVERY_SECOND
//#define EVERY_MINUTE

#define BLACK 0
#define WHITE 1
#define INVERSE 2


Button buttonMid(MBUT, true, true, 20);
Button buttonUp(UBUT, true, true, 20);
Button buttonDown(DBUT, true, true, 20);

Adafruit_SharpMem display(SCK, MOSI, SS);
WatchMenu menu(display);
volatile boolean buttonRead = false; //variables in ISR need to be volatile
volatile boolean buttonFired = false; //variables in ISR need to be volatile
volatile boolean rtcRead = false; //variables in ISR need to be volatile
volatile boolean rtcFired = false; //variables in ISR need to be volatile

DS3232RTC MyDS3232;
//RTCx MCP7941(RTCx::MCP7941xAddress, RTCx::MCP7941x);

byte activeTime = 15; //how many sec until entering standby
unsigned long standbyTimer;
boolean active = false;

static bool toggle = false;

void enableInterrupts()
{
  // Enable EIC
  EIC->CTRL.bit.ENABLE = 1;
  while (EIC->STATUS.bit.SYNCBUSY == 1) { }
}

void disableInterrupts()
{
  // Enable EIC
  EIC->CTRL.bit.ENABLE = 0;
  while (EIC->STATUS.bit.SYNCBUSY == 1) { }
}

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

void RTC_int() //ISR for RTC interrupt overy minute
{
  disableInterrupts();
  rtcRead = !rtcRead;
  rtcFired = true;
  enableInterrupts();
}

void myISR() //ISR for button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.
  
  buttonRead = !buttonRead;
  buttonFired = true;
  enableInterrupts();
}

void initializePins()
{
  // Set pullups for all the interrupts
  pinMode(MBUT, INPUT_PULLUP);
  pinMode(UBUT, INPUT_PULLUP);
  pinMode(DBUT, INPUT_PULLUP);
  pinMode(RTC_INT, INPUT_PULLUP); // RTC Interrupt

  // Set LED pin to output.
  pinMode(LED, OUTPUT);

  // RTC square wave VCOM at 1Hz  
  pinMode(EXTMODE, OUTPUT); //VCOM Mode (h=ext l=sw)
//  digitalWrite(EXTMODE, HIGH); // switch VCOM to external

}

void initializeRTC()
{
  // Disable the RTC interrupts for the moment.
  MyDS3232.alarmInterrupt(ALARM_1, false);
  MyDS3232.alarmInterrupt(ALARM_2, false);

  // Attach button and RTC interrupt routine to the pins.
  attachInterrupt(digitalPinToInterrupt(MBUT), myISR, LOW); // when button B is pressed display 
  attachInterrupt(digitalPinToInterrupt(UBUT), myISR, LOW); // when button C is pressed display 
  attachInterrupt(digitalPinToInterrupt(DBUT), myISR, LOW); // when button C is pressed display battery status
  attachInterrupt(digitalPinToInterrupt(RTC_INT), RTC_int, LOW); // RTC Interrupt

  // Set RTC to interrupt every second for now just to make sure it works.
  // Will finally set to one minute.
#ifdef EVERY_SECOND
  MyDS3232.setAlarm(ALM1_EVERY_SECOND, 0, 0, 0);
  MyDS3232.alarmInterrupt(ALARM_1, true);
#endif
#ifdef EVERY_MINUTE
  MyDS3232.setAlarm(ALM2_EVERY_MINUTE, 0, 0, 0);
  MyDS3232.alarmInterrupt(ALARM_2, true);
#endif

  // Ensure the oscillator is running.
//  MCP7941.startClock();
//  Serial.println("MCP7941.startClock()");

//  MCP7941.setSQW(RTCx::freq1Hz);
//  Serial.println("MCP7941.setSQW()");
}

void sleepProcessor()
{
  //wait-for-interrupt has no effect unless the sleep bit is set in the
  //System Control Register (SCR)(see setup, in the attachInterrupt area)
  //if the sleep bit is set, we wait after this instruction for an interrupt 
//  PM->SLEEP.reg |= PM_SLEEP_IDLE_CPU;
  PM->SLEEP.reg |= PM_SLEEP_IDLE_APB;

  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;  // set to deep sleep (bit-1)

  // Clear the alarm interrupt in the RTC, else we will never wake up from sleep.
  // Very strange happening that only exhibits self when interrupt trigger is LOW.
#ifdef EVERY_SECOND
  uint8_t stat = MyDS3232.alarm(ALARM_1); 
//  Serial.println("sleep SECOND");
#endif
#ifdef EVERY_MINUTE
  uint8_t stat = MyDS3232.alarm(ALARM_2); 
//  Serial.println("sleep MINUTE");
#endif
  
//  Serial.println("sleep");
//  delay(500);
//  Serial.end();
  
  __WFI(); // Now wait for interrupt.
}

void setup()
{
  Serial.begin(9600);
//  while (!Serial); 

  Wire.begin();

  // Setup the pins for buttons etc.
  initializePins();

  // Initialize the RTC (DS3232 and MCP7941)
  initializeRTC();
  

  // start & clear the display
//  display.begin();
//  display.clearDisplay();

  // Initialise the display
//  initializeMenu();

//  pinMode(EXTMODE, OUTPUT);
//  digitalWrite(EXTMODE, LOW); // switch VCOM to software

  //standbyTimer = millis()+activeTime*1000;

  buttonMid.read();
  buttonUp.read();
  buttonDown.read();

//  Serial.println("setup: exit");
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
  // Sleep and wait for interrupt from buttons or RTC
  sleepProcessor();
  
  digitalWrite(LED, rtcRead ? HIGH : LOW);


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
//     delay(500);
//  }
  
  buttonMid.read();
  if (buttonMid.wasPressed())
  {
//    Serial.println("Mid wasPressed");
  }

  buttonUp.read();
  if (buttonUp.wasPressed())
  {
//    Serial.println("Up wasPressed");
  }

  buttonDown.read();
  if (buttonDown.wasPressed())
  {
//    Serial.println("Down wasPressed");
  }

//  pinMode(EXTMODE, OUTPUT); //VCOM Mode (h=ext l=sw)
//  digitalWrite(EXTMODE, HIGH); // switch VCOM to external
  
//  Serial.println("Looping");
//  int xpos = 5;
//  xpos += displayChar(xpos, 10, 0);
//  xpos += displayChar(xpos, 10, 4);
//  xpos += displayColon(xpos, 15);
//  xpos += displayChar(xpos, 10, 4);
//  xpos += displayChar(xpos, 10, 4);

//  digitalWrite(LED, (toggle == true) ? HIGH : LOW);

//  display.refresh();

}


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

#define SCK 19
#define MOSI 18
#define SS 23
#define EXTMODE 28

#define LED 6
#define MBUT 4
#define UBUT 14
#define DBUT 22
#define RTC_INT 9

#define INACTIVITY 10000

#define EVERY_SECOND
//#define EVERY_MINUTE
//#define SLEEP_PROCESSOR

extern void timeFunc();
extern const GFXfont courier_10x15FontInfo;


Adafruit_SharpMem display(SCK, MOSI, SS);
WatchMenu menu(display);
WatchMenu *currentMenu = &menu;

volatile boolean buttonRead = false; //variables in ISR need to be volatile
volatile boolean buttonFired = false; //variables in ISR need to be volatile
volatile boolean rtcRead = false; //variables in ISR need to be volatile
volatile boolean rtcFired = false; //variables in ISR need to be volatile
volatile uint8_t pinValM = false;
volatile uint8_t pinValD = false;
volatile uint8_t pinValU = false;

DS3232RTC MyDS3232;
RTCx MCP7941;

byte activeTime = 15; //how many sec until entering standby
unsigned long standbyTimer;
boolean active = false;

void enableInterrupts()
{
  // Enable EIC
  EIC->CTRL.bit.ENABLE = 1;
  while (EIC->STATUS.bit.SYNCBUSY == 1) { }
}

void disableInterrupts()
{
  // Disable EIC
  EIC->CTRL.bit.ENABLE = 0;
  while (EIC->STATUS.bit.SYNCBUSY == 1) { }
}

void menuDownFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuDownFunc(): Enter");
#endif
  menu.downOption();
}

void menuUpFunc()
{
#ifndef SLEEP_PROCESSOR
Serial.println("menuUpFunc(): Enter");
#endif
  menu.upOption();
}

void initializeMenu()
{
#define NUM_MENUS           3
#define MENU_MAIN_INDEX     0
#define MENU_DATE_TIME_INDEX     1

  menu.setTextSize(1);
  menu.setFont(&courier_10x15FontInfo);
  
  menu.initMenu(1);  // Create a menu system with ? menu rows
  
  menu.createMenu(MENU_MAIN_INDEX, 2, PSTR("<MAIN MENU>"), MENU_TYPE_ICON, menuDownFunc, menuUpFunc); // 3 options
//  menu.createMenu(MENU_SUB_INDEX, 3, PSTR("< SET TIME >")); // 3 options
//  menu.createMenu(MENU_SUB_SUB_INDEX, 2, PSTR("< SLEEP >")); // 2 options

  menu.createOption(MENU_MAIN_INDEX, 0, PSTR("Date & Time"), menu_clockBitmaps, timeFunc);
  menu.createOption(MENU_MAIN_INDEX, 1, PSTR("Exit"), menu_exitBitmaps, MENU_EXIT);
//  menu.createOption(MENU_MAIN_INDEX, 2, PSTR("Scroll Speed"), menu_speedBitmaps, setDisplaySpeedFunc);
//  menu.createOption(MENU_MAIN_INDEX, 3, PSTR("Exit"), menu_exitBitmaps, backtoSchedule);

//  menu.createOption(MENU_SUB_INDEX, 0, PSTR("2.1st Option"), menu_alarmBitmaps, alarmFunc);
//  menu.createOption(MENU_SUB_INDEX, 1, PSTR("2.2nd Option"), menu_alarmBitmaps, MENU_SUB_SUB_INDEX);
//  menu.createOption(MENU_SUB_INDEX, 2, PSTR("2.Exit Option"), menu_exitBitmaps, MENU_EXIT);
//
//  menu.createOption(MENU_SUB_SUB_INDEX, 0, PSTR("3.1st Option"), menu_wirelessBitmaps, alarmFunc);
//  menu.createOption(MENU_SUB_SUB_INDEX, 1, PSTR("3.Exit Option"), menu_exitBitmaps, MENU_EXIT);


  //!!!! Remove this later after buttons implemented  !!!!!!!
//  handleDefaultSelectOption();
  
  // Setup the pins for the buttons
//  setupButtons();
}

void RTC_int() //ISR for RTC interrupt overy minute
{
  disableInterrupts();
  rtcRead = !rtcRead;
  rtcFired = true;
  enableInterrupts();
}

void buttonISR_M() //ISR for Middle button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.\
  
  pinValM = true;

  buttonRead = !buttonRead;
  buttonFired = true;
  enableInterrupts();
}

void buttonISR_U() //ISR for Up button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.\
  
  pinValU = true;

  buttonRead = !buttonRead;
  buttonFired = true;
  enableInterrupts();
}

void buttonISR_D() //ISR for Down button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.\
  
  pinValD = true;

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
  digitalWrite(EXTMODE, HIGH); // switch VCOM to external
}

void initializeRTC()
{
  // Disable the RTC interrupts for the moment.
  MyDS3232.alarmInterrupt(ALARM_1, false);
  MyDS3232.alarmInterrupt(ALARM_2, false);

  // Attach button and RTC interrupt routine to the pins.
  attachInterrupt(digitalPinToInterrupt(MBUT), buttonISR_M, LOW); // when button B is pressed display 
  attachInterrupt(digitalPinToInterrupt(UBUT), buttonISR_U, LOW); // when button C is pressed display 
  attachInterrupt(digitalPinToInterrupt(DBUT), buttonISR_D, LOW); // when button C is pressed display battery status
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

  // Enable 32Khz output on pin 1
  MyDS3232.writeRTC(RTC_STATUS, MyDS3232.readRTC(RTC_STATUS) | _BV(EN32KHZ));

  // The address used by the DS1307 is also used by other devices (eg
  // MCP3424 ADC). Test for a MCP7941x device first.
  uint8_t addressList[] = {RTCx::MCP7941xAddress};

  // Autoprobe to find a real-time clock.
  MCP7941.autoprobe(addressList, sizeof(addressList));

  // Ensure the oscillator is running.
  MCP7941.startClock();
  MCP7941.setSQW(RTCx::freq1Hz);
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
  // and we want to deepsleep.
#ifdef EVERY_SECOND
  uint8_t stat = MyDS3232.alarm(ALARM_1); 
//  Serial.println("sleep SECOND");
#endif
#ifdef EVERY_MINUTE
  uint8_t stat = MyDS3232.alarm(ALARM_2); 
//  Serial.println("sleep MINUTE");
#endif
  
  __WFI(); // Now wait for interrupt.
}

void setup()
{
  Serial.begin(9600);
//  while (!Serial); 

  Serial.println("setup: enter");

  // Set up communications
  Wire.begin();

  // Set up display
  display.begin();

  // Setup the pins for buttons etc.
  initializePins();

  // Initialize the RTC (DS3232 and MCP7941)
  initializeRTC();
  
  display.clearDisplay();
  Serial.println("setup: clearDisplay");
  display.refresh();
  Serial.println("setup: refresh");

  display.setTextColor(BLACK);
  display.setTextSize(1);

  // Initialise the display
  initializeMenu();

//  pinMode(EXTMODE, OUTPUT);
//  digitalWrite(EXTMODE, LOW); // switch VCOM to software

  //standbyTimer = millis()+activeTime*1000;

//  buttonMid.read();
//  buttonUp.read();
//  buttonDown.read();

  Serial.println("setup: exit");
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

void loop(void) 
{
  digitalWrite(EXTMODE, HIGH); // switch VCOM to external

#ifdef SLEEP_PROCESSOR
  // Sleep and wait for interrupt from buttons or RTC
  sleepProcessor();
#else
  delay(1000);
#endif

  digitalWrite(EXTMODE, LOW); // switch VCOM to software.

  // If this is a RTC interrupt then need to
  // get the time and display it.
  if (rtcFired)
  {
    rtcFired = false;
    // Get the time from the RTC
    tmElements_t currTime;
    MyDS3232.read(currTime);

    displayTime(currTime);
  }

  // See if a button fired and woke up the processor.
  if (buttonFired)
  {
//  Serial.print("buttonFired=");
//  Serial.println(buttonFired);
    buttonFired = false;

    // Clear which button was pressed.
    pinValM = false;
    pinValU = false;
    pinValD = false;
    
    // get the current time in millis
    long pressStart = millis();
    
#ifndef SLEEP_PROCESSOR
Serial.print("pressStart=");
Serial.println(pressStart);
#endif
    while(true)
    {
      delay(10);
      rtcRead = !rtcRead;

      display.fillRect(0, 64, 128, 128, WHITE);
      bool animating = currentMenu->updateMenu();
      display.refresh();

      while (animating)
      {
//        display.clearDisplayBuffer();
        display.fillRect(0, 64, 128, 128, WHITE);
        animating = currentMenu->updateMenu();
        display.refresh();
        delay(20);
      }
    
//Serial.println("looping");
      if (pinValM)
      {
        pinValM = false;
        pressStart = millis();    // Reset the idle as we had a keypress
#ifndef SLEEP_PROCESSOR
Serial.print("pinValM=");
Serial.println(pinValM);
#endif
        currentMenu->selectOption(); 
      }
      if (pinValD)
      {
        pinValD = false;
        pressStart = millis();    // Reset the idle as we had a keypress
#ifndef SLEEP_PROCESSOR
Serial.print("pinValD=");
Serial.println(pinValD);
#endif
        currentMenu->menuDown();
      }
        
      if (pinValU)
      {
        pinValU = false;
#ifndef SLEEP_PROCESSOR
Serial.print("pinValU=");
Serial.println(pinValU);
#endif
        pressStart = millis();  // Reset the idle as we had a keypress
        currentMenu->menuUp();
      }
      // See if inactive and get out.
      long inactiveTimer = millis() - pressStart;
//Serial.print("inactiveTimer=");
//Serial.println(inactiveTimer);
      if (inactiveTimer > INACTIVITY)
      {
//Serial.println("getout");
        menu.resetMenu();
        break;
      }
    }// while
  }
  digitalWrite(LED, rtcRead ? HIGH : LOW);
}


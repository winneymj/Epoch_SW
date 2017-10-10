#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <TimeLib.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Watch_Menu.h>
#include <DS3232RTC.h>    // http://github.com/JChristensen/DS3232RTC
#include <RTCx.h>         // https://github.com/stevemarple/RTCx

#include "defs.h"

#define SCK 19
#define MOSI 18
#define SS 23
#define EXTMODE 28

extern void displayMenu();
extern void initializeMenu();
extern WatchMenu menu;
extern void displayTime();
extern void displayCalendar();


Adafruit_SharpMem display(SCK, MOSI, SS);
WatchMenu *currentMenu = &menu;
pFunc drawFunc = displayTime;
DS3232RTC MyDS3232;
RTCx MCP7941;

volatile boolean rtcRead = false; //variables in ISR need to be volatile
volatile boolean rtcFired = false; //variables in ISR need to be volatile
volatile uint8_t pinValM = false;
volatile uint8_t pinValD = false;
volatile uint8_t pinValU = false;

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
  enableInterrupts();
}

void buttonISR_U() //ISR for Up button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.\
  
  pinValU = true;
  enableInterrupts();
}

void buttonISR_D() //ISR for Down button presses
{
  disableInterrupts();  // This must exist, especially with the LOW trigger.  For some reason
  // when a LOW is interrupt trigger is received it continues to fire and locks the processor.
  // I am using a LOW trigger as I am planning to put the processor into deep sleep where the clocks
  // are disabled. Other triggers (FALLING, RISING etc) need the clock running to be triggered.\
  
  pinValD = true;
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
#endif
#ifdef EVERY_MINUTE
  uint8_t stat = MyDS3232.alarm(ALARM_2); 
#endif
  
  __WFI(); // Now wait for interrupt.
}

void setup()
{
  Serial.begin(9600);
//  while (!Serial); 

#ifndef SLEEP_PROCESSOR
  Serial.println("setup: enter");
#endif
  // Set up communications
  Wire.begin();

  // Set up display
  display.begin();

  // Setup the pins for buttons etc.
  initializePins();

  // Initialize the RTC (DS3232 and MCP7941)
  initializeRTC();
  
  display.clearDisplay();
  display.refresh();

  display.setTextColor(BLACK);
  display.setTextSize(1);

  // Initialise the display menu
  initializeMenu();

#ifndef SLEEP_PROCESSOR
  Serial.println("setup: exit");
#endif
}

bool updateDisplay()
{
#ifndef SLEEP_PROCESSOR
  Serial.println("updateDisplay(): enter");
#endif
  // If this is a RTC interrupt then need to
  // get the time and display it.
  if (rtcFired)
  {
    rtcFired = false;

    // Clear the display buffer before writing to the display.
    // Don't need to clear the display as the refresh will
    // write it all.
    display.clearDisplayBuffer();

    displayTime();

    displayCalendar();
// Clear the alarm interrupt
#ifdef EVERY_SECOND
    MyDS3232.alarm(ALARM_1);
#endif
#ifdef EVERY_MINUTE
    MyDS3232.alarm(ALARM_2);
#endif

    display.refresh();
  }
    
  // See if middle button fired and woke up the processor.
  if (pinValM)
  {
    // Clear which button was pressed.
    pinValM = false;
    pinValU = false;
    pinValD = false;

    // Display the menu on button press
    displayMenu();

    // Back from the menu so redisplay the watch face
    rtcFired = true;
    updateDisplay();
  }    
}

void loop(void) 
{
  // Display something before we sleep..just the first time
  rtcFired = true;
  updateDisplay();

  while (true)
  {
    // Before we sleep set the VCOM to external, the 1Hz VCOM signal
    digitalWrite(EXTMODE, HIGH); // switch VCOM to external
  

#ifdef SLEEP_PROCESSOR
  // Sleep and wait for interrupt from buttons or RTC
  sleepProcessor();
#else
  delay(1000);
#endif

    // If we got here we were woken up by interrupt
    digitalWrite(EXTMODE, LOW); // switch VCOM to software.

    updateDisplay();
  }

//  digitalWrite(LED, rtcRead ? HIGH : LOW);
}


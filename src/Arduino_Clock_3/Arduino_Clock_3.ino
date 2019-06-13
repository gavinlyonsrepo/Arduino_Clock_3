//******************* HEADER ********************************
/*
  Name : clock_number_3
  Title : Arduino RTC 
  Description : Arduino RTC using the TM1638 and DS3231
  Author: Gavin Lyons
  URL: https://github.com/gavinlyonsrepo/Arduino_Clock_3
*/

//*************************** LIBS  *****************
//Both in library manger 
// https://github.com/gavinlyonsrepo/TM1638plus
// https://github.com/JChristensen/DS3232RTC
#include <TM1638plus.h> // By Author 
#include <DS3232RTC.h> 

//*************************** GLOBALS & DEFINES********************

// TM1638 Setup
// I/O pins on the Arduino connected to Tm1638 strobe, clock, data
#define  STROBE_TM 6
#define  CLOCK_TM 7
#define  DIO_TM 8
TM1638plus TM1638(STROBE_TM, CLOCK_TM , DIO_TM);

// Intervals and delays
unsigned long previousMillis = 0;
const long  interval  = 225; // interval at which to debounce button readback function(milliseconds)
#define displayinterval  1500 // interval for displaying Info- once offs, hello etc

//Pin defines for alarm and buzzer
#define buzzer A2
#define AlarmInput 2

//Control vars
bool LEDS_on_flag = false;
bool Alarm_set = false;
uint8_t MainMode = 2;

// ********************* FUNCTIONS PROTOTYPES **************
void MainMenu(void); 
void Display(uint8_t DisplayMode); 
void ShowAlarm(void); 
void SleepMode(void); 
void SettingsMenuDisplay(void);
void SetTime(void);
void SetDate(uint8_t Hours , uint8_t Minutes);
void SetAlarm(void);
void Brightness(void);
uint8_t buttonsRead(void); 
void setLEDonoff(void); 


//***************** SETUP ************************
void setup() {
  /*Serial for debug only
  Serial.begin(9600);
  Serial.println("Arduino CLock three, Serial comms up, Start");*/

  //RTC
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    //Serial.println("Unable to sync with the RTC"); 
    while(1)TM1638.displayText("COnnFAiL");
  else
    //Serial.println("RTC has set the system time");
    __asm__("nop\n\t");

  //ALARM Setup
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  pinMode(AlarmInput, INPUT_PULLUP);
  ClearAlarm();

  TM1638.displayText("HELLO   ");
  delay(displayinterval);
}



//*************************** MAIN LOOP **************
void loop() {

  if (MainMode == 2) Display(MainMode);   //Default display
  MainMenu(); //Display MainMenu

  if ( !digitalRead(AlarmInput)  )
  {
    RTC.alarm(ALARM_2);    // reset the alarm flag
    digitalWrite(buzzer, HIGH);
    MainMode = 2;
  }
}


// ********************* FUNCTIONS SPACE *****************


//Function to Display Main Menu
void MainMenu(void)
{
  uint8_t buttons = buttonsRead();

  switch (buttons)
  {
    case 0x01:
      LEDS_on_flag = !LEDS_on_flag ;
      setLEDonoff();
      digitalWrite(buzzer, LOW);
      break;
    case 0x02 :
      MainMode = 2;
      Display(MainMode);
      break;
    case 0x04 :
      MainMode = 3;
      Display(MainMode);
      break;
    case 0x08 :
      MainMode = 4;
      Display(MainMode);
      break;
    case 0x10 :
      MainMode = 5;
      Display(MainMode);
      break;
    case 0x20 :
      MainMode = 6;
      ShowAlarm();
      break;
    case 0x40 :
      MainMode = 7;
      TM1638.displayText("SLEEP   ");
      delay(displayinterval);
      TM1638.reset();
      break;
    case 0x80 :
      MainMode = 8;
      SettingsMenuDisplay();
      break;
  }
}

// Function to display the settings menu Called from Main
void SettingsMenuDisplay(void)
{
  TM1638.displayText("SEttInGs");
  while (1)
  {
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case 0x02 : Display(2); break;
      case 0x04 :
        SetTime();
        break;
      case 0x08 : SetAlarm(); break;
      case 0x10 : Brightness(); break;

    }
    if (MainMode == 2) break;

  }
}

// Function to set the Time,  called from settings
void SetTime(void)
{
  char workstr[11];
  uint8_t Hours = 0;
  uint8_t Minutes = 0;
  while (1)
  {
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case  0x02 : MainMode = 2; break;
      case  0x04 :
        SetDate(Hours , Minutes);
        MainMode = 2;
        break;
      case  0x40 :
        Hours++;
        break;
      case  0x80 :
        Minutes++;
        break;
    }
    if (Hours == 24) Hours = 0;
    if (Minutes == 59) Minutes = 0;
    sprintf(workstr, "tS.  %02d.%02d", Hours, Minutes);
    TM1638.displayText(workstr);
    buttons = 0;
    if (MainMode == 2) break;
  }

}

// Function to Set Date called from setTime
// passed two integers with the time to set in hours and minutes
void SetDate(uint8_t Hours , uint8_t Minutes)
{
  char workstr[13];
  uint8_t Days = 0;
  uint8_t Months = 0;
  uint8_t Years = 0;
  MainMode = 0;

  while (1)
  {
    uint8_t buttons = buttonsRead();

    switch (buttons)
    {
      case  0x02 : MainMode = 2; break;
      case  0x04 : MainMode = 3; break;
      case  0x20 :
        Days++;
        break;
      case  0x40 :
        Months++;
        break;
      case  0x80 :
        Years++;
        break;
    }

    if (Days == 32) Days = 1;
    if (Months == 13) Months = 1;
    if (Years == 100) Years = 0;

    sprintf(workstr, "DS.%02d.%02d.%02d", Days, Months, Years);
    TM1638.displayText(workstr);
    buttons = 0;
    if (MainMode == 2) break;
    if (MainMode == 3)
    {
      time_t t;
      tmElements_t tm;
      tm.Year = y2kYearToTm(Years);
      tm.Month = Months;
      tm.Day = Days;
      tm.Hour = Hours;
      tm.Minute = Minutes;
      tm.Second = 0;
      t = makeTime(tm);
      RTC.set(t);        // use the time_t value to ensure correct weekday is set
      setTime(t);
      TM1638.displayText("tInESEt ");
      delay(displayinterval);
      break;
    }
  }
}

//Function to set Alarm called from settings
void SetAlarm(void)
{

  char workstr[11];
  uint8_t Hours = 0;
  uint8_t Minutes = 0;
  while (1)
  {
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case  0x02 : MainMode = 2; break;
      case  0x04 :
        //Set Alarm
        // set Alarm 2 for  RTC.setAlarm(alarmType, seconds, minutes, hours, dayOrDate);
        RTC.setAlarm(ALM2_MATCH_HOURS, 0, Minutes, Hours, 0);
        // clear the alarm flags
        RTC.alarm(ALARM_1);
        RTC.alarm(ALARM_2);
        // configure the INT/SQW pin for "interrupt" operation (disable square wave output)
        RTC.squareWave(SQWAVE_NONE);
        // enable interrupt output for Alarm 2 only
        RTC.alarmInterrupt(ALARM_1, false);
        RTC.alarmInterrupt(ALARM_2, true);
        Alarm_set = true;
        TM1638.displayText("ALRnSEt ");
        delay(displayinterval);
        MainMode = 2;
        break;
      case 0x08:
        digitalWrite(buzzer, HIGH);
        TM1638.displayText("ALRntESt");
        delay(displayinterval);
        digitalWrite(buzzer, LOW);
        break;
      case 0x10:
        // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
        ClearAlarm();
        Alarm_set = false;
        TM1638.displayText("ALRn CLr");
        delay(displayinterval);
        break;
      case  0x40 :
        Hours++;
        break;
      case  0x80 :
        Minutes = Minutes + 5;
        break;
    }
    if (Hours == 24) Hours = 0;
    if (Minutes == 60) Minutes = 0;
    sprintf(workstr, "AS.  %02d.%02d", Hours, Minutes);
    TM1638.displayText(workstr);
    buttons = 0;
    if (MainMode == 2) break;
  }
}

//Function to set brightness called from settings
void Brightness(void)
{

  uint8_t bright = 0x00;
  TM1638.displayText("        ");
  while (1)
  {
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case  0x02 : MainMode = 2; break;
      case  0x80 :
        bright++;
        break;
    }
    if (bright == 0x08)
    {
      bright = 0x00;
    }
    buttons = 0;
    TM1638.brightness(bright);
    TM1638.displayText("Bright");
    TM1638.displayHex(7, bright);
    if (MainMode == 2) break;
  }
}

// Displays selected display mode for Main Menu
//passed integer with display mode, 4 modes
//2.=  Just time HH.MM.SS
//3 =  just Date DD.MM.YYYY
//4 = Time and Date HH.MM.DD.MM
//5 = Temperature TEMP.NN.NN
void Display(uint8_t DisplayMode)
{
  tmElements_t tm;
  char timebuf[11]; // Time
  char datebuf[12]; // Date
  RTC.read(tm);
  switch (DisplayMode)
  {
    case 2 :
      sprintf(timebuf, "  %02d.%02d.%02d", tm.Hour, tm.Minute, tm.Second);
      TM1638.displayText(timebuf);
      break;
    case 3 :
      sprintf(datebuf, "%02d.%02d.%04d", tm.Day, tm.Month, tm.Year + 1970);
      TM1638.displayText(datebuf);
      break;
    case 4 :
      sprintf(datebuf, "%02d.%02d.%02d.%02d", tm.Hour, tm.Minute, tm.Day, tm.Month, tm.Year);
      TM1638.displayText(datebuf);
      break;
    case 5 :
      char workstr[12];
      uint16_t Temp = RTC.temperature();
      Temp = (Temp / 4.0) * 100;
      sprintf(workstr, "TEnP.%d%d.%d%d", (Temp / 1000) % 10, (Temp / 100) % 10, (Temp / 10) % 10, Temp % 10 );
      TM1638.displayText(workstr);
      break;
  }
}

//Switch All LEDS on  TM1638 on or off, if button S1 pressed on main menu
void setLEDonoff(void)
{
  for (uint8_t position = 0; position < 8; position++)
  {
    TM1638.setLED(position, LEDS_on_flag);
  }
}

// Show the alarm reads the SRAM of DS3231 for alarm 2 and gets
// values and displays them ,  called from main
void  ShowAlarm(void)
{
  
  if (Alarm_set == true)
  {
    byte minbyte, minupper , minlower = 0;
    byte hourbyte, hourupper, hourlower = 0;
    char alarmbuf[11]; // Time
    minbyte = RTC.readRTC(0x0B);  //read the minute byte value from SRAM location B
    hourbyte = RTC.readRTC(0X0C);  //read the hour byte  from SRAM location C

    minlower = (minbyte) & 0x0F;  // select lower nibble
    minupper =  (minbyte >> 4) & 0X0F; //select upper nibble
    minbyte = (minupper * 10) + minlower;

    hourlower = (hourbyte) & 0x0F;  // select lower nibble
    hourupper =  (hourbyte >> 4) & 0X0F; //select upper nibble
    hourbyte = (hourupper * 10) + hourlower;

    sprintf(alarmbuf, "ALrN.%02d.%02d", hourbyte, minbyte);
    TM1638.displayText(alarmbuf);
  } else {

    TM1638.displayText(" no ALrN");
  }


}

// Read and debounce the buttons form TM1638
uint8_t buttonsRead(void)
{
  uint8_t buttons = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    buttons = TM1638.readButtons();
  }
  return buttons;
}

// initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
// Called at init(optional) and also by ALarm clear option in Alarm menu
void ClearAlarm(void)
{
  RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
  RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
  RTC.alarm(ALARM_1);
  RTC.alarm(ALARM_2);
  RTC.alarmInterrupt(ALARM_1, false);
  RTC.alarmInterrupt(ALARM_2, false);
  RTC.squareWave(SQWAVE_NONE);
}

//*************************** EOF *****************************

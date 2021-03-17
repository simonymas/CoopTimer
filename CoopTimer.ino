/******************************************************************
 Created - 15.03.2021
 
 Project    : TIME CONTROLLER PROGRAM - cooptimer
 
 Libraries  : Wire.h //Included in Arduino IDE folder hardware/libraries/Wire
              TimeLib.h http://swfltek.com/arduino/timelord_library_deprecated.pdf
              TimeLord.h https://codebender.cc/library/TimeLord#TimeLord.h
              LiquidCrystal.h Included in Arduino IDE folder
              EEPROM.h Included in Arduino IDE folder
              avr/wdt.h Included in Arduino IDE folder
 
 Author     : Simon Nyrup Madsen
 
 DESCRIPTION:
 This program is designes to control relays on the basis of timers and manual inputs on a keypad.
 Its features includes:
 * Timekeeping and setting timers
 * Calculation of todays sunset and sunrise for automatic timekeeping
 * Control of 8 relays
 * Keypad and display for manual control and for chaning settings.
 In this version, the program is designed to manage a chicken coop with automatic lights as well as doors and nests operated by lineary actuators.
 
 USER INPUTS (SETTINGS IN CODE):
 * Default values at first upload - activate in Setup(), reset arduino and disabled in code before uploading again
 * Lounguitude and altitude - to determine times of sunset and sunrise
 * Default timer parameters and delays
 * Serial debug - set to true or false
    
 SUGGESTED IMPROVEMENTS:
 * Enable reset to preset values from keypad
 
 HARDWARE:  
 *  Arduino Uno/Mega (disable code for the board, that is not relevant to you)
 *  Clock-mocule DS3231 (insert rechargeable battery LIR2032)
        Power: 3.3V, ~3.0 microA
        Pins: Connect to SCL and SDA on Arduino and supplied from 3.3 V outlet and GND on Arduino
        Libraries: Wire.h, TimeLib.h v.7.2011
 *  Relay-module - 8 Realys in this version
        Power: 5V, max. 575 mA - external supply
        Pins: A8-15 (Arduino Mega), GND on arduino on pin side - seperate GND and power supply to VCC-JD from external power supply
 *  LCD Keypad Shield, DF Robot
        Power: 5V, 20-40 mA
        Pins: LCD D4-10, Keypad A0
        Library: LiquidCrystal.h
 *  Lineary actuators (connected to Relay)

******************************************************************/

//INCLUSION OF LIBRARIES - libraries compatible with Arduino IDE 1.8.13

  //  I2C connection
      #include <Wire.h> 
      
  //  Time features
      #include <TimeLib.h>
      #include <TimeLord.h>
                  
  //  LCD display
      #include  <LiquidCrystal.h>
      
  //  EEPROM to save settings to non-volatile memory on the board
      #include <EEPROM.h>
  
  //  Watchdog to reset
      #include <avr/wdt.h>

//DISTRIBUTION OF PINS
  //  Keypad
      #define KeyPad_IN A0
  
  //  Relay
      /* FOR ARDUNO UNO
      #define Relay_1 15 //door 15=A1 on ArduinoUno etc.
      #define Relay_2 16 //door 
      #define Relay_3 17 //nest
      #define Relay_4 18 //nest
      #define Relay_5 00 //nest
      #define Relay_6 00 //nest
      #define Relay_7 19 //light
      #define Relay_8 00 //light
      */

      //FOR ARDUINO MEGA
      #define Relay_1 A8 //door
      #define Relay_2 A9 //door 
      #define Relay_3 A10 //nest
      #define Relay_4 A11 //nest
      #define Relay_5 A12 //nest
      #define Relay_6 A13 //nest
      #define Relay_7 A14 //light
      #define Relay_8 A15 //light
                   
  //  LCD 1602
      LiquidCrystal LCD( 8, 9, 4, 5, 6, 7); //LCD pins set by syntax LiquidCrystal [Name](RS,E,D4,D5,D6,D7)
      #define DisplayLight_OUT 10 //Light intensity on display - usend in Setup_LCD()

  //  Real Time Clock DS3231  
      //RTC_SDA
      //RTC_SCL

//DISTRIBUTION OF EEPROM ADRESSES
  //  Eeprom-update
      #define Eeprom_status_address           0 
      
  //  Light
      #define LightOnMorning_set_address      1
      #define LightOnMorning_hour_address     2
      #define LightOnMorning_minute_address   3
      #define LightOffMorning_set_address     4
      #define LightOffMorning_hour_address    5
      #define LightOffMorning_minute_address  6
      #define TimeWithLight_hour_address      7
      #define TimeWithLight_minute_address    8
      
  //  Door
      #define DoorOpen_set_address            9
      #define DoorOpen_hour_address          10
      #define DoorOpen_minute_address        11 
      #define DoorClose_set_address          12
      #define DoorClose_hour_address         13
      #define DoorClose_minute_address       14   
      
  //  Nest
      #define NestOpen_set_address           15
      #define NestOpen_hour_address          16
      #define NestOpen_minute_address        17
      #define NestClose_set_address          18
      #define NestClose_hour_address         19
      #define NestClose_minute_address       20    

//DISTRIBUTION OF I2C ADRESSES

  //  Real time clock DS3231
      #define DS3231_I2C_ADDRESS 0x68

//DECLARATION OF GLOBAL VARIABLES AND SETTING SOME VALUES (SETTINGS)
    
  //  Activate debugging messages in serial screen - set to true to debug (Warning: if all is activated, dynamic memory will overload)
      const bool SerialDebugSetup = false;
      const bool SerialDebugDisplay = false;
      const bool SerialDebugControls = false;
      const bool SerialDebugTimers = false;
      const bool SerialDebugStatus = false;
      
  //  Constants and preset values for timer-variables (values used, when nothing has yet been saved in EEPROM, or if code overwriting EEPROM status variable is activated in setup-routine)
          
      //Light      
      #define LightOnMorning_set_preset     0 // Values: 1 = Time set below, 0 = Time set automatically to turn on in the morning if needed (using TimeWithLight_hours), 2 = Disabled - turn on manually
      #define LightOnMorning_hour_preset    5
      #define LightOnMorning_minute_preset  30

      #define LightOffMorning_set_preset    0 // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn off manually
      #define LightOffMorning_hour_preset   9
      #define LightOffMorning_minute_preset 00
      
      const int LightOffDelayAfterSunRise_minutes = 30; // Used if timer is set automatically
            
      #define TimeWithLight_hour_preset    12
      #define TimeWithLight_minute_preset   00
      
      const byte LightOnEvening_set = 2; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn on manually
      const byte LightOnEvening_hour = 20;
      const byte LightOnEvening_minute = 30;
      
      const byte LightOffEvening_set = 2; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn off manually
      const byte LightOffEvening_hour = 21;
      const byte LightOffEvening_minute = 55;
      
      const int LightOnDelayAfterSunSet_minutes = -15; // Used if timer is set automatically
      
      //Door
      #define DoorOpen_set_preset     0   // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - open manually
      #define DoorOpen_hour_preset    6
      #define DoorOpen_minute_preset  30
  
      const int DoorOpenDelayAfterSunRise_minutes = -15; // Used if timer is set automatically - delay after sun has risen

      #define DoorClose_set_preset    0   // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - close manually
      #define DoorClose_hour_preset   17
      #define DoorClose_minute_preset 17    
                
      const int DoorCloseDelayAfterCivilTwilight_minutes = 20; // Used if timer is set automatically. Civil twilight is 37-62 minutes after sunset at altitude of Denmark - less at 23 of october and december,and more at 23 rd of june and december
      
      const int DoorOpenProcessing_seconds = 40; //Time to open fully, when door is fully closed
      const int DoorCloseProcessing_seconds = 80; //Time to close door
      
      //Nest
      #define NestOpen_set_preset     0   // Values: 1 = Time set below, 0 = Time set automatically (at time of light), 2 = Disabled - open manually
      #define NestOpen_hour_preset    5
      #define NestOpen_minute_preset  0 
      
      const int NestOpenDelayAfterCivilTwilight_minutes = 0; // Used if timer is set automatically - delay after the minimum amount of light set has tuned on - or civil twilight, if this is earlier

      #define NestClose_set_preset    1   // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - close manually
      #define NestClose_hour_preset   14
      #define NestClose_minute_preset 30
      
      const int NestCloseDelayAfterDoorClose_minutes = -60; // Used if timer is set automatically - time to wait to close nests after doors have closed
      
      const int NestOpenProcessing_seconds = 30; //Time to run open routine 
      const int NestCloseProcessing_seconds = 30; //Time to run close routine

  //  Time - variables used to display and change time from menus
      byte Time_hour;
      byte Time_minute;
      byte Time_day;
      byte Time_month;
      int Time_year;
  
  //  Location (used by TimeLord-library to calculate sunrise and sunset times)
      const float Lattitude = 55.783748, Longitude = 11.939181; //Currently set to position of Skibby, Denmark - change if location is changed - and change values for civil twilight in setup_sun()!

  //  Intensity of backgrund light on reset - set a number between 0 and 255
      const int DisplayLightIntensity = 120;

  //  KeyPad and display
      int  SensitivityKeypad = 500; //  Set sensitivity of buttons on keypad in miliseconds - don't exceed 500 not to trigger Watchdog reset
      int MenuReset = 50; // Seconds before menu exits, so loop can continue. If value is to high, system will reset (don´t know why...)

  //  Menu structure
      #define MenuMax     7  //Defines number of menues
      
      #define Lines_menu1 2  // Define number of lines in each menu
      #define Lines_menu2 8    
      #define Lines_menu3 8
      #define Lines_menu4 7
      #define Lines_menu5 6
      #define Lines_menu6 6
      #define Lines_menu7 7

//DECLARATION OF SOME ADDITIONAL GLOBAL VARIABLES USED BY THE FUNCTIONS - don't cahnge!

  //  Calculated in Setup_sun()
      time_t TodaysSunRise_t; 
      time_t TodaysSunSet_t;
      time_t TodaysCivilTwilightMorning_t;
      time_t TodaysCivilTwilightEvening_t;

  //  Calculated in Setup_timer()   
      int TimeWithElectricLight_seconds;
      time_t LightOnMorning_t; 
      time_t LightOffMorning_t;
      time_t LightOnEvening_t;
      time_t LightOffEvening_t;
      time_t DoorOpen_t;
      time_t DoorClose_t;
      time_t NestOpen_t;
      time_t NestClose_t;

  //  Calcultated in Input_keypad();
      time_t Adjusted_time;

  //  Define global variables and read values from EEPROM
      //Eeprom-update
      byte Eeprom_status = EEPROM.read(Eeprom_status_address);
      
      //Light           
      byte LightOnMorning_set = EEPROM.read(LightOnMorning_set_address);
      byte LightOnMorning_hour = EEPROM.read(LightOnMorning_hour_address);
      byte LightOnMorning_minute = EEPROM.read(LightOnMorning_minute_address);
      
      byte LightOffMorning_set = EEPROM.read(LightOffMorning_set_address);
      byte LightOffMorning_hour = EEPROM.read(LightOffMorning_hour_address);
      byte LightOffMorning_minute = EEPROM.read(LightOffMorning_minute_address);
      
      byte TimeWithLight_hour = EEPROM.read(TimeWithLight_hour_address);
      byte TimeWithLight_minute = EEPROM.read(TimeWithLight_minute_address);
      
      //Door
      byte DoorOpen_set = EEPROM.read(DoorOpen_set_address);
      byte DoorOpen_hour = EEPROM.read(DoorOpen_hour_address);
      byte DoorOpen_minute = EEPROM.read(DoorOpen_minute_address);
          
      byte DoorClose_set = EEPROM.read(DoorClose_set_address);
      byte DoorClose_hour = EEPROM.read(DoorClose_hour_address);
      byte DoorClose_minute = EEPROM.read(DoorClose_minute_address);
      
      //Nest
      byte NestOpen_set = EEPROM.read(NestOpen_set_address);
      byte NestOpen_hour = EEPROM.read(NestOpen_hour_address);
      byte NestOpen_minute = EEPROM.read(NestOpen_minute_address);

      byte NestClose_set = EEPROM.read(NestClose_set_address);
      byte NestClose_hour = EEPROM.read(NestClose_hour_address);
      byte NestClose_minute = EEPROM.read(NestClose_minute_address);
      
  //  Used in Input_keypad and Display_menu functions
      int KeyStatus = 0;
      int KeyValue = 0;     
      byte Pos = 11;
      byte Cur = 2;     //Values:  2: cursor off, 0: Cursor line 0, 1: cur line 1
      byte CurSelect = 0;  //Values:  1: Line selected, 0: Line not selected
      byte PosLast = 0;
      byte CurDel = 2;
      byte Line = 0;
      byte ValueChanged =0;

  //  Variables used in Check_status fucntions
      byte LightStatus = 0; //Values: 0 = No light nedded; 1 = Morning light has not been turned on yet, 2 = Morning light is turned on, 3 = Morning light has been turned off, 4 = Evening light is turned on)
      byte DoorStatus = 0; //Values: 0 = Not set; 1 = Closed; 2 = Opening; 3 = Open; 4 = Closing - See explanation in Check_door_status
      byte NestStatus = 0; //Values: 0 = Not set; 1 = Closed; 2 = Opening; 3 = Open; 4 = Closing
      
      byte DoorActualPosition = 0; //Values: 0 = Unkonown; 1 = Open; 2 = Closed;
      byte NestActualPosition = 0; //Values: 0 = Unkonown; 1 = Open; 2 = Closed;
            
  //  From Setup_reset functions
      time_t ResetTime_t;
      time_t MenuReset_t;

  //  Variable to determine, if DST is set. Values: 1 = DST is activated, 0 = Normal time is activated - always set to 0 at startup
      byte DST = 0;

//SETUP ROUTINE - runs only once    
void setup()
{  
  //  Define PINs as input/output
      Setup_pins();       
        
  //  Initiate serial screen
      Serial.begin(9600);

  //  Initiate LCD, set background light intensity and define special characters
      Setup_LCD();
          
  //  Get values from EEPROM
      //Eeprom_status = 0; // 0 = Force EEPROM to reset to preset values above  - Values of adress 0: 1 = Take user saved values from eeprom, 0 = Save preset values to eeprom agian - RESTART to have them loaded into RAM 2 = Update eeprom with new time-values set by Keypad
      Setup_eeprom();
  
  //  Upload initial time on DS3231 - after setting time, disable theese two lines in code and upload again - otherwise the time will be reset to preset values entered below every time arduino resets!
      //setTime(12, 30, 0, 15, 3, 21); // Key: Hour, minute, second, day, month, year
      //Setup_DS3231_fra_arduino_time();
      
  //  Get time from DS3231
      Setup_arduino_from_DS3231_time();
  
  //  Setup arduino to reset at 00:00:00 the following day
      Setup_reset();
   
  //  Display update message to indicate, that reset has been done
      Display_notice_menu(Display_update, 500); //Don´t set to high, so that watchdog is not activated (after 8 secs. without reset)
  
  //  Calculate time of sunrise and sunset
      Setup_sun();
 
  //  Set timers and light
      Setup_light_timer();
      Setup_door_timer();
      Setup_nest_timer();
}

//PROGRAM - runs in loop - functions defined in other tabs
void loop()
{
  //  Check to se, if it is time to reset Arduino - if not, watch dog timer is reset - this also prevents Arduino to fuck up, sinse it resets every 8 seconds if this function is not called
      Reset_watchdog_timer();
  
  //  Check keypad, timers, display status and initate events
      Initiate_light_event(); 
      
      Initiate_door_event();
      
      Initiate_nest_event();
      
      Input_keypad();

  //  Refresh LCD to show current menu
      Display_menu();
}


//GENERAL UTILITY FUNCTIONS

  //  Calculate time_t for TODAYS occurrance from input hour and minute
  time_t Time_t(byte Hour, byte Minute)
  {
   time_t Todays_t;
   TimeElements tm;
   tm.Hour = Hour;
   tm.Minute = Minute;
   tm.Second = 0;
   tm.Day = day();
   tm.Month = month();
   tm.Year = year()-1970;
   Todays_t = makeTime(tm);
   return Todays_t;
  }
  
  //  Calculate time_t for NEXT occurrance from input hour and minute
  time_t Time_next_t(byte Hour, byte Minute)
  {
   time_t Next_t;
   TimeElements tm;
   tm.Hour = Hour;
   tm.Minute = Minute;
   tm.Second = 0;
   if ((hour() >= Hour) && (minute() >= Minute))
   {
     tm.Day = day() + 1;
   }
   else
   {
     tm.Day = day();
   }
   tm.Month = month();
   tm.Year = year()-1970;
   Next_t = makeTime(tm);
   return Next_t;
  }
 
  //  Calculate time_t for specific DATE
  time_t Time_date_t(byte Day, byte Month)
  {
   time_t Date_t;
   TimeElements tm;
   tm.Hour = 23;
   tm.Minute = 59;
   tm.Second = 59;
   tm.Day = Day;
   tm.Month = Month;
   tm.Year = year()-1970;
   Date_t = makeTime(tm);
   return Date_t;
  }

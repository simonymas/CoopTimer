/* TIME CONTROLLER PROGRAM

This program is designes to control relays on the basis of timers and manual inputs on a keypad.

Its features includes:
 * Timekeeping and setting timers
 * Calculation of todays sunset and sunrise for automatic timekeeping
 * Control of 8 relays
 * Keypad and display for manual control.

In this version, the program is designed to manage a chicken coop with automatic lights as well as doors and nests operated by lineary actuators.

Hardware set-up:
 *  Arduino Uno/Mega (Disable code for the board, that is not relevant to you)
 *  Clock-mocule DS3231 (Insert rechargeable battery LIR2032. Connect to SCL and SDA on Arduino and supplied from 3.3 V outlet and GND on Arduino)
 *  Relay-module (Connect to GND on arduino on pin side - but with seperate GND and power supply to VCC-JD)
 *  LCD Keypad Shield
 *  Temperature sensor S18B20 (Currently disabled in code)
 *  Lineary actuators
*/

//INCLUSION OF LIBRARIES - libraries compatible with Arduino IDE 1.6.1

  //  I2C connection
      #include <Wire.h> //Included in Arduino IDE folder hardware/libraries/Wire
      
  //  Time features
      #include <TimeLib.h> //https://codebender.cc/library/TimeLord#TimeLord.h - place in sketchbook folder as specified in Files/Preferences/
      #include <TimeLord.h> //http://swfltek.com/arduino/timelord_library_deprecated.pdf - place in sketchbook folder as specified in Files/Preferences/
            
  //  Temperature
      #include <OneWire.h> //http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip - place in sketchbook folder as specified in Files/Preferences/
      //#include <DallasTemperature.h> //http://www.milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library#Download - place in sketchbook folder as specified in Files/Preferences/
      
  //  LCD display
      #include  <LiquidCrystal.h> //Included in Arduino IDE folder
      
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

  //  Temperature sensor DS18B20
      //#define Temp_PWM 11

  //  Real Time Clock DS3231  
      //RTC_SDA; - asigned by Wire library
      //RTC_SCL; - asigned by Wire library
      //GND
      //3,3V
            
//SETTINGS
    
  //  Activate debugging messages in serial screen - set to true to debug (Warning: if all is activated, dynamic memory will overload)
      const bool SerialDebugSetup = true;
      const bool SerialDebugDisplay = true;
      const bool SerialDebugControls = true;
      const bool SerialDebugTimers = true;
      const bool SerialDebugStatus = false;
      
  //  Timers     
      //Light        
      const byte LightOnMorning_set = 3; // Values: 1 = Time set below, 0 = Time set automatically to turn on in the morning and evening if needed (using TimeWithLight_hours), 2 = Disabled - turn on manually, 3 = Time set automatically to turn on only in the morning if needed
      const byte LightOnMorning_hour = 6;
      const byte LightOnMorning_minute = 37;
      
      const byte LightOffMorning_set = 1; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn off manually
      const byte LightOffMorning_hour = 15;
      const byte LightOffMorning_minute = 00;
      const int LightOffDelayAfterSunRise_minutes = 30; // Used if timer is set automatically

      const byte LightOnEvening_set = 2; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn on manually
      const byte LightOnEvening_hour = 20;
      const byte LightOnEvening_minute = 30;
      
      const byte LightOffEvening_set = 0; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - turn off manually
      const byte LightOffEvening_hour = 21;
      const byte LightOffEvening_minute = 55;
      const int LightOnDelayAfterSunSet_minutes = -5; // Used if timer is set automatically
      
      const byte TimeWithLight_hours = 12;
      
      //Door
      const byte DoorOpen_set = 0; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - open manually
      const byte DoorOpen_hour = 6;
      const byte DoorOpen_minute = 30;
      const int DoorOpenDelayAfterSunRise_minutes = -15; // Used if timer is set automatically - delay after sun has risen
          
      const byte DoorClose_set = 0; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - close manually
      const byte DoorClose_hour = 17;
      const byte DoorClose_minute = 17;
      const int DoorCloseDelayAfterCivilTwilight_minutes = 20; // Used if timer is set automatically. Civil twilight is 37-62 minutes after sunset at altitude of Denmark - less at 23 of october and december,and more at 23 rd of june and december
      
      const int DoorOpenProcessing_seconds = 40; //Time to open fully, when door is fully closed
      const int DoorCloseProcessing_seconds = 80; //Time to close door
      
      //Nest
      const byte NestOpen_set = 0; // Values: 1 = Time set below, 0 = Time set automatically (at time of light), 2 = Disabled - open manually
      const byte NestOpen_hour = 5;
      const byte NestOpen_minute = 00;
      const int NestOpenDelayAfterCivilTwilight_minutes = 0; // Used if timer is set automatically - delay after the minimum amount of light set has tuned on - or civil twilight, if this is earlier

      const byte NestClose_set = 1; // Values: 1 = Time set below, 0 = Time set automatically, 2 = Disabled - close manually
      const byte NestClose_hour = 16;
      const byte NestClose_minute = 15;
      const int NestCloseDelayAfterDoorClose_minutes = -30; // Used if timer is set automatically - time to wait to close nests after doors have closed
      
      const int NestOpenProcessing_seconds = 30; //Time to run open routine 
      const int NestCloseProcessing_seconds = 30; //Time to run close routine

  //  Location (used by TimeLord-library to calculate sunrise and sunset times)
      const float Lattitude = 55.783748, Longitude = 11.939181; //Currently set to position of Skibby, Denmark - change if location is changed - and change values for civil twilight in setup_sun()!

  //  Intensity of backgrund light on reset - set a number between 0 and 255
      const int DisplayLightIntensity = 190;

        
//DEFINITION OF SOME VARIABLES AND VALUES FOR THE FUNCTIONS - donn't change
  
  //  Variable to determine, if DST is set. Values: 1 = DST is activated, 0 = Normal time is activated - always set to 0 at startup
      byte DST = 0;
      
  //  Variables used in checks
      int LightStatus = 0; //Values: 0 = No light nedded; 1 = Morning light has not been turned on yet, 2 = Morning light is turned on, 3 = Morning light has been turned off, 4 = Evening light is turned on)
      int DoorStatus = 0; //Values: 0 = Not set; 1 = Closed; 2 = Opening; 3 = Open; 4 = Closing - See explanation in Check_door_status
      int NestStatus = 0; //Values: 0 = Not set; 1 = Closed; 2 = Opening; 3 = Open; 4 = Closing
      
      byte DoorActualPosition = 0; //Values: 0 = Unkonown; 1 = Open; 2 = Closed;
      byte NestActualPosition = 0; //Values: 0 = Unkonown; 1 = Open; 2 = Closed;
      
      int  TimeWithElectricLight_seconds; //Calculation in Setup_light_timer;
      
  //  Time_t numbers
      time_t ResetTime_t;
      
      time_t TodaysSunRise_t; //Calculated in Setup_sun();
      time_t TodaysSunSet_t;
      time_t TodaysCivilTwilightMorning_t;
      time_t TodaysCivilTwilightEvening_t;
          
      time_t LightOnMorning_t; 
      time_t LightOffMorning_t;
      time_t LightOnEvening_t;
      time_t LightOffEvening_t;
               
      time_t DoorOpen_t;
      time_t DoorClose_t;
      
      time_t NestOpen_t;
      time_t NestClose_t;

      time_t MenuReset_t;
               
  //  Temperature
      /*
      OneWire oneWire(Temp_PWM); 
      DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
      float temp = sensors.getTempCByIndex(0);
      */
       
  //  KeyPad and display fuctions
      int KeyStatus = 0;
      int KeyValue = 0;
            
      byte Pos = 11;
      byte Cur = 2;
      byte PosLast = 0;
      byte CurDel = 2;

      byte Line = 0;
      int  SensitivityKeypad = 500; //  Set sensitivity of buttons on keypad in miliseconds - don't exceed 500 not to trigger Watchdog reset
      int MenuReset = 30; // Seconds before menu exits,so loop can continue. If value is to high, system will resets (don´t know why...)

//SETUP ROUTINE - runs only once    
void setup()
{
  //  Starting I2C communication by Wire-library  
      Setup_i2c();
  
  //  Define PINs as input/output
      Setup_pins();       
        
  //  Initiate serial screen
      Serial.begin(9600);

  //  Initiate LCD, set background light intensity and define special characters
      Setup_LCD();
          
  //  Temperature
      //sensors.begin();
      
  //  Upload initial time on DS3231 - after setting time, disable line in code and upload again - otherwise the time will be reset to the time entered below every time arduino resets!
      //Setup_time_initial(00,10,9,3,3,11,20); // Key: (seconds, minutes, hours, weekday (1=Sunday, 7=Saturday), date, month, year)
      //ALWAYS SET TO NORMAL TIME, NOT TAKING DAYLIGHT SAVING TIME INTO ACCOUNT - in between last sunday of march and last sunday of october, one hour should be substracted from time on your watch
               
  //  Sync time from DS3231
      Setup_time_sync();
  
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
      //Display_temperature_LCD();
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
      
  //  Get temperature from DS18B20
      //Input_temp();
      
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

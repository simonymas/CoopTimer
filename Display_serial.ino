//FUNCTIONS TO DISPLAY CONTENT ON SERIAL SCREEN
       
  //  Setup debug functions
      void Display_Setup_i2c_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_i2c()");}}
          
      void Display_Setup_pins_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_pins()");}}

      void Display_Setup_LCD_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_LCD()");}}

      void Display_Setup_time_sync_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_time_sync()");}}

      void Display_Setup_reset_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_reset()");}}
        
      void Display_Setup_sun_serial()
      {if (SerialDebugSetup){Serial.println();Serial.print("Setup_sun()");}}

  //  Display debug functions
      void Display_Display_update_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Display_update()");}}
           
      void Display_Display_time_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Display_time()");}}

      void Display_Input_keypad_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Input_keypad() - KeyStatus = ");Serial.print(KeyStatus);Serial.print(" Pos = ");Serial.print(Pos);Serial.print(" Cur = ");Serial.print(Cur);Serial.print(" CurSelect = ");Serial.print(CurSelect);}}

      void Display_Display_menu11_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Display_menu11() - Menu = 1, Pos = ");Serial.print(Pos);}}

      void Display_Display_menu12_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Display_notice_menu12() - Menu = 1, Pos = ");Serial.print(Pos);}}
      
      void Display_Display_menu_serial()
      {if (SerialDebugDisplay){Serial.println();Serial.print("Display_menu() - Menu = ");Serial.print(Active_menu());Serial.print(" - Pos = ");Serial.print(Pos);}}

  //  Control debug funtions
      void Display_Reset_watchdog_timer_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Reset_watchdog_timer()");}}

      void Display_Check_light_status_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Check_light_status()");}}

      void Display_Check_door_status_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Check_door_status()");}}

      void Display_Check_nest_status_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Check_nest_status()");}}

      void Display_Initiate_light_event_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Initiate_light_event()");}}
 
      void Display_Initiate_door_event_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Initiate_door_event()");}}
        
      void Display_Initiate_nest_event_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Initiate_nest_event()");}}

      void Display_Motor_open_door_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_open_door()");}}
      
      void Display_Motor_close_door_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_close_door()");}}

      void Display_Motor_open_nest_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_open_nest()");}}
      
      void Display_Motor_close_nest_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_close_nest()");}}

      void Display_Motor_on_light_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_on_light()");}}
      
      void Display_Motor_off_light_serial()
      {if (SerialDebugControls){Serial.println();Serial.print("Motor_off_light()");}}
  //  Timers debug functions
  
      //Time and date
      void Display_time_serial()
      {if (SerialDebugTimers)
      {
      Serial.println();
      Serial.print("Now: ");
      Serial.print(day());
      Serial.print(".");
      switch(month())
      {
       case 1: Serial.print(" jan.");break;
       case 2: Serial.print(" febr.");break;
        case 3: Serial.print(" marts");break;
        case 4: Serial.print(" april");break;
        case 5: Serial.print(" maj");break;
        case 6: Serial.print(" juni");break;
        case 7: Serial.print(" juli");break;
        case 8: Serial.print(" aug.");break;
        case 9: Serial.print(" sept.");break;
        case 10: Serial.print(" okt.");break;
        case 11: Serial.print(" nov.");break;
        case 12: Serial.print(" dec.");break;
        default: Serial.print(" Fejl!");break;
       }
       Serial.print(" ");
       Serial.print(year());
       Serial.print(" ");
       SerialprintDigits(hour());
       Serial.print(":");
       SerialprintDigits(minute());
       if (DST == 1)
       {
        Serial.print(" (DST)");
       }
       if (DST == 0)
       {
       Serial.print(" (not DST)");
       }
       Serial.println();
       }
      }
            
      // Todays sunrise / sunset
      void Display_sunrise_sunset_serial(){if (SerialDebugTimers)
      {
        Serial.print ("Todays sunrise: ");
        SerialprintDigits (hour(TodaysSunRise_t));
        Serial.print (":");
        SerialprintDigits (minute((TodaysSunRise_t)));
        Serial.print (" ");
        Serial.print (day(TodaysSunRise_t));
        Serial.print ("/");
        Serial.print (month(TodaysSunRise_t));
        Serial.print (" ");
        Serial.println (year(TodaysSunRise_t));
               
        Serial.print ("Todays sunset: ");
        SerialprintDigits (hour(TodaysSunSet_t));
        Serial.print (":");
        SerialprintDigits (minute((TodaysSunSet_t)));
        Serial.print (" ");
        Serial.print (day(TodaysSunSet_t));
        Serial.print ("/");
        Serial.print (month(TodaysSunSet_t));
        Serial.print (" ");
        Serial.println (year(TodaysSunSet_t));
        
        Serial.print ("Todays civil twilight morning: ");
        SerialprintDigits (hour(TodaysCivilTwilightMorning_t));
        Serial.print (":");
        SerialprintDigits (minute((TodaysCivilTwilightMorning_t)));
        Serial.print (" ");
        Serial.print (day(TodaysCivilTwilightMorning_t));
        Serial.print ("/");
        Serial.print (month(TodaysCivilTwilightMorning_t));
        Serial.print (" ");
        Serial.println (year(TodaysCivilTwilightMorning_t));
        
        Serial.print ("Todays civil twilight evening: ");
        SerialprintDigits (hour(TodaysCivilTwilightEvening_t));
        Serial.print (":");
        SerialprintDigits (minute((TodaysCivilTwilightEvening_t)));
        Serial.print (" ");
        Serial.print (day(TodaysCivilTwilightEvening_t));
        Serial.print ("/");
        Serial.print (month(TodaysCivilTwilightEvening_t));
        Serial.print (" ");
        Serial.println (year(TodaysCivilTwilightEvening_t));
        
        Serial.print ("Reset time: ");
        SerialprintDigits (hour(ResetTime_t));
        Serial.print (":");
        SerialprintDigits (minute((ResetTime_t)));
        Serial.print (" ");
        Serial.print (day(ResetTime_t));
        Serial.print ("/");
        Serial.print (month(ResetTime_t));
        Serial.print (" ");
        Serial.println (year(ResetTime_t));
      }}
  
      //  Light timer
      void Display_Setup_light_timer_serial(){if (SerialDebugTimers)
      {
        Serial.print ("Setup_light_timer()");
        Serial.print ("Time with light (manually set): ");
        Serial.println (TimeWithLight_hour);
        Serial.println (":");
        Serial.println (TimeWithLight_minute);

        Serial.print ("Seconds with electric light (calculated): ");
        Serial.println (TimeWithElectricLight_seconds);
        
        Serial.print ("Morning light on: ");
        SerialprintDigits (hour(LightOnMorning_t));
        Serial.print (":");
        SerialprintDigits (minute((LightOnMorning_t)));
        Serial.print (" ");
        Serial.print (day(LightOnMorning_t));
        Serial.print ("/");
        Serial.print (month(LightOnMorning_t));     
        Serial.print (" ");
        Serial.print (year(LightOnMorning_t));
        Serial.print (" time_t number:");
        Serial.println (LightOnMorning_t);
       
        Serial.print ("Morning light off: ");
        SerialprintDigits (hour(LightOffMorning_t));
        Serial.print (":");
        SerialprintDigits (minute((LightOffMorning_t))); 
        Serial.print (" ");
        Serial.print (day(LightOffMorning_t));
        Serial.print ("/");
        Serial.print (month(LightOffMorning_t));
        Serial.print (" ");
        Serial.println (year(LightOffMorning_t));
        
        Serial.print ("Evening light on: ");
        SerialprintDigits (hour(LightOnEvening_t));
        Serial.print (":");
        SerialprintDigits (minute((LightOnEvening_t)));
        Serial.print (" ");
        Serial.print (day(LightOnEvening_t));
        Serial.print ("/");
        Serial.print (month(LightOnEvening_t));
        Serial.print (" ");
        Serial.println (year(LightOnEvening_t));
       
        Serial.print ("Evening light off: ");
        SerialprintDigits (hour(LightOffEvening_t));
        Serial.print(":");
        SerialprintDigits (minute((LightOffEvening_t))); 
        Serial.print (" ");
        Serial.print (day(LightOffEvening_t));
        Serial.print ("/");
        Serial.print (month(LightOffEvening_t));
        Serial.print (" ");
        Serial.println (year(LightOffEvening_t));      
      }}
  
      //  Door timer
      void Display_Setup_door_timer_serial(){if (SerialDebugTimers)
      {
        Serial.print ("Setup_door_timer()");
        Serial.print ("Door opens: ");
        SerialprintDigits (hour(DoorOpen_t));
        Serial.print (":");
        SerialprintDigits (minute((DoorOpen_t)));
        Serial.print (" ");
        Serial.print (day(DoorOpen_t));
        Serial.print ("/");
        Serial.print (month(DoorOpen_t));     
        Serial.print (" ");
        Serial.print (year(DoorOpen_t));
        Serial.print (" time_t number:");
        Serial.println (DoorOpen_t);
       
        Serial.print ("Door closes: ");
        SerialprintDigits (hour(DoorClose_t));
        Serial.print (":");
        SerialprintDigits (minute((DoorClose_t))); 
        Serial.print (" ");
        Serial.print (day(DoorClose_t));
        Serial.print ("/");
        Serial.print (month(DoorClose_t));
        Serial.print (" ");
        Serial.println (DoorClose_t);
      }}
  
      //  Nest timer
      void Display_Setup_nest_timer_serial(){if (SerialDebugTimers)
      {
        Serial.print ("Setup_nest_timer()");
        Serial.print ("Nests open: ");
        SerialprintDigits (hour(NestOpen_t));
        Serial.print (":");
        SerialprintDigits (minute((NestOpen_t)));
        Serial.print (" ");
        Serial.print (day(NestOpen_t));
        Serial.print ("/");
        Serial.print (month(NestOpen_t));     
        Serial.print (" ");
        Serial.print (year(NestOpen_t));
        Serial.print (" time_t number:");
        Serial.println (NestOpen_t);
       
        Serial.print ("Nests close: ");
        SerialprintDigits (hour(NestClose_t));
        Serial.print (":");
        SerialprintDigits (minute((NestClose_t))); 
        Serial.print (" ");
        Serial.print (day(NestClose_t));
        Serial.print ("/");
        Serial.print (month(NestClose_t));
        Serial.print (" ");
        Serial.print (year(NestClose_t));
        Serial.print (" time_t number:");
        Serial.println (NestClose_t);
      }}

  //  Status debug functions      
      /*
      //  Temperature
      void Display_temp_serial(){if (SerialDebugTimers)
      {
       Serial.print(sensors.getTempCByIndex(0));
       Serial.print(char(243));
       Serial.println("C");
      }}
 */
   
      //  Status of light
      void Display_light_status_serial() {if (SerialDebugStatus)
      {
        Serial.print ("Light status: ");
        Serial.println (LightStatus);
      }}     

      //  Status of door
      void Display_door_status_serial() {if (SerialDebugStatus)
      {
        Serial.print ("Door actual position: ");
        Serial.println (DoorActualPosition);
        
        Serial.print ("Door status: ");
        Serial.println (DoorStatus);
      }}
      
      //  Status of nest
      void Display_nest_status_serial() {if (SerialDebugStatus)
      {
        Serial.print ("Nest actual position: ");
        Serial.println (NestActualPosition);

        Serial.print ("Nest status: ");
        Serial.println (NestStatus);
      }}
      
  //  Utility function to add "0" if number is smaller than 10
      void SerialprintDigits(int digits)
      {
       if(digits < 10)
       Serial.print('0');
       Serial.print(digits);
      }
   

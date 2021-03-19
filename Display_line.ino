//PLACES CURSOR AND PRINTS LINES ON LCD - update of the menu is done in Display_menu

/* SPECIAL CHARACTERS (See function Setup_LC)
 LCD.print(char(1)); // writes "æ"
 LCD.print(char(2)); // writes "ø"
 LCD.write(3); // writes "å"
 LCD.write(4); // writes "Æ"
 LCD.write(5); // writes "Ø"
 LCD.write(6); // writes "Å"
 LCD.write(7); // writes Up pointer
 LCD.print(char(0)); // writes Down pointer
*/

  //  Menu lines
      void Display_item(int x)
      {
        switch (x)
        {
          //Menu 1 - START SCREEN
          case 11: Display_time();break;
          // Item12 is used for printing a message according to a function passed as a parameter to Dispaly_menu()
          
          //Menu 2 - CONTROLS MENU
          case 21: LCD.setCursor(0,Line);LCD.print("HANDLINGER      ");break;
          case 22: LCD.setCursor(0,Line);LCD.print(" Lys til        ");break;
          case 23: LCD.setCursor(0,Line);LCD.print(" Lys auto       ");break;
          case 24: LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.write(3);LCD.print("bn        ");break;
          case 25: LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.print("luk        ");break;
          case 26: LCD.setCursor(0,Line);LCD.print(" Rede ");LCD.write(3);LCD.print("bn        ");break;
          case 27: LCD.setCursor(0,Line);LCD.print(" Rede luk       ");break;
          case 28: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;

          //Menu 3 lines - TIMERS DISPLAY
          case 31: LCD.setCursor(0,Line);LCD.print("AKTUELLE TIMERE ");break;
          case 32: 
                   LCD.setCursor(0,Line);LCD.print(" Morgenlys:");
                   if (LightOnMorning_set == 2) {LCD.print("  Fra");break;}
                   if (LightOnMorning_set == 1) {LCDprintDigits(LightOnMorning_hour); LCD.print(":"); LCDprintDigits(LightOnMorning_minute); break;}
                   if (LightOnMorning_set == 0)
                   {
                    if (TimeWithElectricLight_seconds > 0) {LCDprintDigits(LightOnMorning_hour); LCD.print(":"); LCDprintDigits(LightOnMorning_minute); break;}
                    if (TimeWithElectricLight_seconds <= 0) {LCD.print("  Fra");break;} 
                   }
          case 33:
                   LCD.setCursor(0,Line);LCD.print(" Aftenlys: ");
                   if (LightOffEvening_set == 2) {LCD.print("  Fra");break;}
                   if (LightOffEvening_set == 1) {LCDprintDigits(LightOffEvening_hour); LCD.print(":"); LCDprintDigits(LightOffEvening_minute); break;}
                   if (LightOffEvening_set == 0)
                   {
                    if (TimeWithElectricLight_seconds > 0) {LCDprintDigits(LightOffEvening_hour); LCD.print(":"); LCDprintDigits(LightOffEvening_minute); break;}
                    if (TimeWithElectricLight_seconds <= 0) {LCD.print("  Fra");break;} 
                   }
          case 34: LCD.setCursor(0,Line);LCD.print(" ");Display_door_status(1); break;
          case 35: LCD.setCursor(0,Line);LCD.print(" ");Display_door_status(4);break;
          case 36: LCD.setCursor(0,Line);LCD.print(" ");Display_nest_status(1);break;
          case 37: LCD.setCursor(0,Line);LCD.print(" ");Display_nest_status(4);break;
          case 38: LCD.setCursor(0,Line);LCD.print(" Solopg.:  "); LCDprintDigits(hour(TodaysSunRise_t)); LCD.print(":"); LCDprintDigits(minute(TodaysSunRise_t));break;
          case 39: LCD.setCursor(0,Line);LCD.print(" Solnedg.: "); LCDprintDigits(hour(TodaysSunSet_t)); LCD.print(":"); LCDprintDigits(minute(TodaysSunSet_t));break;
          case 40: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;

          //Menu 4 lines - MORNING LIGHT MENU
          case 41: LCD.setCursor(0,Line);LCD.print("INDST. MORGENLYS");break;
          case 42: LCD.setCursor(0,Line);LCD.print(" T");LCD.print(char(1));LCD.print("nd mode:");Display_mode_status(LightOnMorning_set);break;
          case 43: LCD.setCursor(0,Line);LCD.print(" S");LCD.print("luk mode:");Display_mode_status(LightOffMorning_set);break;
          case 44: LCD.setCursor(0,Line);LCD.print(" Tid lys:  ");LCDprintDigits(TimeWithLight_hour);LCD.print(":");LCDprintDigits(TimeWithLight_minute);break;
          case 45: LCD.setCursor(0,Line);LCD.print(" Lys t"); LCD.print(char(1)); LCD.print("nd: "); LCDprintDigits(LightOnMorning_hour); LCD.print(":"); LCDprintDigits(LightOnMorning_minute); break;
          case 46: LCD.setCursor(0,Line);LCD.print(" Lys sluk: "); LCDprintDigits(LightOffMorning_hour); LCD.print(":"); LCDprintDigits(LightOffMorning_minute); break;
          case 47: LCD.setCursor(0,Line);LCD.print(" Solopg.-:   "); LCD.print(":"); LCDprintDigits(LightOffDelayAfterSunRise_minute); break;
          case 48: LCD.setCursor(0,Line);LCD.print(" V");LCD.write(3);LCD.print("gelys+:   "); LCD.print(":"); LCDprintDigits(LightDimmerOnPrecedeLight_minute); break;
          case 49: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;

          //Menu 5 lines - EVENING LIGHT MENU
          case 51: LCD.setCursor(0,Line);LCD.print("INDST. AFTENLYS ");break;
          case 52: LCD.setCursor(0,Line);LCD.print(" T");LCD.print(char(1));LCD.print("nd mode:");Display_mode_status(LightOnEvening_set);break;
          case 53: LCD.setCursor(0,Line);LCD.print(" S");LCD.print("luk mode:");Display_mode_status(LightOffEvening_set);break;
          case 54: LCD.setCursor(0,Line);LCD.print(" Tid lys:  ");LCDprintDigits(TimeWithLight_hour);LCD.print(":");LCDprintDigits(TimeWithLight_minute);break;
          case 55: LCD.setCursor(0,Line);LCD.print(" Lys t"); LCD.print(char(1)); LCD.print("nd: "); LCDprintDigits(LightOnEvening_hour); LCD.print(":"); LCDprintDigits(LightOnEvening_minute); break;
          case 56: LCD.setCursor(0,Line);LCD.print(" Lys sluk: "); LCDprintDigits(LightOffEvening_hour); LCD.print(":"); LCDprintDigits(LightOffEvening_minute); break;
          case 57: LCD.setCursor(0,Line);LCD.print(" Solnedg.+:  "); LCD.print(":"); LCDprintDigits(LightOnPrecedeSunSet_minute); break;
          case 58: LCD.setCursor(0,Line);LCD.print(" V");LCD.write(3);LCD.print("gelys+:   "); LCD.print(":"); LCDprintDigits(LightDimmerOffDelayAfterLight_minute); break;
          case 59: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;
          
          //Menu 6 lines - DOOR MENU
          case 61: LCD.setCursor(0,Line);LCD.print("INDSTIL D");LCD.write(5);LCD.print("R     ");break;
          case 62: LCD.setCursor(0,Line);LCD.print(" ");LCD.write(6);LCD.print("bn mode: ");Display_mode_status(DoorOpen_set);break;
          case 63: LCD.setCursor(0,Line);LCD.print(" Luk mode: ");Display_mode_status(DoorClose_set);break;
          case 64: LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.write(3);LCD.print("bn:  "); LCDprintDigits(DoorOpen_hour); LCD.print(":"); LCDprintDigits(DoorOpen_minute); break;
          case 65: LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.print("luk:  "); LCDprintDigits(DoorClose_hour); LCD.print(":"); LCDprintDigits(DoorClose_minute); break;
          case 66: LCD.setCursor(0,Line);LCD.print(" Solopg.-:   "); LCD.print(":"); LCDprintDigits(DoorOpenPrecedeSunRise_minute); break;
          case 67: LCD.setCursor(0,Line);LCD.print(" Tusm");LCD.write(5);LCD.print("rke+:  "); LCD.print(":"); LCDprintDigits(DoorCloseDelayAfterCivilTwilight_minute); break;
          case 68: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;

          //Menu 7 lines - NEST MENU
          case 71: LCD.setCursor(0,Line);LCD.print("INDSTIL REDE    ");break;
          case 72: LCD.setCursor(0,Line);LCD.print(" ");LCD.write(6);LCD.print("bn mode: ");Display_mode_status(NestOpen_set);break;
          case 73: LCD.setCursor(0,Line);LCD.print(" Luk mode: ");Display_mode_status(NestClose_set);break;
          case 74: LCD.setCursor(0,Line);LCD.print(" Rede ");LCD.write(3);LCD.print("bn: "); LCDprintDigits(NestOpen_hour); LCD.print(":"); LCDprintDigits(NestOpen_minute); break;
          case 75: LCD.setCursor(0,Line);LCD.print(" Rede ");;LCD.print("luk: "); LCDprintDigits(NestClose_hour); LCD.print(":"); LCDprintDigits(NestClose_minute); break;
          case 76: LCD.setCursor(0,Line);LCD.print(" Tusm");LCD.write(5);LCD.print("rke-:  "); LCD.print(":"); LCDprintDigits(NestOpenPrecedeCivilTwilight_minute); break;
          case 77: LCD.setCursor(0,Line);LCD.print(" Solnedg.-:  "); LCD.print(":"); LCDprintDigits(NestClosePrecedeSunSet_minute); break;
          case 78: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;

          //Menu 8 lines - TIME MENU
          case 81: LCD.setCursor(0,Line);LCD.print("INDSTIL TID     ");break;
          case 82: LCD.setCursor(0,Line);LCD.print(" Time:       ");LCDprintDigits(Time_hour);LCD.print(":");break;
          case 83: LCD.setCursor(0,Line);LCD.print(" Minut:      ");LCD.print(":");LCDprintDigits(Time_minute);break;
          case 84: LCD.setCursor(0,Line);LCD.print(" Dag:         ");LCDprintDigits(Time_day);break;
          case 85: LCD.setCursor(0,Line);LCD.print(" M");LCD.write(3);LCD.print("ned:       ");LCDprintDigits(Time_month);break;
          case 86: LCD.setCursor(0,Line);LCD.print(" ");LCD.write(6);LCD.print("r:        ");LCD.print(Time_year);break;
          case 87: LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");break;
        }
      }
 
  //  Generic texts (use in different menues)
      
      // Display "*" or ">" in col 0
      void Display_cur()
      {
       LCD.setCursor(0,Line);
       if (CurSelect == 1) {LCD.print (">");}
       else {LCD.print ("*");}
      }

      // Empty old cursor " " in col 0
      void Display_curdel()
      {
       LCD.setCursor(0,Line);
       LCD.print (" ");
      }
      
      //Empty line
      void Display_empty()
      {
        LCD.setCursor(0,Line);
        LCD.print("                ");
      }
      
      //Date and time
      void Display_time()
      { 
        LCD.setCursor(0,Line);
        LCDprintDigits(day());
        LCD.print("/");
        LCDprintDigits(month());
        LCD.print("/");
        LCDprintDigits(year());
        LCD.print(" ");
        LCDprintDigits(hour());
        LCD.print(":");
        LCDprintDigits(minute());
        Display_Display_time_serial();
      }

      //Update time only
      void Display_update_time()
      {
        LCD.setCursor(11,Line);
        LCDprintDigits(hour());
        LCD.print(":");
        LCDprintDigits(minute());
       }
      
      //Error message
      void Display_ERROR()
      {
       LCD.print("Fejl!");  
      }
  
      //Update message
      void Display_update(int Delay)
      {
        LCD.setCursor(0,Line);
        LCD.print("Opdaterer");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        Reset_watchdog_timer();
        Display_Display_update_serial();
        Display_empty();
       }        

      //Save message
      void Display_save(int Delay)
      {
        LCD.setCursor(1,Line);
        LCD.print("               ");
        LCD.setCursor(1,Line);
        LCD.print("Gemmer");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        LCD.print(".");
        delay(Delay);
        Reset_watchdog_timer();
        Display_empty();
       }  
   
   // UTILITY FIÙNCTIONS
   
      //Display "..."
      void Display_processing()
      {
       delay(SensitivityKeypad);
       LCD.print(".");
       Reset_watchdog_timer();
       delay(SensitivityKeypad);
       Input_keypad();
       LCD.print(".");
       Reset_watchdog_timer();
       delay(SensitivityKeypad);
       Input_keypad();
       LCD.print(".");
       delay(SensitivityKeypad);
       Input_keypad();
       Reset_watchdog_timer();
      }

      //Utility function to add "0" if number is smaller than 10
      void LCDprintDigits(int digits)
      {
       if(digits < 10) {LCD.print("0");}
       LCD.print(digits);
      }
  

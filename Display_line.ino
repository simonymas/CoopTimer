//PRINTS LINES ON LCD - update of the menu is done in Display_menu

/* SPECIAL CHARACTERS (See function Setup_LC)
 lcd.print(char(1)); // writes "æ"
 lcd.print(char(2)); // writes "ø"
 lcd.write(3); // writes "å"
 lcd.write(4); // writes "Æ"
 lcd.write(5); // writes "Ø"
 lcd.write(6); // writes "Å"
 lcd.write(7); // writes Up pointer
 lcd.print(char(0)); // writes Down pointer
*/

/* STRUCTURE OF THE MENU
   
   START SCREEN
   L1: Date + time
   L2: Motor status

   CONTROL MENU
   L1: "Manual controls"
   L2: Open door
   L3: Close door
   L4: Open nest
   L5: Close nest
   L6: Light on
   L7: Light off
   
*/

  //  Menu 1 lines
      void Display_item11() {Display_time();}
      // Item12 is used for printing a message according to a function passed as a parameter to Dispaly_menu()
  
  //  Menu 2 lines
      void Display_item21() {LCD.setCursor(0,Line);LCD.print("HANDLINGER      ");}
      void Display_item22() {LCD.setCursor(0,Line);LCD.print(" Lys til        ");}
      void Display_item23() {LCD.setCursor(0,Line);LCD.print(" Lys auto       ");}
      void Display_item24() {LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.write(3);LCD.print("bn        ");}
      void Display_item25() {LCD.setCursor(0,Line);LCD.print(" D");LCD.print(char(2));LCD.print("r ");LCD.print("luk        ");}
      void Display_item26() {LCD.setCursor(0,Line);LCD.print(" Rede ");LCD.write(3);LCD.print("bn        ");}
      void Display_item27() {LCD.setCursor(0,Line);LCD.print(" Rede luk       ");}
      void Display_item28() {LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");}

  //  Menu 3 lines
      void Display_item31() {LCD.setCursor(0,Line);LCD.print("TIMERE          ");}
      void Display_item32() {LCD.setCursor(0,Line);LCD.print(" ");Display_light_status(1);}
      void Display_item33() {LCD.setCursor(0,Line);LCD.print(" ");Display_light_status(2);}
      void Display_item34() {LCD.setCursor(0,Line);LCD.print(" ");Display_door_status(1);}
      void Display_item35() {LCD.setCursor(0,Line);LCD.print(" ");Display_door_status(4);}
      void Display_item36() {LCD.setCursor(0,Line);LCD.print(" ");Display_nest_status(1);}
      void Display_item37() {LCD.setCursor(0,Line);LCD.print(" ");Display_nest_status(4);}
      void Display_item38() {LCD.setCursor(0,Line);LCD.print(" EXIT MENU      ");}
  
  //  Generic lines (use in different menues)
      
      // Display "*" in col 0
      void Display_cur()
      {
       LCD.setCursor(0,Line);
       LCD.print ("*");
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
        LCD.print(".");
        delay(Delay);
        Reset_watchdog_timer();
        Display_Display_update_serial();
        Display_empty();
      }        
      
      //Temperature
      /*
      void Display_temp()
      {
       {
        LCD.setCursor(6,Line);
        LCD.print(sensors.getTempCByIndex(0));
        LCD.print(char(223));
        LCD.print("C");
       }
      }
      */   

  //  Light status - line 1 - values LightStatus: 0 = No light nedded; 1 = Morning light has not been turned on yet, 2 = Morning light is turned on, 3 = Morning light has been turned off, 4 = Evening light is turned on);   
      void Display_light_status(int x)
      {
        switch (x)
        { //Space as last character to fit cursor in menues
          case 0: LCD.print("Ikke lysbehov   "); break;
          case 1: LCD.print("Lys t"); LCD.print(char(1)); LCD.print("nd: "); LCDprintDigits(hour(LightOnMorning_t)); LCD.print(":"); LCDprintDigits(minute(LightOnMorning_t)); break;          
          case 2: LCD.print("Lys sluk: "); LCDprintDigits(hour(LightOffMorning_t)); LCD.print(":"); LCDprintDigits(minute(LightOffMorning_t)); LCD.print(" ");break; //Space as last character to fit cursor in menues
          case 3: LCD.print("Lys t"); LCD.print(char(1)); LCD.print("nd: "); LCDprintDigits(hour(LightOnEvening_t)); LCD.print(":"); LCDprintDigits(minute(LightOnEvening_t));LCD.print(" "); break; //Space as last character to fit cursor in menues
          case 4: LCD.print("Lys sluk:  "); LCDprintDigits(hour(LightOffEvening_t)); LCD.print(":"); LCDprintDigits(minute(LightOffEvening_t)); break;
          case 5: LCD.print(" T"); LCD.print(char(1)); LCD.print("nd lys manuel"); break;
          case 6: LCD.print("Sluk lys manuelt"); break;
          case 7: LCD.print("Lys t"); LCD.print(char(1)); LCD.print("ndt!      ");
                  delay(SensitivityKeypad);
                  Input_keypad();
                  delay(SensitivityKeypad);
                  Input_keypad();
                  Reset_watchdog_timer();
                  delay(SensitivityKeypad);
                  Input_keypad();
                  break;
          case 8: LCD.print(" Automatisk lys ");
                  delay(SensitivityKeypad);
                  Input_keypad();
                  delay(SensitivityKeypad);
                  Input_keypad();
                  Reset_watchdog_timer();
                  delay(SensitivityKeypad);
                  Input_keypad();
                  break;
        }
       }

  //  Door status - line 1
      void Display_door_status(int x)
      {
        switch (x)
        {
          case 0: break;
          case 1: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r "); LCD.print(char(3)); LCD.print ("bn:  "); LCDprintDigits(hour(DoorOpen_t)); LCD.print(":");LCDprintDigits(minute(DoorOpen_t));LCD.print(" "); //Space as last character to fit cursor in menues
               break;
          case 2: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r "); LCD.print(char(3)); LCD.print("bner");
               Display_processing();
               break;    
          case 3:
               LCD.print ("D"); LCD.print(char(2)); LCD.print("r lukker");
               Display_processing();
               break;
          case 4: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r ");LCD.print ("luk:  "); LCDprintDigits(hour(DoorClose_t)); LCD.print(":");LCDprintDigits(minute(DoorClose_t));LCD.print(" "); //Space as last character to fit cursor in menues
               break;
          case 5: LCD.setCursor(0,Line);LCD.print(char(6)); LCD.print("ben d"); LCD.print(char(2)); LCD.print("r manuelt"); break;
          case 6: LCD.setCursor(0,Line);LCD.print("Luk d"); LCD.print(char(2)); LCD.print("r manuelt"); break;
          case 7: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r "); LCD.print(char(3)); LCD.print("bner");
               Display_processing();
               break;
          case 8:
               LCD.print ("D"); LCD.print(char(2)); LCD.print("r lukker");
               Display_processing();
               break;
        }
       }

  //  Nest status - line 1
      void Display_nest_status(int x)
      {
        switch (x)
        {
          case 0: break;
          case 1: LCD.print("Rede "); LCD.write(3); LCD.print ("bn: "); LCDprintDigits(hour(NestOpen_t)); LCD.print(":");LCDprintDigits(minute(NestOpen_t));LCD.print(" "); break; //Space as last character to fit cursor in menues
          case 2: 
              LCD.print("Rede "); LCD.print(char(3)); LCD.print("bner");
              Display_processing();
            break;
          case 3:
              LCD.print("Rede lukker");
              Display_processing();
            break;
          case 4: LCD.print("Rede luk: "); LCDprintDigits(hour(NestClose_t)); LCD.print(":");LCDprintDigits(minute(NestClose_t)); LCD.print(" ");break; //Space as last character to fit cursor in menues
          case 5: LCD.print(char(6)); LCD.print("bn rede manuelt"); break;
          case 6: LCD.print("Luk rede manuelt"); break;
          case 7: 
              LCD.print("Rede "); LCD.print(char(3)); LCD.print("bner");
              Display_processing();
          case 8:
              LCD.print("Rede lukker");
              Display_processing();
        }
       }  
   
   // Display "..."
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

  //  Utility function to add "0" if number is smaller than 10
      void LCDprintDigits(int digits)
      {
       if(digits < 10)
       LCD.print('0');
       LCD.print(digits);
      }
  

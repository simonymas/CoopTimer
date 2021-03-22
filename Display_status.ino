//PRINTS SPECIFIC TEXTS ON LCD from a position specified in Display_lines
  
  //  Mode status - values: 1 = Timer, 0 = Automatic, 2 = Disabled - manual mode
      void Display_mode_status(byte x)
      {
        switch (x)
        { 
          case 0: LCD.print(" AUTO"); break;
          case 1: LCD.print("TIMER"); break;          
          case 2: LCD.print("  FRA");break;
        }
      }
      
  //  Light status - values LightStatus: 0 = No light nedded; 1 = Morning light has not been turned on yet, 2 = Morning light is turned on, 3 = Morning light has been turned off, 4 = Evening light is turned on);   
      void Display_light_status(int x)
      {
        switch (x)
        { //Space as last character to fit cursor in menues
          case 0: LCD.print("Ikke lysbehov   "); break;
          case 1: LCD.print("Lys t"); LCD.print(char(1)); LCD.print("nd  "); LCDprintDigits(hour(LightOnMorning_t)); LCD.print(":"); LCDprintDigits(minute(LightOnMorning_t)); break;          
          case 2: LCD.print("Lys sluk  "); LCDprintDigits(hour(LightOffMorning_t)); LCD.print(":"); LCDprintDigits(minute(LightOffMorning_t)); LCD.print(" ");break; //Space as last character to fit cursor in menues
          case 3: LCD.print("Lys t"); LCD.print(char(1)); LCD.print("nd  "); LCDprintDigits(hour(LightOnEvening_t)); LCD.print(":"); LCDprintDigits(minute(LightOnEvening_t));LCD.print(" "); break; //Space as last character to fit cursor in menues
          case 4: LCD.print("Lys sluk   "); LCDprintDigits(hour(LightOffEvening_t)); LCD.print(":"); LCDprintDigits(minute(LightOffEvening_t)); break;
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
          case 8: break;
        }
       }

  //  Door status 
      void Display_door_status(int x)
      {
        switch (x)
        {
          case 0: break;
          case 1: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r "); LCD.print(char(3)); LCD.print ("bn   "); LCDprintDigits(hour(DoorOpen_t)); LCD.print(":");LCDprintDigits(minute(DoorOpen_t));LCD.print(" "); //Space as last character to fit cursor in menues
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
               LCD.print("D"); LCD.print(char(2)); LCD.print("r ");LCD.print ("luk   "); LCDprintDigits(hour(DoorClose_t)); LCD.print(":");LCDprintDigits(minute(DoorClose_t));LCD.print(" "); //Space as last character to fit cursor in menues
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

  //  Nest status 
      void Display_nest_status(int x)
      {
        switch (x)
        {
          case 0: break;
          case 1: LCD.print("Rede "); LCD.write(3); LCD.print ("bn  "); LCDprintDigits(hour(NestOpen_t)); LCD.print(":");LCDprintDigits(minute(NestOpen_t));LCD.print(" "); break; //Space as last character to fit cursor in menues
          case 2: 
              LCD.print("Rede "); LCD.print(char(3)); LCD.print("bner");
              Display_processing();
            break;
          case 3:
              LCD.print("Rede lukker");
              Display_processing();
            break;
          case 4: LCD.print("Rede luk  "); LCDprintDigits(hour(NestClose_t)); LCD.print(":");LCDprintDigits(minute(NestClose_t)); LCD.print(" ");break; //Space as last character to fit cursor in menues
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

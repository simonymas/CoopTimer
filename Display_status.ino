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
          case 0: break;
          case 1: break;          
          case 2: break;
          case 3: break;
          case 4: break;
          case 5: break;
          case 6: break;
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
          case 1: break;
          case 2: 
               LCD.print("D"); LCD.print(char(2)); LCD.print("r "); LCD.print(char(3)); LCD.print("bner");
               Display_processing();
               break;    
          case 3:
               LCD.print ("D"); LCD.print(char(2)); LCD.print("r lukker");
               Display_processing();
               break;
          case 4:               
               break;
          case 5: break;
          case 6: break;
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
          case 1: break;
          case 2: 
               LCD.print("Rede "); LCD.print(char(3)); LCD.print("bner");
               Display_processing();
               break;
          case 3:
               LCD.print("Rede lukker");
               Display_processing();
               break;
          case 4: break;
          case 5: break;
          case 6: break;
          case 7: 
               LCD.print("Rede "); LCD.print(char(3)); LCD.print("bner");
               Display_processing();
          case 8:
               LCD.print("Rede lukker");
               Display_processing();
        }
       }  

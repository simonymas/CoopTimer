//Updates menu position and determines, what lines to print where (printing of the lines on the LCD is done in Display_line - navigation with keys Input_keypad)

  //  Determine which menu to show
      byte Active_menu()
       {
        if (Pos < 20) return 1;
        if (Pos < 30) return 2;
        if (Pos < 40) return 3;
        return 1;
       }     
      
  //  Update menu (except for line 2 in menu 1 which is used for ad hoc notices - see function Display_notice_menu below)
      void Display_menu()
      {     
       if (Active_menu () > 1)
       {
        if (PosLast < 20)
        {Setup_menu_reset();}                     //When menu 2, 3 etc is first shown, timer is set
       }
       Reset_menu();                              //Check to se if it is time to reset to menu 1 
       
       if (Active_menu() == 1)                    //MENU 1 - line 1
       {
        if (Pos != PosLast)
        {
         Line = 0;
         Display_item11();  
         Display_Display_menu11_serial();
         PosLast = Pos;
         Line = 1;
         Display_empty();
        }
        else
        {
         Line = 0;
         Display_update_time();
        }         
       }
       
       if (Active_menu() > 1)                    
       {
         if (Pos != PosLast)
         {
         Line = 0;
         switch (Pos)        
         {
          case 21: Display_item21();              //MENU 2
                   Line = 1;
                   Display_item22();
                   break;
          case 22: Display_item22();
                   Line = 1;
                   Display_item23();
                   break;
          case 23: Display_item23();
                   Line = 1;
                   Display_item24();
                   break;
          case 24: Display_item24();
                   Line = 1;
                   Display_item25();
                   break;
          case 25: Display_item25();
                   Line = 1;
                   Display_item26();
                   break;
          case 26: Display_item26();
                   Line = 1;
                   Display_item27();
                   break;
          case 27: Display_item27();
                   Line = 1;
                   Display_item28();
                   break;
          
          case 31: Display_item31();            //MENU 3
                   Line = 1;
                   Display_item32();
                   break;
          case 32: Display_item32();
                   Line = 1;
                   Display_item33();
                   break;
          case 33: Display_item33();
                   Line = 1;
                   Display_item34();
                   break;
          case 34: Display_item34();
                   Line = 1;
                   Display_item35();
                   break;
          case 35: Display_item35();
                   Line = 1;
                   Display_item36();
                   break;
          case 36: Display_item36();
                   Line = 1;
                   Display_item37();
                   break;
          case 37: Display_item37();
                   Line = 1;
                   Display_item38();
                   break;
         }
        }
        switch (Cur)
        {
         case 0: Line = 0;
                 Display_cur();
                 break;
         case 1: Line = 1;
                 Display_cur();
                 break;
         case 2: break;
         }
        
        switch (CurDel)
         {
         case 0: Line = 0;
                 Display_curdel();
                 CurDel = 2;
         case 1: Line = 1;
                 Display_curdel();
                 CurDel = 2;
         }
        
         PosLast = Pos;
         Display_Display_menu2_serial();     
       }
   
       Reset_watchdog_timer();
       Input_keypad();
      }

  //  Update menu 1, line 2 - Pass the function that is to be printed in line 2 as a parameter to the Display_menu() function, ex. "Display_notice_menu(Display_door_status(DoorStatus));"
      void Display_notice_menu(void (*PassedFunction)(int),int PassedArg)
      {
       if (Active_menu() == 1)                    //MENU 1 - line 2
       {
        Display_Display_menu12_serial();
        LCD.setCursor(0,1);
        Line = 1;
        (*PassedFunction)(PassedArg);
        Line = 1;
        Display_empty();
       }
      }

  //  Reset to menu 1
      void Reset_menu()
      {
       if (MenuReset_t < now()) {Pos = 11;}
      }

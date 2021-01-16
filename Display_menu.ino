//Updates menu position and determines, what lines to print where (printing of the lines on the LCD is done in Display_line - navigation with keys Input_keypad)

  //  Determine which menu to show
      byte Active_menu()
       {
        return ((Pos-Pos%10)/10);
       }     
      
  //  Update menu (except for line 2 in menu 1 which is used for ad hoc notices - see function Display_notice_menu below)
      void Display_menu()
      {     
       if (Active_menu() > 1)
       {
        if (PosLast < 20) {Setup_menu_reset();}   //When navigating to menu 2, 3, timer is set
       }
       Reset_menu();                              //Check to se if it is time to reset to menu 1 
     
       if (Active_menu() == 1)                    //MENU 1 l ine 1
       {
        if (Pos != PosLast)
        {
         Line = 0;
         Display_item(11);  
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
   
       if (Active_menu() > 1)                   //OTHER MENUES          
       {
        if (Pos != PosLast)
        {
         Line = 0;
         Display_item(Pos);
         Line = 1;
         Display_item(Pos+1);
        }
        switch (Cur)
        {
         case 0: Line = 0; Display_cur(); break;
         case 1: Line = 1; Display_cur(); break;
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
         Display_Display_menu_serial();     
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
       if (MenuReset_t < now()) {Pos = 11;Cur = 2; CurSelect = 0;}
      }

//SETS STATUS OF SENSOR BUTTONS

/*
MENU STRUCTURE

Variable "Pos" is comprised of menunumber (1st integer) and line number shown i line 0 of the display (2nd integer).
Variable "Cur" has the values 0 = line 0, 1 = line 1, 2 = not shown

Menu     1 - Start menu                     2 - Control menu              
Line
1        11 [date] + [time]                 21 HANDLINGER       
2        12 [light/door/nest staus]         22  Tænd lys      
3                                           23  Auto lys        
4                                           24  Åbn dør         
5                                           25  Luk dør         
6                                           26  Åbn rede        
7                                           27  Luk rede        
8                                           28  EXIT MENU      
 */
 
  // Define number of menues

     #define MenuMax     6
  
  // Define number of lines in each menu
      
     #define Lines_menu1 2
     #define Lines_menu2 8    
     #define Lines_menu3 8
     #define Lines_menu4 7
     #define Lines_menu5 6
     #define Lines_menu6 6
      
     byte Linemax_menu()
     {
       switch (Active_menu())
       {
         case 1: return Lines_menu1;
         case 2: return Lines_menu2;
         case 3: return Lines_menu3;
         case 4: return Lines_menu4;
         case 5: return Lines_menu5;
         case 6: return Lines_menu6;
         return 8;
       }
     }
        
  //  Update position from keypad input
      void Input_keypad()
      {
       delay(SensitivityKeypad);
       KeyValue = analogRead(0); // Read the value from the keypad shield
       if (KeyValue < 800) 
       {
        if (CurSelect == 1){Pos = Input_value_keypad();}
        else {Pos = Input_navigate_keypad();}
        Display_Input_keypad_serial();
        Display_menu();
        if (DoorStatus > 6) Initiate_door_event();
        if (NestStatus > 6) Initiate_nest_event();
        if (LightStatus > 6) Initiate_light_event();
       }
       if (Active_menu() > 1) {Display_menu();}
      }
        
  //  Get input from keypad 

      #define RIGHT  0
      #define UP     1
      #define DOWN   2
      #define LEFT   3
      #define SELECT 4
      #define NONE   5 
   
      int Input_read_keypad()
      {
        if (KeyValue > 1000) return NONE;
        if (KeyValue < 10)   return RIGHT;  
        if (KeyValue < 130)  return UP; 
        if (KeyValue < 280)  return DOWN; 
        if (KeyValue < 450)  return LEFT; 
        if (KeyValue < 690)  return SELECT;   
        return NONE;// when all others fail, return this...
      }  

  //  Navigate - update position and cursor - returns updated Pos variable
      int Input_navigate_keypad()
      {
       KeyStatus = Input_read_keypad();
       byte LineMax = Linemax_menu();
       switch (KeyStatus)            
       {
        case RIGHT:
         Cur = 2;
         if (Pos > (MenuMax*10)) {return 11;}
         return (Pos-Pos%10+11);
         break;
               
        case LEFT:
         Cur = 2;
         if (Pos < 20) {return (MenuMax*10+1);}
         return (Pos-Pos%10-9);
         break;
   
        case UP:
         if (Pos < 20) {return 11;}
         if (Pos%10 == 1) {Cur = 2; CurDel = 1; return Pos;}
         if (Pos%10 == 2) {if (Cur = 1) return --Pos;}
         if (Cur == 1) {Cur = 0; CurDel = 1; return Pos;}
         if (Cur == 0) {return --Pos;}
         break;
        
        case DOWN:
          if (Pos < 20) {return 11;}
          if (Pos%10 == (LineMax-1)) {Cur = 1; CurDel = 0; return Pos;}
          if (Cur == 1) {return ++Pos;}
          if (Pos%10 == 1) {Cur = 1; CurDel = 2; return Pos;}
          if (Cur == 2) {Cur = 1; return Pos;}
          if (Cur == 0) {Cur = 1;CurDel = 0;return Pos;}
          return 11;
          break;
        
        case SELECT:
           if (Pos < 20) {return 11;}                          //ACTIONS MENU
           if (Pos%10 == 1)                                    //ACTIONS first and last menu items
           {if (Cur == 2) {return Pos;}}                                    //First menu item always a header with no action
           if (Pos%10 == (LineMax-1)) {return 11;}                          //Last menu item always exits to start screen
           if (Cur == 1) {++Pos;}                              
           if (Active_menu()>3)                                //ACTIONS MENU 4+
           {
            switch(CurSelect)
            {
             case 0: CurSelect = 1;break;
             case 1: CurSelect = 0;break;
            } 
           }
             if (Active_menu() == 2)                              //ACTIONS MENU 2
             {
              switch (Pos)
              {            
               case 22: LightStatus = 7; return 11; break;
               case 23: LightStatus = 8; return 11; break;
               case 24: DoorStatus = 7; return 11; break;
               case 25: DoorStatus = 8; return 11; break;
               case 26: NestStatus = 7; return 11; break;
               case 27: NestStatus = 8; return 11; break;         
              }
            if (Active_menu() == 3) return Pos;                 //ACTION MENU 3
           }
           if (Cur == 1) {--Pos;}
           default: return Pos;
        }
      }

 //  Adjust values
     int Input_value_keypad()
     {
      KeyStatus = Input_read_keypad();
      Setup_menu_reset();
      ++PosLast;
      switch (KeyStatus)
      {
       case RIGHT: break;
       case LEFT: break;
       case UP: Adjust_value_keypad(1); break;
       case DOWN: Adjust_value_keypad(-1);break;
       case SELECT:
       {
        CurSelect = 0;
        if (ValueChanged == 1)
        {
         Eeprom_status = 2;
         Setup_eeprom();
         Setup_light_timer();
         Setup_door_timer();
         Setup_nest_timer();
         Line = Cur;
         Display_save(500);
         ValueChanged = 0;
        }
         break;
       }
      }
      return Pos;
     }

     void Adjust_value_keypad(int x)
     {
      ValueChanged = 1;
      if (Cur == 1) {++Pos;}
      switch (Pos)
      {       
       //LIGHT MENU       
       case 42:  LightOnMorning_set = Adjust_mode(LightOnMorning_set, x); break;
       case 43:  LightOffMorning_set = Adjust_mode(LightOffMorning_set, x); break;
       case 44:                      
                 TimeWithLight_hour = hour(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x));
                 TimeWithLight_minute = minute(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x));
                 break;  
       case 45:         
                 LightOnMorning_hour = hour(Adjust_time(LightOnMorning_hour, LightOnMorning_minute, x));
                 LightOnMorning_minute = minute(Adjust_time(LightOnMorning_hour, LightOnMorning_minute, x));    
                 break;
       case 46: 
                 LightOffMorning_hour = hour(Adjust_time(LightOffMorning_hour, LightOffMorning_minute, x));
                 LightOffMorning_minute = minute(Adjust_time(LightOffMorning_hour, LightOffMorning_minute, x));
                 break;

        //DOOR MENU
       case 52:  DoorOpen_set = Adjust_mode(DoorOpen_set, x); break;
       case 53:  DoorClose_set = Adjust_mode(DoorClose_set, x); break;
       case 54:         
                 DoorOpen_hour = hour(Adjust_time(DoorOpen_hour, DoorOpen_minute, x));
                 DoorOpen_minute = minute(Adjust_time(DoorOpen_hour, DoorOpen_minute, x));    
                 break;
       case 55: 
                 DoorClose_hour = hour(Adjust_time(DoorClose_hour, DoorClose_minute, x));
                 DoorClose_minute = minute(Adjust_time(DoorClose_hour, DoorClose_minute, x));
                 break;

        //NEST MENU
       case 62:  NestOpen_set = Adjust_mode(NestOpen_set, x); break;
       case 63:  NestClose_set = Adjust_mode(NestClose_set, x); break;
       case 64:         
                 NestOpen_hour = hour(Adjust_time(NestOpen_hour, NestOpen_minute, x));
                 NestOpen_minute = minute(Adjust_time(NestOpen_hour, NestOpen_minute, x));    
                 break;
       case 65: 
                 NestClose_hour = hour(Adjust_time(NestClose_hour, NestClose_minute, x));
                 NestClose_minute = minute(Adjust_time(NestClose_hour, NestClose_minute, x));
                 break;
      }
      if (Cur == 1) {--Pos;}
     }

//  Utility function: Calculate time_t for specific time (hour and minutes)
    time_t Adjust_time(byte Hour, byte Minute, int AddedValue)
    {
     time_t AdjustedHourMinute_t;
     TimeElements tm;
     tm.Hour = Hour;
     tm.Minute = Minute;
     tm.Second = 0;
     tm.Day = 1;
     tm.Month = 1;
     tm.Year = 2020-1970;
     AdjustedHourMinute_t = makeTime(tm) + AddedValue*60*10;
     return AdjustedHourMinute_t;
    }

//  Utility function to adjust mode
    byte Adjust_mode(byte ModeLast, int AddedValue)
    {
     int ModeNew;
     ModeNew = ModeLast + AddedValue;
     if (ModeNew > 2) {ModeNew = 0;}
     if (ModeNew < 0) {ModeNew = 2;}
     return ModeNew;
    }

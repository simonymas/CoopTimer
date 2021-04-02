//CALCULATES INPUTS FROM KEYPAD
        
  //  Calculate number of lines in the present menu      
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
        case 7: return Lines_menu7;
        case 8: return Lines_menu8;
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
        Setup_menu_reset();    //When a key is pressed, set timer anew to postpone reset to menu 1
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
       #define MenuMax     8  //Defines number of menues
       
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
         if (Pos%10 == 2 && Cur == 0) {Cur = 1; return --Pos;}
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
         if (Active_menu() == 8){Setup_arduino_from_menu_time();} //Set number of time menu here
         else
         {
          Eeprom_status = 2;
          Setup_eeprom();
          Setup_timer();
         }
         Line = Cur;
         Display_save(200);
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
       //MORNING LIGHT MENU       
       case 42:  LightOnMorning_set = Adjust_mode(LightOnMorning_set, x); break;
       
       case 43:  if (LightOnMorning_set == 0)
                 {
                  TimeWithLight_hour = hour(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x*10));
                  TimeWithLight_minute = minute(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x*10));
                  break;
                 }
                 if (LightOnMorning_set == 1)
                 {
                  LightOnMorning_hour = hour(Adjust_time(LightOnMorning_hour, LightOnMorning_minute, x*10));
                  LightOnMorning_minute = minute(Adjust_time(LightOnMorning_hour, LightOnMorning_minute, x*10));    
                  break;
                 }
                 else break;
       
       case 44:  LightOffMorning_set = Adjust_mode(LightOffMorning_set, x); break;                            

       case 45:  if(LightOffMorning_set == 0)
                 {
                  LightOffDelayAfterSunRise_minute = Adjust_pos_value(LightOffDelayAfterSunRise_minute, x); break; 
                 }
                 if(LightOffMorning_set == 1)
                 {
                  LightOffMorning_hour = hour(Adjust_time(LightOffMorning_hour, LightOffMorning_minute, x*10));
                  LightOffMorning_minute = minute(Adjust_time(LightOffMorning_hour, LightOffMorning_minute, x*10));
                  break;
                 }
                 else break;
                 
       case 46:  LightDimmerOnPrecedeLight_minute = Adjust_pos_value(LightDimmerOnPrecedeLight_minute, x); break;

       //EVENING LIGHT MENU       
       case 52:  LightOnEvening_set = Adjust_mode(LightOnEvening_set, x); break;
       
       case 53:  if (LightOnEvening_set == 0)
                 {
                  TimeWithLight_hour = hour(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x*10));
                  TimeWithLight_minute = minute(Adjust_time(TimeWithLight_hour,TimeWithLight_minute, x*10));
                  break;  
                 }
                 if (LightOnEvening_set == 1)
                 {
                  LightOnEvening_hour = hour(Adjust_time(LightOnEvening_hour, LightOnEvening_minute, x*10));
                  LightOnEvening_minute = minute(Adjust_time(LightOnEvening_hour, LightOnEvening_minute, x*10));
                  break;
                 }
                 else break;
       
       case 54:  LightOffEvening_set = Adjust_mode(LightOffEvening_set, x); break;                    
       
       case 55:         
                 if (LightOffEvening_set == 0)
                 {
                  LightOnPrecedeSunSet_minute = Adjust_pos_value(LightOnPrecedeSunSet_minute, x); break;
                 }
                 if (LightOffEvening_set == 1)
                 {
                  LightOffEvening_hour = hour(Adjust_time(LightOffEvening_hour, LightOffEvening_minute, x*10));
                  LightOffEvening_minute = minute(Adjust_time(LightOffEvening_hour, LightOffEvening_minute, x*10));
                  break;
                 }
                 else break;    
       
       case 56:  LightDimmerOffDelayAfterLight_minute = Adjust_pos_value(LightDimmerOffDelayAfterLight_minute, x); break;

       //DOOR MENU
       case 62:  DoorOpen_set = Adjust_mode(DoorOpen_set, x); break;
       
       case 63:  if (DoorOpen_set == 0)
                 {
                  DoorOpenPrecedeSunRise_minute = Adjust_pos_value(DoorOpenPrecedeSunRise_minute,x);break;
                 }
                 if (DoorOpen_set == 1)
                 {
                  DoorOpen_hour = hour(Adjust_time(DoorOpen_hour, DoorOpen_minute, x*10));
                  DoorOpen_minute = minute(Adjust_time(DoorOpen_hour, DoorOpen_minute, x*10));    
                  break;
                 }
                 else break;
                 
       case 64:  DoorClose_set = Adjust_mode(DoorClose_set, x); break;       
                 
       case 65: if (DoorClose_set == 0)
                {
                 DoorCloseDelayAfterCivilTwilight_minute = Adjust_pos_value(DoorCloseDelayAfterCivilTwilight_minute,x);break;
                }
                if (DoorClose_set == 1)
                {
                 DoorClose_hour = hour(Adjust_time(DoorClose_hour, DoorClose_minute, x*10));
                 DoorClose_minute = minute(Adjust_time(DoorClose_hour, DoorClose_minute, x*10));
                 break;
                }
                else break;

       //NEST MENU
       case 72:  NestOpen_set = Adjust_mode(NestOpen_set, x); break;
       
       case 73:  if (NestOpen_set == 0)
                 {
                  NestOpenPrecedeCivilTwilight_minute = Adjust_pos_value(NestOpenPrecedeCivilTwilight_minute,x);break;
                 }
                 if (NestOpen_set == 1)
                 {
                  NestOpen_hour = hour(Adjust_time(NestOpen_hour, NestOpen_minute, x*10));
                  NestOpen_minute = minute(Adjust_time(NestOpen_hour, NestOpen_minute, x*10));    
                  break;
                 }
                 else break;
                 
       case 74:  NestClose_set = Adjust_mode(NestClose_set, x); break;       
                 
       case 75:  if (NestClose_set == 0)
                 {
                  NestClosePrecedeSunSet_minute = Adjust_pos_value(NestClosePrecedeSunSet_minute,x);break;
                 }
                 if (NestClose_set == 1)
                 {
                  NestClose_hour = hour(Adjust_time(NestClose_hour, NestClose_minute, x*10));
                  NestClose_minute = minute(Adjust_time(NestClose_hour, NestClose_minute, x*10));
                  break;
                 }
                 else break;       

       //Time MENU
       case 82:  Time_hour = hour(Adjust_time(Time_hour, minute(), x*60)); break;
       case 83:  Time_minute = minute(Adjust_time(hour(), Time_minute, x)); break;
       case 84:  Time_day = Adjust_day(x); break;
       case 85:  Time_month = Adjust_month(x); break;
       case 86:  Time_year = Time_year+x; break;
      }
      if (Cur == 1) {--Pos;}
     }

//  Utility function: Adjust time_t for specific time (hour and minutes)
    time_t Adjust_time(byte Hour, byte Minute, int AddedValue)
    {
     time_t AdjustedHourMinute_t;
     TimeElements tm;
     tm.Hour = Hour;
     tm.Minute = Minute;
     tm.Second = 30;
     tm.Day = Time_day;
     tm.Month = Time_month;
     tm.Year = Time_year-1970;
     AdjustedHourMinute_t = makeTime(tm) + AddedValue*60;
     return AdjustedHourMinute_t;
    }

//  Utility function: Adjust day
    byte Adjust_day(int AddedDay)
    {
     byte AdjustedDay;
     if(Time_day == 31 && AddedDay > 0) {AdjustedDay = 1;}
     else if(AddedDay < 0 && Time_day==1) {AdjustedDay = 31;}
     else {AdjustedDay = Time_day+AddedDay;}
     return AdjustedDay;
    }

//  Utility function: Adjust month
    byte Adjust_month(int AddedMonth)
    {
     if(AddedMonth > 0 && Time_month == 12) {Time_month = 1;}
     if(AddedMonth < 0 && Time_month == 1) {Time_month = 12;}
     else {Time_month = Time_month+AddedMonth;}
     return Time_month;
    }
    
//  Utility function: Adjust mode
    byte Adjust_mode(byte ModeLast, int AddedValue)
    {
     int ModeNew;
     ModeNew = ModeLast + AddedValue;
     if (ModeNew > 2) {ModeNew = 0;}
     if (ModeNew < 0) {ModeNew = 2;}
     return ModeNew;
    }

//  Utility function: Adjust number, only allowing positive values
    byte Adjust_pos_value(byte ValueLast, int AddedValue)
    {
     int ValueNew = ValueLast+AddedValue;
     if (ValueNew >= 0) {return ValueNew;}
     if (ValueNew < 0) {return ValueLast;}
    }

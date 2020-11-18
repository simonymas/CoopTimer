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
 
 //  Define some variables and values used by the keypad functions
      byte PosMax = 27; //First integer: Number of menues used in this version of the program, Second integer: Last line in last menu in this version of the program
      byte LineMax = 8;         //Maximum number of lines in menues  in this version of the program, except for menu 1 (in menu 1, max no. is always 2)   
    
      #define RIGHT  0
      #define UP     1
      #define DOWN   2
      #define LEFT   3
      #define SELECT 4
      #define NONE   5 
        
  //  Update position from keypad input
      void Input_keypad()
      {
       delay(SensitivityKeypad);
       KeyValue = analogRead(0); // Read the value from the keypad shield
       Display_Input_keypad_serial();
       if (KeyValue < 800) 
       {
        Pos = Input_calculate_keypad();
        Display_menu();
        if (DoorStatus > 6) {Initiate_door_event();}
        if (NestStatus > 6) {Initiate_nest_event();}
        if (LightStatus > 6) {Initiate_light_event();}
       }
       if (Active_menu() > 1) {Display_menu();}
      }
        
  //  Get input from keypad 
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

  //  Check status of keypad and update position and cursor - returns updated Pos variable
      int Input_calculate_keypad()
      {
       KeyStatus = Input_read_keypad();
       switch (KeyStatus)            
       {
        case RIGHT:
         Cur = 2;
         if (Pos < 20) return 21;
         if (Pos < 30) return 31;
         if (Pos < 40) return 11;
         return Pos;
         break;
               
        case LEFT:
         Cur = 2;
         if (Pos < 20) return 31;
         if (Pos > 30) return 21;
         if (Pos > 20) return 11;
         return 11;
         break;
   
        case UP:
         if (Pos < 20) return 11;
         if (Pos%10 == 1) {Cur = 2; CurDel = 1; return Pos;}
         if (Pos%10 == 2)
          {
           if (Cur = 1) {Cur = 1; return --Pos;}
          }
         if (Cur == 1) {Cur = 0; CurDel = 1; return Pos; }
         if (Cur == 0) return --Pos;
         break;
        
        case DOWN:
          if (Pos < 20) return 11;
          if (Pos%10 == (LineMax-1)) {Cur = 1; return Pos;}
          if (Cur == 1) {return ++Pos;}
          if (Pos%10 == 1) {Cur = 1; CurDel = 2; return Pos;}
          if (Cur == 2) {Cur = 1; return Pos;}
          if (Cur == 0) {Cur = 1;CurDel = 0;return Pos;}
          return 11;
          break;
        
        case SELECT:
           if (Pos < 20) return 11;
           if (Cur == 1) {++Pos;}
           switch (Pos)
           {
            case 22: LightStatus = 7;
                     return 11;
                     break;
            case 23: LightStatus = 8;
                     return 11;
                     break;
            case 24: DoorStatus = 7;
                     return 11;
                     break;
            case 25: DoorStatus = 8;
                     return 11;
                     break;
            case 26: NestStatus = 7;
                     return 11;
                     break;
            case 27: NestStatus = 8;
                     return 11;
                     break;
            case 28: return 11;
                     break;
            default: return Pos;break;
            }
            if (Cur == 1) {--Pos;}
            break;
      
          case NONE: return Pos; break;

          default: return Pos; break;
        }
     }

//DETERMINES THE STATUS OF LIGHT, DOOR AND NESTS. STATUS IS USED TO DETERMINE, IF EVENTS SCHOULD BE INITIATED

 //Check light status
 /*
  Values:
  0 = No light nedded
  1 = Morning light has not been turned on yet
  2 = Morning light is turned on
  3 = Morning light has been turned off
  4 = Evening light is turned on
  5 = Turn light on manually
  6 = Turn light off manually
  7 = Forces turn on
  8 = Set back to automatic
  */

  byte Check_light_status()
  {
     Display_Check_light_status_serial();
     if (LightStatus == 7) return 7;
     if (LightStatus == 8) return 0;
     if (TimeWithElectricLight_seconds <= 0) return 7; // Do not turn on light
     else
     {
      // Morning should be turned on
      if ((LightOnMorning_t <= now()) && (now()<LightOffMorning_t))
      {
       if (LightOnMorning_set == 2) return 5; // Turn light on manually
       else return 2;
      }
       // Morning light should be turned off, and evening light schould not be turned on yet
       if ((LightOffMorning_t <= now()) && (now() < LightOnEvening_t))
       {
        if (LightOffMorning_set == 2) return 6; // Turn light off manually
        else return 3;}
       }
       // Evening light should be turned on
       if ((LightOnEvening_t <= now()) && ((now() < LightOffEvening_t)))
       {
        if (LightOnEvening_set == 2) return 5; // Turn light on manually
        else return 4;
       }
       //Evening light schould be turned off
       if ((LightOffEvening_t <= now()) || (LightOnMorning_t > now()))
       {
         if (LightOffMorning_set == 2) return 6; // Turn light off manually
         else return 1;
       }
     Display_light_status_serial();  
     }
 
  //Check door status - values:
    /*
    Status   Actual position          Expected posision    Action            lcd TEXT
    0        
    1        Closed (2)               Closed               Stop              Opens at 00:00
    2        Closed (2) / Unknown (0) Open                 Open              Opening...
    3        Open (1) / Unkonwn (0)   Closed               Close             Closing...
    4        Open (1)                 Open                 Stop              Closes at 00:00
    5        -                        -                    -                 Open manually
    6        -                        -                    -                 Close manually
    7        -                        Open                 Open              Forced opening until next event or reset (ActualPosition not updated)
    8        -                        Closed               Closed            Forced closing until next event or reset (ActualPosition not updated)                   
    */  

  void Check_door_status()
  {
    //Expected to be closed
    if ((DoorClose_t < now () || now() < DoorOpen_t))
    { 
      if (DoorClose_set == 2) {DoorStatus = 6;}
      else
      {
        if (DoorActualPosition == 0 || DoorActualPosition == 1) {DoorStatus = 3;}
        if (DoorActualPosition == 2)  {DoorStatus = 1;}
      } 
    }
    
    //Expected to be open
    if (DoorOpen_t < now() && now() < DoorClose_t)
    {
      if (DoorOpen_set == 2) {DoorStatus = 5;}
      else
      {
        if (DoorActualPosition == 2 || DoorActualPosition == 0)  {DoorStatus = 2;}
        if (DoorActualPosition == 1) {DoorStatus = 4;}
      }
    }
    Display_Check_door_status_serial();
    Display_door_status_serial();
  }
        
  //Check nest status - values:
  /*
  Status   Actual position           Expected posision    Action            lcd TEXT
  1        Closed (2)                Closed               Stop              Opens at 00:00
  2        Closed (2) / Unkonown (0) Open                 Open              Opening...
  3        Open (1) / Unknown (0)    Closed               Close             Closing...
  4        Open (1)                  Open                 Stop              Closes at 00:00
  5                                                                         Open manually
  6                                                                         Close manually
  7        -                         Open                 Open              Forced opening until next event or reset (ActualPosition not updated)
  8        -                         Closed               Closed            Forced closing until next event or reset (ActualPosition not updated)  
  */  

  void Check_nest_status()
  {
    //Expected to be closed
    if ( (NestClose_t < now () || now() < NestOpen_t)) 
    {
      if (NestClose_set == 2) {NestStatus = 6;}
      else
      {
        if (NestActualPosition == 2) {NestStatus = 1;}
        if (NestActualPosition == 1 || NestActualPosition == 0) {NestStatus = 3;}
      }
    }
  
    //Expected to be open
    if (NestOpen_t < now() && now() < NestClose_t) 
    {
      if (NestOpen_set == 2) {NestStatus = 5;}
      else
      {
        if (NestActualPosition == 2 || NestActualPosition == 0) {NestStatus = 2;}
        if (NestActualPosition == 1) {NestStatus = 4;}
      }
    }
    Display_Check_nest_status_serial();
    Display_nest_status_serial();
   }

//SET TIMERS

//Light
    
  void Setup_light_timer()
  {        
  //Calculate time with electric light - determine, if light schuld be activated or not
    TimeWithElectricLight_seconds = ((TimeWithLight_hours*60UL*60UL)-TodaysSunSet_t+TodaysSunRise_t);
    
  //Morning light ON
    if (LightOnMorning_set == 1) // Values: 1 = Specific time set, 0 = Time set automatically to turn on in the morning and evening if needed (using TimeWithLight_hours), 2 = Disabled - turn on manually, 3 = Time set automatically to turn on only in the morning if needed
    {
      LightOnMorning_t = Time_t(LightOnMorning_hour, LightOnMorning_minute);
    }
    if (LightOnMorning_set == 3)
    {
      LightOnMorning_t = TodaysSunRise_t-TimeWithElectricLight_seconds/2;
    }
    if (LightOnMorning_set == 3)
    {
      LightOnMorning_t = TodaysSunRise_t-TimeWithElectricLight_seconds;
    } 
      
  //Morning light OFF
    if (LightOffMorning_set == 1) // Manual setting of opening times. Values: 1 = Manual, 0 = Automatic
    {
      LightOffMorning_t = Time_t(LightOffMorning_hour, LightOffMorning_minute);
    }
    else
    {
      LightOffMorning_t = TodaysSunRise_t+LightOffDelayAfterSunRise_minutes*60;
    } 
  
  //Evening light ON
    if (LightOnEvening_set == 1) // Values: 1 = Manual, 0 = Automatic
    {
      LightOnEvening_t = Time_t(LightOnEvening_hour, LightOnEvening_minute);
    }
    else
    {
      LightOnEvening_t = TodaysSunSet_t+LightOnDelayAfterSunSet_minutes*60;
    }
    
  //Evening light OFF
    if (LightOffEvening_set == 1)
    {
      LightOffEvening_t = Time_t(LightOffEvening_hour, LightOffEvening_minute);
    }
    else
    {
      LightOffEvening_t = TodaysSunSet_t+TimeWithElectricLight_seconds/2;
    }
    Display_Setup_light_timer_serial();
    Display_sunrise_sunset_serial();
   }
   
  //Door
    void Setup_door_timer()
    {        
    //Door opening
      if (DoorOpen_set == 1) // Manual setting of opening times. Values: 1 = Time, 0 = Automatic timer, 2 = Manual opening
      {
        DoorOpen_t = Time_t(DoorOpen_hour, DoorOpen_minute);
      }
      else
      {
        DoorOpen_t = TodaysSunRise_t+DoorOpenDelayAfterSunRise_minutes*60;
      } 
  
    //Door closing
      if (DoorClose_set == 1) // Manual setting of opening times. Values: 1 = Timer, 0 = Automatic, 2 = Manual
      {
        DoorClose_t = Time_t(DoorClose_hour, DoorClose_minute);
      }
      else
      {
        DoorClose_t = TodaysCivilTwilightEvening_t+DoorCloseDelayAfterCivilTwilight_minutes*60;
      }
      Display_Setup_door_timer_serial();
    }
    
  //Nests
    void Setup_nest_timer()
    {       
    //Nest opening
      if (NestOpen_set == 1) // Manual setting of opening times. Values: 1 = Timer, 0 = Automatic, 2 = Manual
      {
        NestOpen_t = Time_t(NestOpen_hour, NestOpen_minute);
      }
      else
      {
        if (TodaysCivilTwilightMorning_t <= LightOnMorning_t) {NestOpen_t = TodaysCivilTwilightMorning_t+NestOpenDelayAfterCivilTwilight_minutes*60;}
        if (TodaysCivilTwilightMorning_t > LightOnMorning_t) {NestOpen_t = LightOnMorning_t+NestOpenDelayAfterCivilTwilight_minutes*60;}
      } 
  
    //Nest closing
      if (NestClose_set == 1) // Manual setting of opening times. Values: 1 = Timer, 0 = Automatic, 2 = Manual
      {
        NestClose_t = Time_t(NestClose_hour, NestClose_minute);
      }
      else
      {
        NestClose_t = DoorClose_t+NestCloseDelayAfterDoorClose_minutes*60;
      }
      Display_Setup_nest_timer_serial();
    }
  

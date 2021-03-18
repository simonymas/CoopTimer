//SET TIMERS

//Light
  
  void Setup_light_timer()
  {        
  //Calculate time with electric light - determine, if light should be activated or not
    TimeWithElectricLight_seconds = ((TimeWithLight_hour*60UL*60UL+TimeWithLight_minute*60UL)-TodaysSunSet_t+TodaysSunRise_t);
    
  //Morning light ON
    if (LightOnMorning_set == 1) // Values: 1 = Specific time set, 0 = Time set automatically to turn on in the morning if needed, 2 = Disabled - turn on manually
    {
      LightOnMorning_t = Time_t(LightOnMorning_hour, LightOnMorning_minute);
    }
    if (LightOnMorning_set == 0)
    {
      if (LightOffEvening_set == 0) {LightOnMorning_t = TodaysSunRise_t-TimeWithElectricLight_seconds/2;}
      if (LightOffEvening_set == 1) {LightOnMorning_t = TodaysSunRise_t-TimeWithElectricLight_seconds-(LightOffEvening_t-TodaysSunSet_t);}
      else {LightOnMorning_t = TodaysSunRise_t-TimeWithElectricLight_seconds;}
    }
      
  //Morning light OFF
    if (LightOffMorning_set == 1)
    {
      LightOffMorning_t = Time_t(LightOffMorning_hour, LightOffMorning_minute);
    }
    else
    {
      LightOffMorning_t = TodaysSunRise_t-LightOffDelayAfterSunRise_minute*60;
    } 
  
  //Morning dimmer ON
    LightDimmerOnMorning_t = LightOnMorning_t-LightDimmerOnPrecedeLight_minute*60;
  
  //Morning dimmer OFF
    LightDimmerOffMorning_t = LightOffMorning_t;
  
  //Evening light ON
    if (LightOnEvening_set == 1)
    {
      LightOnEvening_t = Time_t(LightOnEvening_hour, LightOnEvening_minute);
    }
    else
    {
      LightOnEvening_t = TodaysSunSet_t-LightOnPrecedeSunSet_minute*60;
    }
    
  //Evening light OFF
    if (LightOffEvening_set == 1)
    {
      LightOffEvening_t = Time_t(LightOffEvening_hour, LightOffEvening_minute);
    }
    {
      if (LightOnMorning_set == 0) {LightOffEvening_t = TodaysSunSet_t+TimeWithElectricLight_seconds/2;}
      if (LightOnMorning_set == 1) {LightOffEvening_t = TodaysSunSet_t+TimeWithElectricLight_seconds-(TodaysSunRise_t-LightOnMorning_t);} 
      else {LightOffEvening_t = TodaysSunSet_t+TimeWithElectricLight_seconds;}
    }

  //Evening dimmer ON
    LightDimmerOnEvening_t = LightOnEvening_t;
  
  //Evening dimmer OFF
    LightDimmerOffEvening_t = LightOffEvening_t+LightDimmerOffDelayAfterLight_minute*60;  
    
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
  

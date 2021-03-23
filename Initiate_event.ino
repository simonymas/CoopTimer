//CONTROL TIMERS OF LIGHT SWICH

  void Initiate_event()
  {
    Initiate_light_event();
    Initiate_dimmer_event();
    Initiate_door_event();
    Initiate_nest_event();
  }
  
  void Initiate_light_event()
  {
   Display_Initiate_light_event_serial();
   LightStatus = Check_light_status();
   switch(LightStatus)
   {
     case 0: Motor_off_light(); break; // 0 = No light nedded
     case 1: Motor_off_light(); break; // 1 = Morning light has not been turned on yet
     case 2: Motor_on_light(); break;  // 2 = Morning light is turned on
     case 3: Motor_off_light(); break; // 3 = Morning light has been turned off
     case 4: Motor_on_light(); break;  // 4 = Evening light is turned on
     case 5: break;                    // 5 = Turn light on manually
     case 6: break;                    // 6 = Turn light off manually
     case 7: Motor_on_light(); Display_notice_menu(Display_light_status, LightStatus); break; // 7 = Forces turn on
     case 8: break;                   // 8 = Set back to automatic
     default: break;
   }
   Check_light_status();
  }

  void Initiate_dimmer_event()
  {
    byte DimmerStatus = Check_dimmer_status();
    switch(DimmerStatus)
    {
      case 0: Motor_off_dimmer_light(); break;
      case 1: Motor_on_dimmer_light(); break;
      default: break;
    }
  }
  
  void Initiate_door_event()
  {
    Display_Initiate_door_event_serial();
    switch(DoorStatus)
    {
      case 1: break;
      case 2: Motor_open_door(); DoorActualPosition = 1; Check_door_status(); break;
      case 3: Motor_close_door(); DoorActualPosition = 2; Check_door_status(); break;
      case 4: break;
      case 5: break;
      case 6: break;
      case 7: Motor_open_door(); break;
      case 8: Motor_close_door(); break;
      default: break;
   }
   Check_door_status();
  } 
  
    void Initiate_nest_event()
  {
    Display_Initiate_nest_event_serial();
    switch(NestStatus)
    {
      case 1: break;
      case 2: Motor_open_nest(); NestActualPosition = 1; break;
      case 3: Motor_close_nest(); NestActualPosition = 2; break;
      case 4: break;
      case 5: break;
      case 6: break;
      case 7: Motor_open_nest(); break;
      case 8: Motor_close_nest(); break;
      default: break;
   }
   Check_nest_status();
  }

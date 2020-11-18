//CONTROL TIMERS OF LIGHT SWICH
  
  void Initiate_light_event()
  {
   Display_Initiate_light_event_serial();
   LightStatus = Check_light_status();
   switch(LightStatus)
   {
     case 0: Motor_off_light(); break;
     case 1: Motor_off_light(); break;
     case 2: Motor_on_light(); break;
     case 3: Motor_off_light(); break;
     case 4: Motor_on_light(); break;
     case 5: break;
     case 6: break;
     case 7: Motor_on_light(); Display_notice_menu(Display_light_status, LightStatus); break;
     case 8: Display_notice_menu(Display_light_status, LightStatus); break;
     default: Display_ERROR; Display_ERROR_serial; break;
   }
   Check_light_status();
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
      default: Display_ERROR(); Display_ERROR_serial(); break;
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
      default: Display_ERROR(); Display_ERROR_serial(); break;
   }
   Check_nest_status();
  }

//CONTROL OF RELAY TO OPEN AND CLOSE NEST

//  Opening nest
    void Motor_open_nest()
    {
      Display_Motor_open_nest_serial();
      digitalWrite(Relay_4, HIGH);
      digitalWrite(Relay_6, HIGH);
      NestStatus = 2;
      time_t TimeNestOpenStart_t = now();
      while (TimeNestOpenStart_t + NestOpenProcessing_seconds > now())
      {
        Reset_watchdog_timer();
        digitalWrite(Relay_3, LOW);
        digitalWrite(Relay_5, LOW);
        Display_notice_menu(Display_nest_status, NestStatus);
        Input_keypad();
      }
      digitalWrite(Relay_3,HIGH);
      digitalWrite(Relay_5, HIGH);   
      NestStatus = 4;
   }

//  Closing nest
    void Motor_close_nest()
    {
      Display_Motor_close_nest_serial();
      time_t TimeNestCloseStart_t = now();
      digitalWrite(Relay_3, HIGH);
      digitalWrite(Relay_5, HIGH);
      NestStatus = 3;
      while (TimeNestCloseStart_t + NestCloseProcessing_seconds > now())
      {
        Reset_watchdog_timer();
        digitalWrite(Relay_4, LOW);digitalWrite(Relay_6, LOW);
        Display_notice_menu(Display_nest_status, NestStatus);      
       }
        digitalWrite(Relay_4,HIGH);
        digitalWrite(Relay_6,HIGH);
        NestStatus = 1;
      }

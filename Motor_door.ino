//CONTROL OF RELAY TO OPEN AND CLOSE DOOR

//  Opening door
    void Motor_open_door()
    {
      Display_Motor_open_door_serial();
      time_t TimeDoorOpenStart_t = now();
      digitalWrite(Relay_2,HIGH);
      DoorStatus = 2;
      while (TimeDoorOpenStart_t + DoorOpenProcessing_seconds > now())
      {
        Reset_watchdog_timer();
        digitalWrite(Relay_1,LOW);
        Display_notice_menu(Display_door_status, DoorStatus);
      }
      digitalWrite(Relay_1,HIGH);
      DoorStatus = 4;
    }

//  Closing door  
    void Motor_close_door()
    {
      Display_Motor_close_door_serial();
      byte DoorTurns = 0;
      time_t TimeDoorCloseStart_t = now();
      digitalWrite(Relay_1,HIGH);
      DoorStatus = 3;
      while (TimeDoorCloseStart_t + DoorCloseProcessing_seconds > now())
      {
        Reset_watchdog_timer();
        if (DoorTurns%2 == 0) {digitalWrite(Relay_2,HIGH);}
        else {digitalWrite(Relay_2,LOW);}
        ++DoorTurns;
        Display_notice_menu(Display_door_status, DoorStatus);
      }
      digitalWrite(Relay_2,HIGH);
      DoorStatus = 3;
    }

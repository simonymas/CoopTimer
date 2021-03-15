//SETUP TIMERS FROM VALUES SAVED IN EEPROM

  //  Function to set update EEPROM - values of Eeprom_status: 1 = EEPROM is updated, don't save anything, 0 = Save preset values / nothing has been saved in EEPROM by this program, 2 = Update EPROM from time values entered via keypad (values are only written to eeprom, if they have changed)
      void Setup_eeprom()
      {
        if (Eeprom_status == 0)  
        {
          EEPROM.put(Eeprom_status_address,1);   
          EEPROM.put(LightOnMorning_set_address, LightOnMorning_set_preset);
          EEPROM.put(LightOnMorning_hour_address, LightOnMorning_hour_preset);
          EEPROM.put(LightOnMorning_minute_address, LightOnMorning_minute_preset);
          EEPROM.put(LightOffMorning_set_address, LightOffMorning_set_preset);
          EEPROM.put(LightOffMorning_hour_address, LightOffMorning_hour_preset);
          EEPROM.put(LightOffMorning_minute_address, LightOffMorning_minute_preset);
          EEPROM.put(TimeWithLight_hour_address, TimeWithLight_hour_preset);
          EEPROM.put(TimeWithLight_minute_address, TimeWithLight_minute_preset);
          EEPROM.put(DoorOpen_set_address, DoorOpen_set_preset);
          EEPROM.put(DoorOpen_hour_address, DoorOpen_hour_preset);
          EEPROM.put(DoorOpen_minute_address, DoorOpen_minute_preset);
          EEPROM.put(DoorClose_set_address, DoorClose_set_preset);
          EEPROM.put(DoorClose_hour_address, DoorClose_hour_preset);
          EEPROM.put(DoorClose_minute_address, DoorClose_minute_preset);
          EEPROM.put(NestOpen_set_address, NestOpen_set_preset);
          EEPROM.put(NestOpen_hour_address, NestOpen_hour_preset);
          EEPROM.put(NestOpen_minute_address, NestOpen_minute_preset);
          EEPROM.put(NestClose_set_address, NestClose_set_preset);
          EEPROM.put(NestClose_hour_address, NestClose_hour_preset);
          EEPROM.put(NestClose_minute_address, NestClose_minute_preset);
        }
        
        if (Eeprom_status == 2)  
        {
          EEPROM.put(Eeprom_status_address,1);   
          EEPROM.put(LightOnMorning_set_address, LightOnMorning_set);
          EEPROM.put(LightOnMorning_hour_address, LightOnMorning_hour);
          EEPROM.put(LightOnMorning_minute_address, LightOnMorning_minute);
          EEPROM.put(LightOffMorning_set_address, LightOffMorning_set);
          EEPROM.put(LightOffMorning_hour_address, LightOffMorning_hour);
          EEPROM.put(LightOffMorning_minute_address, LightOffMorning_minute);
          EEPROM.put(TimeWithLight_hour_address, TimeWithLight_hour);
          EEPROM.put(TimeWithLight_minute_address, TimeWithLight_minute);
          EEPROM.put(DoorOpen_set_address, DoorOpen_set);
          EEPROM.put(DoorOpen_hour_address, DoorOpen_hour);
          EEPROM.put(DoorOpen_minute_address, DoorOpen_minute);
          EEPROM.put(DoorClose_set_address, DoorClose_set);
          EEPROM.put(DoorClose_hour_address, DoorClose_hour);
          EEPROM.put(DoorClose_minute_address, DoorClose_minute);
          EEPROM.put(NestOpen_set_address, NestOpen_set);
          EEPROM.put(NestOpen_hour_address, NestOpen_hour);
          EEPROM.put(NestOpen_minute_address, NestOpen_minute);
          EEPROM.put(NestClose_set_address, NestClose_set);
          EEPROM.put(NestClose_hour_address, NestClose_hour);
          EEPROM.put(NestClose_minute_address, NestClose_minute);
        }
      }

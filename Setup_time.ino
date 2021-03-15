//SET TIME OF DS3231 - if function is is activated in "setup()" og time is changed from menu

     void Setup_DS3231_from_arduino_time()
     {
      // Write time to DS3231
      Wire.beginTransmission(DS3231_I2C_ADDRESS);
      Wire.write(0); // set next input to start at the seconds register
      Wire.write(decToBcd(0)); // set seconds
      Wire.write(decToBcd(minute())); // set minutes
      Wire.write(decToBcd(hour())); // set hours
      Wire.write(decToBcd(1)); // set day of week (1=Sunday, 7=Saturday)
      Wire.write(decToBcd(day())); // set day (1 to 31)
      Wire.write(decToBcd(month())); // set month
      Wire.write(decToBcd(year()-2000)); // set year (0 to 99)
      Wire.endTransmission();
     }
     // Convert binary coded decimal to normal decimal numbers
     byte decToBcd(byte val)
     {
      return((val/10*16) + (val%10));
     }

//SYNC TIME FROM RTC DS3231 - Runs every day at 01:00 at restart
  
     // Sync time from real time clock DS3231
     void Setup_arduino_from_DS3231_time() 
     {
      //Getting time from DS3231
      byte DS3231second, DS3231minute, DS3231hour, DS3231dayOfWeek, DS3231day, DS3231month, DS3231year; 
      read_time(&DS3231second,&DS3231minute,&DS3231hour,&DS3231dayOfWeek,&DS3231day,&DS3231month,&DS3231year); 
      setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, DS3231year); // Setting Arduino time
      
      // Set daylight saving time - at 0:00 when Arduino resets
      if (((DS3231month>3) && (DS3231month<10)) || ((DS3231month==3) && (DS3231day-DS3231dayOfWeek>23))  || ((DS3231month==10) && ((DS3231day-DS3231dayOfWeek)<23)))  // Determine if DST should be set (between last sunday of march and last sunday of october at 1:00
      {  
        ++DS3231hour; // Adding one hour to the DS3231 time
        DST = 1; // Indicating, that DST is now activated
        setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, 2000+DS3231year); // Setting Arduino time
      }
      Display_Setup_time_sync_serial();
      Display_time_serial();
     }
   
     void read_time(byte *DS3231second,byte *DS3231minute,byte *DS3231hour,byte *DS3231dayOfWeek,byte *DS3231day,byte *DS3231month,byte *DS3231year)
     {      
      Wire.beginTransmission(DS3231_I2C_ADDRESS);
      Wire.write(0); // set DS3231 register pointer to 00h
      Wire.endTransmission();
      Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
    
      // Request seven bytes of data from DS3231 starting from register 00h
      *DS3231second = bcdToDec(Wire.read() & 0x7f);
      *DS3231minute = bcdToDec(Wire.read());
      *DS3231hour = bcdToDec(Wire.read() & 0x3f);
      *DS3231dayOfWeek = bcdToDec(Wire.read());
      *DS3231day = bcdToDec(Wire.read());
      *DS3231month = bcdToDec(Wire.read());
      *DS3231year = bcdToDec(Wire.read());
     }
      
     //Convert binary coded decimal to normal decimal numbers
     byte bcdToDec(byte val)
     {
      return( (val/16*10) + (val%16) ); 
     }

//UPDATE ARDUINO TIME FROM TIME SET IN MENUS - run, when time has been changed in menu

    void Setup_arduino_from_menu_time()
    {
      setTime(Time_hour, Time_minute, second(), Time_day, Time_month, Time_year); // Setting Arduino time
      Setup_DS3231_from_arduino_time(); // Setting DS3231 time from new arduino time
      Setup_menu_time(); // Setting time shown in menu to new values
    }

//UPDATE VARIABLES TO SHOW AND CHANGE TIME FROM MENUS

    void Setup_menu_time()
    {
      Time_hour = hour();
      Time_minute = minute();
      Time_day = day();
      Time_month = month();
      Time_year = year();
    }

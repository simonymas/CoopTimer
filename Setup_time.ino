//SET TIME OF DS3231 - if function is is activated in "setup()" og time is changed from menu

     void Setup_DS3231_from_arduino_time()
     {
      // Write time to DS3231
      Wire.beginTransmission(DS3231_I2C_ADDRESS);
      Wire.write(0); // set next input to start at the seconds register
      Wire.write(decToBcd(second())); // set seconds
      Wire.write(decToBcd(minute())); // set minutes
      Wire.write(decToBcd(hour())); // set hours
      Wire.write(decToBcd(1));
      Wire.write(decToBcd(day())); // set day (1 to 31)
      Wire.write(decToBcd(month())); // set month
      Wire.write(decToBcd(year()-2000)); // set year (0 to 99)
      Wire.endTransmission();
     }
     // Convert normal decimal numbers to binary coded decimal 
     byte decToBcd(byte val)
     {
      return((val/10*16) + (val%10));
     }

//SYNC TIME FROM RTC DS3231 - Runs every day at 01:00 at restart
  
     // Sync time from real time clock DS3231 and set DST (daylight saving time) automatically
     void Setup_arduino_from_DS3231_time() 
     {
      //Getting time from DS3231
      byte DS3231second, DS3231minute, DS3231hour, DS3231dayOfWeek, DS3231day, DS3231month, DS3231year; 
      read_time(&DS3231second,&DS3231minute,&DS3231hour,&DS3231dayOfWeek,&DS3231day,&DS3231month,&DS3231year); 
      
      // Set daylight saving time 
      DST = Calculate_DST(DS3231day, DS3231month, DS3231year); // Finding out, if DST is now activated - pass bytes: day, month, year (2 digits)
      byte DSTLast = EEPROM.read(DSTLast_address);
      if (DST != DSTLast)
      {
       if (DST == 1) {++DS3231hour;} // Adding one hour to the DS3231 time if daylight saving time has now begun
       if (DST == 0) {--DS3231hour;} // Substracting one hour from the DS3231 time if daylight saving time has now begun
       setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, DS3231year+2000); // Setting Arduino time
       Setup_DS3231_from_arduino_time(); // Saving new time to DS3231 
       EEPROM.put(DSTLast_address, DST);
      } 

      //Setting arduino time
      setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, DS3231year+2000); // Setting Arduino time
      
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

//Utility functions to determine if today is DST

    byte Calculate_DST(byte d, byte m, byte y) //Pass day, month and year (2 digits) - DST is returned
    {
      byte DoW = Calculate_DoW(d, m, y);
      if (((m>3) && (m<10)) || ((m==3) && (d-DoW>23))  || ((m==10) && ((d-DoW)<23)))  // Determine if DST should be set (between last sunday of march and last sunday of october at 1:00
      {
       return 1;
      }
       else {return 0;}
    }
    
    int Calculate_DoW(byte d, byte m, byte y) //Pass day, month and year (2 digits) - Day of week is returned
    {
     int yyyy = y+2000;  // 4-digigit year
     int yy;            // Last 2 digits of the year (ie 2016 would be 16)
     int c;             // Century (ie 2016 would be 20)
     int mTable;        // Month value based on calculation table
     int SummedDate;    // Add values combined in prep for Mod7 calc
     byte DoW;           // Day of the week value (0-6)
     int leap;          // Leap Year or not
     int cTable;        // Century value based on calculation table

     // Leap Year Calculation
     if((fmod(yyyy,4) == 0 && fmod(yyyy,100) != 0) || (fmod(yyyy,400) == 0))
     { leap = 1; }
     else 
     { leap = 0; }

     // Limit results to year 2020-2299 (to save memory)
     while(yyyy > 2299)
     { yyyy = yyyy - 400; }
     while(yyyy < 2020)
     { yyyy = yyyy + 400; }

     // Calculating century 
     c = yyyy/100;

     // Calculating two digit year
     yy = fmod(yyyy, 100);

     // Century value based on Table
     if(c == 20) { cTable = 0; }
     if(c == 21) { cTable = 5; }
     if(c == 22) { cTable = 3; }

     // Jan and Feb calculations affected by leap years
     if(m == 1)
     { if(leap == 1) { mTable = 6; }
       else          { mTable = 0; }}
     if(m == 2)
     { if(leap == 1) { mTable = 2; }
       else          { mTable = 3; }}
     // Other months not affected and have set values
     if(m == 10) { mTable = 0; }
     if(m == 8) { mTable = 2; }
     if(m == 3 || m == 11) { mTable = 3; }
     if(m == 4 || m == 7) { mTable = 6; }
     if(m == 5) { mTable = 1; }
     if(m == 6) { mTable = 4; }
     if(m == 9 || m == 12) { mTable = 5; }

     // Enter the data into the formula
     SummedDate = d + mTable + yy + (yy/4) + cTable;
    
     // Find remainder
     DoW = fmod(SummedDate,7);

     //Convert to numbers from 1-7
     if (DoW == 0) {DoW = 7;}
     
     //Return Dow
     return DoW;
    }

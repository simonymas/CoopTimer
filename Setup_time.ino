//SET TIME - Runs every day at 00:00 at restart
  
  // Setting time of DS3231 - if initial time is activated in "setup()"
     void Setup_time_initial(byte DS3231second, byte DS3231minute, byte DS3231hour, byte DS3231dayOfWeek, byte DS3231day, byte DS3231month, byte DS3231year)
     {
      // Write time to DS3231
      Wire.beginTransmission(DS3231_I2C_ADDRESS);
      Wire.write(0); // set next input to start at the seconds register
      Wire.write(decToBcd(DS3231second)); // set seconds
      Wire.write(decToBcd(DS3231minute)); // set minutes
      Wire.write(decToBcd(DS3231hour)); // set hours
      Wire.write(decToBcd(DS3231dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
      Wire.write(decToBcd(DS3231day)); // set date (1 to 31)
      Wire.write(decToBcd(DS3231month)); // set month
      Wire.write(decToBcd(DS3231year)); // set year (0 to 99)
      Wire.endTransmission();
     }
     // Convert binary coded decimal to normal decimal numbers
     byte decToBcd(byte val)
     {
      return((val/10*16) + (val%10));
     }

  // Syncing time from real time clock DS3231
     void Setup_time_sync() 
     {
      //Getting time from DS3231
      byte DS3231second, DS3231minute, DS3231hour, DS3231dayOfWeek, DS3231day, DS3231month, DS3231year; 
      read_time(&DS3231second,&DS3231minute,&DS3231hour,&DS3231dayOfWeek,&DS3231day,&DS3231month,&DS3231year); 
      setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, DS3231year); // Setting Arduino time    
      
   // Setting Daylight saving time - at 0:00 when Arduino resets
      if (((DS3231month>3) && (DS3231month<10)) || ((DS3231month==3) && (DS3231day-DS3231dayOfWeek>23))  || ((DS3231month==10) && ((DS3231day-DS3231dayOfWeek)<23)))  // Determine if DST should be set (between last sunday of march and last sunday of october at 1:00
      {  
        ++DS3231hour; // Adding one hour to the DS3231 time
        DST = 1; // Indicating, that DST is now activated
        setTime(DS3231hour, DS3231minute, DS3231second, DS3231day, DS3231month, DS3231year); // Setting Arduino time
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

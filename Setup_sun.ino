//SETTING TIME OF SUNRISE AND SUNSET

  //Calculating time of todays sunrise and sunset
  void Setup_sun()
  {
   byte dayTimeLord = day();
   byte monthTimeLord = month();
   byte yearTimeLord = year();
   byte sunRise[]  = {0, 0, 0, dayTimeLord, monthTimeLord, yearTimeLord};
   byte sunSet[]  = {0, 0, 0, dayTimeLord, monthTimeLord, yearTimeLord}; 
 
   TimeLord sunTimeLord;
   
   sunTimeLord.Position(Lattitude, Longitude); //Set position as defines in global constants
   sunTimeLord.TimeZone(1 * 60); // set zone to Denmark
   
   sunTimeLord.SunRise(sunRise);
   sunTimeLord.SunSet(sunSet);
   
     //Ajust to DST
     if (DST == 1) //Determining if DST is activated. Variable defined in Setup_time()
      {  
        ++sunRise[2];
        ++sunSet[2];
       }
   
     //Calculating time_t numbers for sunrise and sunset
     TodaysSunRise_t = Time_t(sunRise[2],sunRise[1]); //Time_t function defined in Setup_time
     TodaysSunSet_t = Time_t(sunSet[2],sunSet[1]);
     
     //Calculating time_t numbers for civil twilight - In Denmark the time in between sunrise/set and civil twilight varies from 62 to 37 minutes - this formular is better, but still only accurate within aprox. 11 minutes...
     if (now()<=Time_date_t(23,3))
     {
       TodaysCivilTwilightMorning_t = TodaysSunRise_t-2820+7,20*(now()-Time_date_t(1,1))/86400;
       TodaysCivilTwilightEvening_t = TodaysSunSet_t+2820-7,20*(now()-Time_date_t(1,1))/86400;
     }
     
     if (now()>Time_date_t(23,3) || now()<=Time_t(23,6))
     {
       TodaysCivilTwilightMorning_t = TodaysSunRise_t-2220-16,12*(now()-Time_date_t(23,3))/86400;
       TodaysCivilTwilightEvening_t = TodaysSunSet_t+2220+16,12*(now()-Time_date_t(23,3))/86400;
     }
     
     if (now()>Time_date_t(23,6) || now()<=Time_t(23,9))
     {
       TodaysCivilTwilightMorning_t = TodaysSunRise_t-2220-16,12*(Time_date_t(23,9)-now())/86400;
       TodaysCivilTwilightEvening_t = TodaysSunSet_t+2220+16,12*(Time_date_t(23,3)-now())/86400;
     }
     
     if (now()>=Time_date_t(23,3) || now()<Time_t(31,12))
     {
       TodaysCivilTwilightMorning_t = TodaysSunRise_t-2820-6,6*(Time_date_t(31,12)-now())/86400;
       TodaysCivilTwilightEvening_t = TodaysSunSet_t+2820+6,6*(now()-Time_date_t(1,1))/86400;
     }
     Display_Setup_sun_serial();
   }

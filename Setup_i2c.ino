//SETUP I2C TO COMMUNICATE WITH DS3231 AND RASPBERRY PI


int number = 0;
#define SLAVE_ADDRESS 0x06
#define DS3231_I2C_ADDRESS 0x68

void Setup_i2c()
{
      Wire.begin(SLAVE_ADDRESS);

       // define callbacks for i2c communication
       Wire.onReceive(receiveData);
       Wire.onRequest(sendData);
       Display_Setup_i2c_serial();
}

// callback for received data
void receiveData(int byteCount)
{
 while(Wire.available()) 
{
  number = Wire.read();
 }
}

// callback for sending data
void sendData(){
  if (number == 1) {
    Wire.write(weekday());
  }
    if (number == 2) {
    Wire.write(day());
  }
    if (number == 3) {
    Wire.write(month());
  }
    if (number == 4) {
    Wire.write(year()-2000);
  }
    if (number == 5) {
    Wire.write(hour());
  }
    if (number == 6) {
    Wire.write(minute());
  }
    if (number == 7) {
    Wire.write(second());
  }
    /*
    if (number == 8) {
    int rtemp = round(temp);
    Wire.write(rtemp);
    }
    */
    
    if (number == 9) {
    Wire.write(hour(LightOnMorning_t));
    }
     
    if (number == 10) {
    Wire.write(minute(LightOnMorning_t));
   }
    
       if (number == 11) {
    Wire.write(hour(LightOffMorning_t));
   }
   
       if (number == 12) {
    Wire.write(minute(LightOffMorning_t));
   }
   
          if (number == 13) {
    Wire.write(hour(LightOnEvening_t));
   }
   
       if (number == 14) {
    Wire.write(minute(LightOnEvening_t));
   }
             if (number == 15) {
    Wire.write(hour(LightOffEvening_t));
   }
   
       if (number == 16) {
    Wire.write(minute(LightOffEvening_t));
   }
}

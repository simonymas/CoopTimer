//SETUP PINS
   void Setup_pins()
   {
    // FOR ARDUINO MEGA
    //Set up input and output pins for Arduino MEGA
      pinMode(Relay_1, OUTPUT);
      pinMode(Relay_2, OUTPUT);
      pinMode(Relay_3, OUTPUT);
      pinMode(Relay_4, OUTPUT);
      pinMode(Relay_5, OUTPUT);
      pinMode(Relay_6, OUTPUT);
      pinMode(Relay_7, OUTPUT);
      pinMode(Relay_8, OUTPUT);
  
      pinMode (DisplayLight_OUT, OUTPUT);
      
    //Set status of pins for Arduino MEGA
      digitalWrite(Relay_1, HIGH);
      digitalWrite(Relay_2, HIGH);
      digitalWrite(Relay_3, HIGH);
      digitalWrite(Relay_4, HIGH);
      digitalWrite(Relay_5, HIGH);
      digitalWrite(Relay_6, HIGH);
      digitalWrite(Relay_7, HIGH);
      digitalWrite(Relay_8, HIGH);

    /* FOR ARDUINO UNO
    //Set up input and output pins
      pinMode(Relay_1, OUTPUT);
      pinMode(Relay_2, OUTPUT);
      pinMode(Relay_3, OUTPUT);
      pinMode(Relay_4, OUTPUT);
      pinMode(Relay_5, OUTPUT);
  
      pinMode(DisplayLight_OUT, OUTPUT);
      
    //Set status of pins
      digitalWrite(Relay_1, HIGH);
      digitalWrite(Relay_2, HIGH);
      digitalWrite(Relay_3, HIGH);
      digitalWrite(Relay_4, HIGH);
      digitalWrite(Relay_5, HIGH);

      Display_Setup_pins_serial();
      */
}

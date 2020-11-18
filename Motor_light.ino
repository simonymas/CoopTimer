//TURNING LIGHT ON AND OFF

//  Switching light on
    void Motor_on_light()
    {
      Display_Motor_on_light_serial();
      digitalWrite(Relay_7,LOW);
      digitalWrite(Relay_8,LOW);
     }

//  Switching light off
    void Motor_off_light()
    {
      Display_Motor_off_light_serial();
      digitalWrite(Relay_7,HIGH);
      digitalWrite(Relay_8,HIGH);
    }
    

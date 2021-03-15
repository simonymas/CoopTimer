//Define special characters æ,ø,å,Æ,Ø og Å
    
 void Setup_LCD()
 {
  byte Lae[8] ={ B00000,B00000,B11010,B00101,B01111,B10100,B11111,B00000}; // æ
  byte Loe[8] ={ B00000,B00001,B01110,B10101,B10101,B01110,B10000,B00000}; // ø
  byte Laa[8] ={ B00100,B00000,B01110,B00001,B01111,B10001,B01111,B00000}; // å
  byte Sae[8] ={ B01111,B10100,B10100,B11110,B10100,B10100,B10111,B00000}; // Æ
  byte Soe[8] ={ B00001,B01110,B10011,B10101,B11001,B01110,B10000,B00000}; // Ø
  byte Saa[8] ={ B00100,B00000,B01110,B10001,B11111,B10001,B10001,B00000}; // Å
  byte Up[8] = { B00100,B01010,B10101,B00100,B00100,B00100,B00100,B00000}; // Up
  byte Down[8] = {B00100,B00100,B00100,B00100,B10101,B01010,B00100,B00000}; // Down
  // æ, ø, å, Æ, Ø, Å, Up pointer, down pointer saved in RAM-adress 1, 2, 3, 4, 5, 6, 7, 0

  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(0,0);
  
  LCD.createChar(1, Lae); // æ
  LCD.createChar(2, Loe); // ø
  LCD.createChar(3, Laa); // å
  LCD.createChar(4, Sae); // Æ
  LCD.createChar(5, Soe); // Ø
  LCD.createChar(6, Saa); // Å
  LCD.createChar(7, Up); // Up pointer
  LCD.createChar(0, Down); // Down pointer

  analogWrite(DisplayLight_OUT, DisplayLightIntensity);

  Display_Setup_LCD_serial();
 } 
 
 //LCD.print(char(1)); // writes "æ"
 //LCD.print(char(2)); // writes "ø"
 //LCD.write(3); // writes "å"
 //LCD.write(4); // writes "Æ"
 //LCD.write(5); // writes "Ø"
 //LCD.write(6); // writes "Å"
 //LCD.write(7); // writes Up pointer
 //LCD.print(char(0)); // writes Down pointer

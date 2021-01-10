//GETTING TEMPERATURE FROM DS18b20

/*

void Input_temp()
{
      sensors.requestTemperatures();
      temp = sensors.getTempCByIndex(0);
 
}
*/

/*  sensors.requestTemperatures(); // Send the command to get temperatures
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature for Device 1 is: ");
  Serial.println(temp); // Why "byIndex"? 
  
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire */

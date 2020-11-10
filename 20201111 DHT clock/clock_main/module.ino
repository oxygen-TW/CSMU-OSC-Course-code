bool updateLCDTime() {
  tmElements_t tm;
  char timeStr[16] = {};
  lcd.setCursor(0, 0);

  //If RTC can be read property
  if (RTC.read(tm)){
    //If sscanf return wrong code then print error and exit function.
    if(sscanf(timeStr, "%d/%d %d:%d:%d", tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second) != 5){
      lcd.print("RTC Time error");
      return false;
    }

    //Everything of RTC are ok, output to LCD.
    lcd.print(timeStr);
  }
  else{
    //RTC is connected but not working.
    if (RTC.chipPresent()) {
      lcd.print("RTC Not working"); 
      return false;
    //Can not found RTC connection.
    } else {
      lcd.print("RTC Error"); 
      return false;
    }
  }
}

void updateDHTdata() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 1);
    lcd.print("Sensor ERROR");
    return;
  }

  //LCD Update
  lcd.setCursor(0, 1);
  lcd.print(t); 
  lcd.print((char) 0xDF); //度C符號 
  lcd.print(F("C ")); 
  lcd.print(h); lcd.print(F("%")); 
}

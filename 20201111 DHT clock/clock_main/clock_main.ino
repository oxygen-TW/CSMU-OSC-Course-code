/*
 * Author: Liu, Tzu-Hao CSMU, ROC
 * License: MIT
 * 
 * About Program:
 * For arduino read and display environment temperature and humidity to LCD.
 * For arduino connect with RTC module DS1307 and display to LCD.
 * 
 * ToDo:
 * 1. DHT 22 read rate is 0.5 Hz, We need new firmware to adapt it.
 * */

#include <DS1307RTC.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTpin 2
#define DHTtype DHT11
DHT dht(DHTpin, DHTtype);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("LCD auto Test");
  delay(1000);
  lcd.clear();

  //Debug only!
  // DHTinfo();
}

void loop() {
  //Main loop control interval between function and function.
  //一種防溢位的寫法 
  //ref. https://note.artchiu.org/2018/02/06/arduino-millis-%E4%BD%BF%E7%94%A8%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A0%85/
  static unsigned long start = millis();
  unsigned long aSec = 970; //修正參數 30 ms
  unsigned long DHTdelay = 1970;

  if (millis() - start > aSec)
  {
    updateLCDTime();
    updateDHTdata();
    start = millis();
  }
}

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

/* Set your UID here! 07 4C CF B4*/
#define passwordUIDArray {0x07, 0x4C, 0xCF, 0xB4}

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
byte UIDArray[4];
String passwordUID = "";

String ReadUID() {
  // Look for new cards
  while ( ! mfrc522.PICC_IsNewCardPresent()) {

  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  UIDArray[0] = mfrc522.uid.uidByte[0];
  UIDArray[1] = mfrc522.uid.uidByte[1];
  UIDArray[2] = mfrc522.uid.uidByte[2];
  UIDArray[3] = mfrc522.uid.uidByte[3];

  String str = String(UIDArray[0], HEX) + ":" + String(UIDArray[1], HEX) + ":" + String(UIDArray[2], HEX) + ":" + String(UIDArray[3], HEX);
  return str;
  delay(500);
}

void doSuccess(){
  Serial.println("Pass");
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  delay(300);
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  delay(300);
}

void doFailed(){
  Serial.println("Failed");
}

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  byte PUA[4] = passwordUIDArray;
  passwordUID = String(PUA[0], HEX) + ":" + String(PUA[1], HEX) + ":" + String(PUA[2], HEX) + ":" + String(PUA[3], HEX);
}

void loop(){
    String checkStr = ReadUID();

    Serial.print("UID = ");
    Serial.println(checkStr);
    if(checkStr == passwordUID){
      doSuccess();
    }else{
      doFailed();
    }
}

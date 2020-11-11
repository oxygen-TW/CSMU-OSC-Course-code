#include <DHT.h>

#define DHTpin 2
#define DHTtype DHT11

DHT dht(DHTpin, DHTtype);

void setup(){
  dht.begin(); //Initial DHT sensor
  Serial.begin(9600);
}

void loop(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  //Error handling
  if(isnan(t) || isnan(h)){
    Serial.println("DHT Sensor Error");
    delay(1000);
    return;
  }
  
  Serial.print(t);Serial.print(",");Serial.println(h);
  delay(1000);
}

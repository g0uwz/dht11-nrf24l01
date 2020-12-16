#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
#define DHTPIN 3  // D3
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
RF24 radio(7, 8); 
struct MyData {
  byte h;
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  dht.begin();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.h = dht.readHumidity();
  data.t = dht.readTemperature();
  if (isnan(data.h) || isnan(data.t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.println("Humidity: ");
  Serial.print(data.h);
  Serial.println("Temperature: ");
  Serial.print(data.t);
  radio.write(&data, sizeof(MyData));
}

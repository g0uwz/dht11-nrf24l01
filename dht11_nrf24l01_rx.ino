#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const uint64_t pipeIn = 0xE8E8F0F0E1LL;
RF24 radio(7, 8);
struct MyData {
  byte h;
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600);
  radio.begin();

  lcd.init();                 // initialize the lcd

  lcd.backlight();           // backlight on
  lcd.clear();

  lcd.print("Booting nRF24L01+");
  delay(500);
  lcd.clear();

  lcd.print("Connecting..");
  delay(500);
  lcd.clear();


  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();

}
void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
  }
}

void loop()
{
  recvData();

  lcd.setCursor(2, 0);
  lcd.print("Humidity. ");
  lcd.print(data.h);
  lcd.print("%");

  lcd.setCursor(3, 1);
  lcd.print("Temp. ");
  lcd.print(data.t);
  lcd.print(" C");

}

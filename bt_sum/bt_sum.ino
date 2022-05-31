#include "BluetoothSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Name");
  lcd.init();
  lcd.backlight();
  lcd.print("Hello, World");
}

void loop() {
  if (SerialBT.available()>0) {
    char data = SerialBT.read();
    Serial.write(data);
    if (data == '1') {
      int data_i = SerialBT.parseInt();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print('result = ');
      lcd.print(data_i);
    }
  }

}

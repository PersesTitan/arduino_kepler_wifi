#include "BluetoothSerial.h"
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
BluetoothSerial SerialBT;
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
int matrix_speed = 200;
int matrix_br = 50;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_17"); //이름 넣기
  matrix.begin();
  matrix.setTextColor(matrix_br);
}

void loop() {
  char temp[10];
  memset(temp, 0, sizeof(temp));
  if (SerialBT.available()>0) {
    char data = SerialBT.read();
    Serial.write(data);
    if (data == '1') {
      SerialBT.readBytes(temp, 10);
      Serial.write(temp);
      for (int x = 0; x>= -30; x--) {
        matrix.clear();
        matrix.setCursor(x, 1);
        matrix.print(temp);
        delay(matrix_speed);
      }
      matrix.clear();
    } 

    if (data == '2') {
      int speed = SerialBT.read();
      matrix_speed = (200-(speed * 2));
      Serial.println("speed");
      Serial.println(matrix_speed);
    }

    if (data == '3') {
      matrix_br = SerialBT.read();
      matrix.setTextColor(matrix_br);
      Serial.println("bright");
      Serial.println(matrix_br);
    }
  }

}

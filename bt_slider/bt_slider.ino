#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
int ledChannel = 0;
int buzzerChannel = 1;
int freq = 2000;
int freq2 = 0;
int resolution = 8;
int dutyCycle = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Name"); //이름 넣기
  pinMode(15,OUTPUT);
  digitalWrite(15, LOW);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(15, ledChannel);
  ledcAttachPin(25, buzzerChannel);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  if (SerialBT.available()>0) {
    int data1 = SerialBT.read();
    int data2 = SerialBT.read();
    int final_data = data1 + (data2 * 256);
    Serial.write(final_data);
    Serial.println(final_data);
    if (final_data >= 1000 && final_data <= 1255) {
      dutyCycle = final_data - 1000;
      ledcWrite(ledChannel, dutyCycle);
    } else if (final_data>=2000 && final_data <= 3023) {
      digitalWrite(2, HIGH);
      freq2 = final_data - 2000;
      ledcWriteTone(buzzerChannel, freq2);
      delay(20);
      digitalWrite(2, LOW);
    }
  }

}

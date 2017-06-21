/*
  A simple example to read pressure and temperature value 
  from LPS25HB sensor on X-NUCLEO-IKS01A1 board.

  Author:zhixinzhao
  Email:techzzx@foxmail.com
*/
#include <LPS25HB_IKS01A1.h>

LPS25HB lps25hb;
double pressure;
double temperature;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  if (true == lps25hb.begin())
  {
    Serial.println("start...");
  }
  else
  {
    Serial.println("Error...Please check device and wiring...");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  pressure = lps25hb.readPressure();
  Serial.print("Pressure : ");
  Serial.print(pressure);
  Serial.println(" mbar");

  temperature = lps25hb.readTemperature();
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.println();
  delay(1000);
}

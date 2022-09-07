#define BLYNK_TEMPLATE_ID "TMPLwKSMfi-m"
#define BLYNK_DEVICE_NAME "SHT3X"
#define BLYNK_AUTH_TOKEN "1omiXS21GSVeoUjQ-QMQ-38uQqPwC5dr"
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Wire.h>
#include "SHTSensor.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

SHTSensor sht;
String datasensor;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KMTek"; //nama wifi
char pass[] = "KMTek123"; //password wifi

BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}
void setup() {
  //initialize Serial Monitor
  Wire.begin();
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  Serial.println("1");
  while (!Serial);

  if (sht.init()) {
    Serial.print("init(): success\n");
  } else {
    Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x
}

void loop() {
  Blynk.run();
  timer.run();

  float Humidity = (sht.getHumidity());
  float Temperature = (sht.getTemperature());
  datasensor = String (sht.getTemperature(), 2);
  if (sht.readSample()) {
    Serial.print("SHT:\n");
    Serial.print("  Humidity: ");
    Serial.print(sht.getHumidity(), 2);
    Serial.print("\n");
    Serial.print("  Temperature :  ");
    Serial.print(sht.getTemperature(), 2);
    Serial.print("\n");

    Blynk.virtualWrite(V1, Humidity);
    Blynk.virtualWrite(V2, Temperature);
    delay(1000);

  } else {
    Serial.print("Error in readSample()\n");
  }

  delay(5000);
}

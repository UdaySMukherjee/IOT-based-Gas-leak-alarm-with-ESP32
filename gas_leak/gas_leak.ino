#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

char auth[] = "K8GUVR9IuWGezsj4PBGz1I-OhViDS5b1";

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

#define MQ2 34
#define GREEN 16
#define RED 17
int sensorValue = 0;
boolean state = false;

void setup()
{

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(MQ2, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  timer.setInterval(1000L, sendUptime);
}

void sendUptime()
{
  
  sensorValue = analogRead(MQ2);
  Blynk.virtualWrite(V1, sensorValue);
  Serial.println(sensorValue);

  if (sensorValue > 600)
  {
    Blynk.notify("Gas Detected!");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }

  else
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}

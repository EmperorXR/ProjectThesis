#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

char auth[] = "drMDVFjM7nQtrVZ3f09OR75IQ95rXqKD";
char ssid[] = "KhunC2";
char pass[] = "khunedahn";

#include <SoftwareSerial.h>
SoftwareSerial wifi(D1,D2);

int BPM = 0;
int Oxy = 0;
int Suhu = 0;

void setup() {
  WifiStatus();
  Serial.begin(115200);
  wifi.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {

 Blynk.run();
 
 wifi.write("wifi");
 
 if(wifi.available()){
  
  BPM = wifi.read();
  Serial.print("BPM = ");
  Serial.println(BPM);

  Suhu = wifi.read();
  Serial.print("Suhu = ");
  Serial.println(Suhu);

  Oxy = wifi.read();
  Serial.print("SpO2 = ");
  Serial.println(Oxy);
  
  Blynk.virtualWrite(V2, BPM);
  Blynk.virtualWrite(V1, Oxy);
  Blynk.virtualWrite(V3, Suhu);
 }
}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

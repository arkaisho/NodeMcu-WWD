/* NODEMCU OT AND WIFI LIBS */
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

/* HIVEMQ BROKER LIBS */
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

/* DHT-11 LIBS */
#include <DHT.h>
#include <DHT_U.h>

// PREFIX -> arkaisho_iot_project_
const char* proximity_sensor_topic = "arkaisho_iot_project_proximity";
const char* temperature_sensor_topic = "arkaisho_iot_project_temperature";
const char* umidity_sensor_topic = "arkaisho_iot_project_umidity";
const char* rain_sensor_topic = "arkaisho_iot_project_rain";


void setup() {
  setupSerial();
  setupWifiConfigurations();
  setupHiveMqClient();
  setupProxmitySensorPinMode();
  setupRainSensorPinMode();
  setupTemperatureUmiditySensorPinMode();
}

void setupSerial() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Iniciando dispositivo...");
}

void loop() {
  //STARTS OTA WATCHING
  ArduinoOTA.handle();
  int proximity_value = readProximitySensor();
  publishMessage(proximity_sensor_topic, String(proximity_value), true);

  int rain_value = readRainSensor();
  publishMessage(rain_sensor_topic, String(rain_value), true);

  int temperature_value = readTemperatureSensor();
  if (temperature_value > 0) {
    publishMessage(temperature_sensor_topic, String(temperature_value), true);
  }

  int umidity_value = readUmiditySensor();
  if (umidity_value > 0 && umidity_value <= 100) {
    publishMessage(umidity_sensor_topic, String(umidity_value), true);
  }
  Serial.println();

  delay(1000);
}

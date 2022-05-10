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
const char* temperature_sensor_failure_topic = "arkaisho_iot_project_temperature_failure";
const char* umidity_sensor_failure_topic = "arkaisho_iot_project_umidity_failure";

//PINOUT REFERENCE
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;

//TIME REFERENCE
unsigned long previousMillis = 0;

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

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > 2000 ) {
    previousMillis = currentMillis;
    int proximity_value = readProximitySensor();
    publishMessage(proximity_sensor_topic, String(proximity_value));

    int rain_value = readRainSensor();
    publishMessage(rain_sensor_topic, String(rain_value));

    int temperature_value = readTemperatureSensor();
    if (temperature_value > 0) {
      publishMessage(temperature_sensor_topic, String(temperature_value));
    } else {
      publishMessage(temperature_sensor_failure_topic, String(temperature_value));
    }

    int umidity_value = readUmiditySensor();
    if (umidity_value > 0 && umidity_value <= 100) {
      publishMessage(umidity_sensor_topic, String(umidity_value));
    } else {
      publishMessage(umidity_sensor_failure_topic, String(umidity_value));
    }

    Serial.println();
  }
  delay(100);
}

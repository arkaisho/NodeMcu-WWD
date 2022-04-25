/* HIVEMQ BROKER LIBS */
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

/* DHT-11 LIBS */
#include <DHT.h>
#include <DHT_U.h>

/* NODEMCU OT AND WIFI LIBS */
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

/* OTA AND WIFI CONFIGURATIONS */
const char* ssid = "";
const char* password = "";

/* HIVEMQ BROKER CONFIGURATIONS */
const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
const char* proximity_sensor_topic = "proximity";

/* RC-SR04 CONFIGURATIONS */
long duration;
float distanceCm;
#define trigPin D6
#define echoPin D5
#define SOUND_VELOCITY 0.034029 //define sound velocity in cm/uS

/* DHT-11 CONFIGURATIONS */
//#define DHTPIN 4 // pino que estamos conectado
//#define DHTTYPE DHT11 // DHT 11

/* MH-RD CONFIGURATIONS */
#define rainAnalog A0
#define rainDigital D1

/* FUNCTIONS CALL */
void setup() {
  setupSerial();
  setupWifiConfigurations();
  setupHiveMqClient();
  setupProxmitySensorPinMode();
  //  setupRainSensorPinMode();
}

void loop() {
  ArduinoOTA.handle();
  mainInteraction();
}

//MAIN FUNCION THAT RUNS AT EVERY LOOP INTERACTION
void mainInteraction() {
  //  readRainSensor();
  float distanceCm = readProximitySensor();
  publishMessage(proximity_sensor_topic,String(distanceCm),true);
  delay(200);
}

//SETUP FUNCTIONS
void setupSerial() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Iniciando firmware...");
}

void setupWifiConfigurations() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexao falhou! Reiniciando...");
    delay(5000);
    ESP.restart();
  }

  // Porta padrao do ESP8266 para OTA eh 8266 - Voce pode mudar ser quiser, mas deixe indicado!
  // ArduinoOTA.setPort(8266);

  // O Hostname padrao eh esp8266-[ChipID], mas voce pode mudar com essa funcao
  ArduinoOTA.setHostname("NodeMcu-joao");

  // Nenhuma senha eh pedida, mas voce pode dar mais seguranca pedindo uma senha pra gravar
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Inicio...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("nFim!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso: %u%%r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erro [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Autenticacao Falhou");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Falha no Inicio");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Falha na Conexao");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Falha na Recepcao");
    else if (error == OTA_END_ERROR) Serial.println("Falha no Fim");
  });
  ArduinoOTA.begin();
  Serial.println("Pronto");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
}


void setupHiveMqClient(){
  client.setServer(mqtt_server, mqtt_port);
  while(!client.connected()){
    Serial.println("Trying mqqt connection ...");
    if(client.connect("ESP8266Client",mqtt_username,mqtt_password)){
      Serial.println("Connected to broker !");
    }else{
      Serial.print("Failed to connect - ");
      Serial.println(client.state());
      delay(200);
    }
  }
}

void publishMessage(const char* topic, String payload , boolean retained){
  client.publish(topic, (byte*) payload.c_str(), 10, true);
  Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

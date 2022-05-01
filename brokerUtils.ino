/* HIVEMQ BROKER CONFIGURATIONS */
const char* mqtt_server = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setupHiveMqClient() {
  client.setServer(mqtt_server, mqtt_port);

  String clientId = "ESP8266-joao-";
  clientId += String(random(0xffff), HEX);

  while (!client.connected()) {
    Serial.println("Tentando se conectar com o servidor MQTT ...");
    //    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado !");
    } else {
      Serial.print("Falha de conexão (estado do cliente = ");
      Serial.print(client.state());
      Serial.println(")");
      delay(500);
    }
  }
}

void publishMessage(const char* topic, String payload , boolean retained) {
  client.publish(topic, payload.c_str());
  //  Serial.println("Message publised [" + String(topic) + "]: " + payload);
}

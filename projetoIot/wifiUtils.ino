/* OTA AND WIFI CONFIGURATIONS */
const char* ssid = "h498-2h5d-23q2";
const char* password = "besourinho";


void setupWifiConfigurations() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print("Falha de conexão: ");
    Serial.println(WiFi.waitForConnectResult());
    Serial.println("Reiniciando...");
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
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
}

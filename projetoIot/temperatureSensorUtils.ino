/* DHT-11 CONFIGURATIONS */
#define temperaturePin D2
#define DHTTYPE DHT11

DHT dht(temperaturePin, DHTTYPE);

int readTemperatureSensor() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    return 0;
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print("\t");
    return (int)temperature;
  }
}

int readUmiditySensor() {
  float  umidity = dht.readHumidity();
  if (isnan(umidity)) {
    return 0;
  } else {
    Serial.print("Umidade: ");
    Serial.print(umidity);
    Serial.print("\t");
    return (int)umidity;
  }
}

void setupTemperatureUmiditySensorPinMode() {
}

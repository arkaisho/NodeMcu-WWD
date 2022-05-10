/* ADAFRUIT BROKER CONFIGURATIONS */
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "arkaisho"
#define AIO_KEY         "aio_GVqD43WbrfWNsMXuor0KoSZDzfqn"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// ADAFRUIT TOPICS
Adafruit_MQTT_Publish distanceFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/distance-feed");

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

void publishDistance(int value){
  distanceFeed.publish(value);
}

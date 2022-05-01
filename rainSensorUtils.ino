/* MH-RD CONFIGURATIONS */
#define rainAnalog A0
#define rainDigital D1

int readRainSensor() {
  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);

  Serial.print("Chuva: ");
  Serial.print(rainAnalogVal);
  Serial.print("\t");
  return (int)rainAnalogVal;
}

void setupRainSensorPinMode() {
  pinMode(rainDigital, INPUT);
  pinMode(rainAnalog , INPUT);
}

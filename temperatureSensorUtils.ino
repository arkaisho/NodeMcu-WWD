
void readTemperatureSensor() {
  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);

  Serial.print(rainAnalogVal);
  Serial.print("\t");
  Serial.println(rainDigitalVal);
}

void setupTemperaturePinMode() {
  pinMode(rainDigital, INPUT);
  pinMode(rainAnalog , INPUT);
}

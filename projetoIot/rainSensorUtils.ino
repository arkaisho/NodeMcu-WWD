/* MH-RD CONFIGURATIONS */
#define rainAnalog A0
//#define rainDigital D1

int readRainSensor() {
  int readedValue = analogRead(rainAnalog);
  //  int rainDigitalVal = digitalRead(rainDigital);

  Serial.print("Chuva: ");
  Serial.print(readedValue);
  Serial.print("\t");
  return (int)readedValue;
}

void setupRainSensorPinMode() {
  pinMode(rainAnalog , INPUT);
  //  pinMode(rainDigital , INPUT);
}

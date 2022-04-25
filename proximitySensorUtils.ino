
float readProximitySensor() {
  //SHOOT PULSE
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //STOP PULSE

  //READ SOUND TRAVEL TIME IN MICROSECONDS
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;


  Serial.print("Distance(cm):");
  Serial.println(distanceCm);
  return distanceCm;
}

void setupProxmitySensorPinMode() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

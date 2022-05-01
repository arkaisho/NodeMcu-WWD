/* RC-SR04 CONFIGURATIONS */
long duration;
float distanceCm;
#define trigPin D6
#define echoPin D5
#define SOUND_VELOCITY 0.034029 //define sound velocity in cm/uS

int readProximitySensor() {
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


  Serial.print("Distância: ");
  Serial.print(distanceCm);
  Serial.print("\t");
  return (int)distanceCm;
}

void setupProxmitySensorPinMode() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

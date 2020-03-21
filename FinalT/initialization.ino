//function to synchronize transmitter and receiver
void initialization(int pin) {
  digitalWrite(pin, HIGH);
  sleep((unsigned long)200000);
  digitalWrite(pin, LOW);
  sleep((unsigned long)200000);
  digitalWrite(pin, HIGH);
  sleep((unsigned long)200000);
  digitalWrite(pin, LOW);
  sleep((unsigned long)200000);
}

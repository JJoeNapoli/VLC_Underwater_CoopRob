//function to convert "0"s and "1"s to Morse code
void bitToMorse(int value, int pin) {
  if (value == 0) {
    digitalWrite(pin, HIGH);
    sleep((unsigned long)wake_0);
    digitalWrite(pin, LOW);
    sleep((unsigned long)sleep_0);
  } else if (value == 1) {
    digitalWrite(pin, HIGH);
    sleep((unsigned long)wake_1);
    digitalWrite(pin, LOW);
    sleep((unsigned long)sleep_1);
  }
}

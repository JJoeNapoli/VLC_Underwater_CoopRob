//function to sleep more precisely
void sleep(unsigned long tim) {
  if (tim > 16000) {
    int temp = tim / 1000;
    delay(temp);
    delayMicroseconds(tim - (temp * 1000));
  } else {
    delayMicroseconds(tim);
  }
}

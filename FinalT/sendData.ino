//function to send the data
void sendData(int my_data[], int my_size, int pin) {
  int my_bit = 0;
  //convert from int to bit
  for (int i = 0; i < my_size; i++) {
    for (int j = 7; j >= 0; j--) {
      my_bit = bitRead(my_data[i], j);
      bitToMorse(my_bit, pin);
    }
    sleep((unsigned long)sample);
  }
  //end message;
  digitalWrite(laser, HIGH);
  sleep((unsigned long)sample * 5);
  digitalWrite(laser, LOW);
  sleep((unsigned long)sample * 30);
}

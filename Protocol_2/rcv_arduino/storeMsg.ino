//function to store the messages
void storeMsg(int pin, int *p) {

  String my_msg_bit = "";
  int my_int;
  int count = 0;
  int flag = 0;
  int flag1 = 0;

  while (1) {
    //clear the string
    my_msg_bit = "";
    //for 8 bit try to convert from Morse to bit
    for (int i = 0; i < 8; i++) {
      //take the time
      t1 = millis();
      //while it is not receiving data
      while (digitalRead(rcv) == 0 ) {
        //take the time
        t2 = millis();
        dt1 = t2 - t1;
        //if the time is > 3s exit
        if (dt1 > 3000) {
          flag = 1;
          flag1 = 1;
          break;
        }
      }
      if (flag1 == 1) {
        break;
      }
      t1 = micros();
      while (digitalRead(rcv) == 1 ) {}
      t2 = micros();
      dt1 = t2 - t1;
      //detect if it is a 0 or a 1
      if (dt1 < wake_0 + error_delay && dt1 > wake_0 - error_delay) {
        my_msg_bit = my_msg_bit + "0";
      } else if (dt1 < wake_1 + error_delay && dt1 > wake_1 - error_delay) {
        my_msg_bit = my_msg_bit + "1";
      } else if (dt1 > wake_1 + error_delay) { //breakpoint-end message
        flag = 1;
        Serial.print("received\n");
        break;
      }
    }
    if (flag == 1) {
      break;
    }
    //every 8 bit
    //convert the Byte (=8 bits) to an int
    my_int = bitToInt(my_msg_bit);
    //store the value
    p[count] = my_int;

    //increase the counter
    count ++;
    //if a breakpoint has been received

  }
}

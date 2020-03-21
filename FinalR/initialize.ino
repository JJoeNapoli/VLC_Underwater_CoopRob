//function to synchronize transmitter and receiver
void initialize() { 
  
  while (1) {
    //this is the way to keep the two codes synchronised
    while (digitalRead(rcv) == 0 ) {} 

    t1 = micros();
    while (digitalRead(rcv) == 1 ) {}
    t2 = micros();
    dt1 = t2 - t1; //laser lighted 1st time
    if (dt1 < 230000 && dt1 > 170000) {
      while (digitalRead(rcv) == 0 ) {}
      t3 = micros();
      while (digitalRead(rcv) == 1 ) {}
      t4 = micros();
      dt2 = t3 - t2; //laser off
      dt3 = t4 - t3; //laser lighted 2nd time
      if (dt2 < 203000 && dt2 > 197000) {
        if (dt3 < 203000 && dt3 > 197000) {
          //Serial.println("finish initialize-------");
          break;
        }
      }
    }
  }
}

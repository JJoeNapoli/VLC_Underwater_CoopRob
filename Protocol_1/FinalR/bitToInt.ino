//function to convert from 8 bits String to Int
int bitToInt(String str) { //needs a 8 char String()
  int numb = 0;
  int add_ = 0;
  String substr;
  int substr_int;
  //make the convertion
  for (int i = 0; i < 8; i++) {
    substr = str.substring(i, i + 1);
    substr_int = substr.toInt();
    add_ = substr_int * bit(7 - i);
    numb = numb + add_;
  }
  return numb;
}

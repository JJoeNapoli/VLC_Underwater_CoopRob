//Giovanni Napoli's Master Thesis

#define BAUD 115200
#define rcv 12
//set the parameters
//frequency
#define freq 2500 //Hz

//needed global variables
int type_msg[] = {0, 0, 0};
int dimension[] = {0, 0};

//time global variables
unsigned long t1 = 0;
unsigned long t2 = 0;
unsigned long t3 = 0;
unsigned long t4 = 0;
unsigned long dt1 = 0;
unsigned long dt2 = 0;
unsigned long dt3 = 0;
double sample;
int wake_0 = 0;
int wake_1 = 0;
int error_delay = 0;

//references for the used functions
int bitToInt(String );
void checkErrors(int *, int , int *, int );
void initialize();
void sleep(unsigned long );
void storeMsg(int , int *);


///////////////////setup///////////////////
void setup() {
  Serial.begin(BAUD);
  while (!Serial) {} //waits for the Serial communication
  pinMode(rcv, INPUT);

  //computes the time constants
  sample = 1000000 / freq;
  wake_0 = sample * 0.3;
  wake_1 = sample * 0.7;
  error_delay = sample * 0.13;

  delay(500);
}

///////////////////loop///////////////////
void loop() {
  delay(500);
  //synchronise the two arduino codes
  initialize();

  //store type of the message
  storeMsg(rcv, type_msg);
  //store dimension of the message
  storeMsg(rcv, dimension);
  //computes the conversion
  int n = (dimension[0] * 250) + dimension[1];
  
  //create the array of the right dimension
  int data [n];
  //waits that the array is created
  sleep((unsigned long) sample * 20);
  //store the data
  storeMsg(rcv, data);

  //now starts the communication 
  //via serial port to the PC
  Serial.print("ready\n");

  //send the type of the message
  Serial.print(type_msg[0], DEC);
  Serial.print(" ");
  Serial.print(type_msg[1], DEC);
  Serial.print(" ");
  Serial.println(type_msg[2], DEC);

//send the dimensions
  Serial.print(dimension[0], DEC);
  Serial.print(" ");
  Serial.print(dimension[1], DEC);
  Serial.print(" ");
  Serial.println(dimension[0] * 250 + dimension[1], DEC);

  if (type_msg[0] == 0) { //for strings
    //convert form array to String
    char msg_text[n];

    for (int i = 0; i < n; i++) {
      msg_text[i] = (char)data[i];
      Serial.print(msg_text[i]);
      //Serial.print(data[i]);
      //Serial.print(" ");
    }
    Serial.println();

  } else if (type_msg[0] == 1) { //for images
    //send the values via serial port
    for (int i = 0; i < n; i++) {
      Serial.print(data[i], DEC);
      Serial.print("\n");
    }

  }
  //sleep a certain amount of time
  sleep((unsigned long)sample * 10);
}

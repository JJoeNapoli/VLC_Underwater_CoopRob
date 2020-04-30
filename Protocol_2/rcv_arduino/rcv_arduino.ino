//Giovanni Napoli's Master Thesis

#define BAUD 115200
#define rcv 12
//set the parameters
//frequency
#define freq 2500 //Hz
// 50*50 picture
#define n_image 2500 //Bytes 

#define n_info 5 //number of elements of "info" 

//needed global variables
int info[n_info];  //the information could be 5
int image [n_image]; //create the array of the right dimension

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
  int randint = random(10);
  //waits that the array is created
  sleep((unsigned long) sample * 20);

  if (randint < 7) { //info
    //now starts the communication
    //via serial port to the PC
    Serial.print("info\n");

    //store the info
    storeMsg(rcv, info);
  }
  else if(randint>=7){
    //now starts the communication
    //via serial port to the PC
    Serial.print("image\n");

    //store the image
    storeMsg(rcv, image);
  }
  //sleep a certain amount of time
  sleep((unsigned long)sample * 10);
}

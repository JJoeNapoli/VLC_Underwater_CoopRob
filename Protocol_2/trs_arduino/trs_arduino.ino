//Giovanni Napoli's Master Thesis//

#define BAUD 115200
#define laser 12
//set the parameters
//frequency
#define freq 2500 //Hz
// 50*50 picture
#define n_image 2500 //Bytes 
#define n_info 5 //elements in "info"

//needed global variables
int info[n_info];
int image[n_image];


//time global variables
unsigned long t1 = 0;
unsigned long t2 = 0;
int sample;
int wake_0 = 0;
int wake_1 = 0;
int sleep_0 = 0;
int sleep_1 = 0;


//references for the used functions
void initialization(int);
void bitToMorse(int , int );
void sendData(int [], int , int );
void sleep(unsigned long );
void here();


///////////////////setup///////////////////
void setup() {
  Serial.begin(BAUD);
  while (!Serial) {} //waits for the Serial communication
  pinMode(laser, OUTPUT);
  digitalWrite(laser, LOW);

  //computes the time constants
  sample = 1000000 / freq;
  wake_0 = sample * 0.3;
  wake_1 = sample * 0.7;
  sleep_0 = sample - wake_0;
  sleep_1 = sample - wake_1;

  delay(500);
}


///////////////////loop///////////////////
void loop() {
  //clear Serial communication
  while (Serial.available() > 0) {
    char type = Serial.read();
  }
  //wait for new incoming messsages
  while (Serial.available() == 0) {
    Serial.println("e");
    delay(50);
  }
  delay(50);
  //choose the type: info or image
  //read from the serial port

  char type = Serial.read();
  int count;

  if (type == 'A') {  //info
    count = 0;
    while (count < n_info) {
      if (Serial.available() > 0) {
        info[count] = Serial.read();
        count++;
      }
    }
    //send the "info"
    sendData(info, n_info, laser);
    Serial.print("finished\n");

  } else if (type == 'B') { //image
    count = 0;
    while (count < n_image) {
      if (Serial.available() > 0) {
        image[count] = Serial.read();
        count++;
      }
    }
    //send the "image"
    sendData(image, n_image, laser);
    Serial.print("finished\n");
  }

sleep((unsigned long)sample * 50);
}

void here() {
  digitalWrite(laser, HIGH);
  delay(500);
  digitalWrite(laser, LOW);
  delay(500);
}

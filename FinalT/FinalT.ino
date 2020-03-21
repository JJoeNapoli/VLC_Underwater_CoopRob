//Giovanni Napoli's Master Thesis//

#define BAUD 115200
#define laser 12
//set the parameters
//frequency
#define freq 2500 //Hz
//global flag for choosing the type of message
//0 for string and 1 for pictures
#define flag_type_msg 1


//needed global variables
int *data;
int size_array[] = {0, 0};
int num_elements = 0;
int type_msg[3];

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
  //clean the serial port
  while (Serial.available() > 0)
    char useless = Serial.read();
  //create "my_dim" array
  int n = 2;
  int my_dim[n];
  //write "start" to synchronize with the PC
  while (Serial.available() == 0) {
    Serial.print("start\n");
    Serial.flush();
    delay(100);
  }
  //clear the serial port
  char useless = Serial.read();

  //read from the serial port
  int count = 0;
  while (count < n) {
    if (Serial.available() > 0) {
      my_dim[count] = Serial.read();
      count++;
    }
  }

  //correct the sizes
  my_dim[0] = my_dim[0] - 1;
  my_dim[1] = my_dim[1] - 1;

  //write to the serial port for confirmation
  Serial.print(my_dim[0], DEC);
  Serial.print(my_dim[1], DEC);
  Serial.write("\n");

  //create "my_data" array
  //for big dimensions uses this conversion: num_elements = 255*x + y
  n = ((my_dim[0]) * 250) + my_dim[1];
  int my_data[n];
  delay(20);

  //read from the serial port
  count = 0;
  while (count < n) {
    if (Serial.available() > 0) {
      my_data[count] = Serial.read();
      count++;
    }
  }

  //first control to know if the size was correct
  Serial.print(n);
  Serial.print("\n");
  //  checkErrors(my_data,n,real_data,sizeof(real_data));

  delay(200);

  ////////now send via laser

  if (flag_type_msg == 0) {//if we want to send a string
    //set the first element of type_msg to 0
    //NOT USED BY NOW
    /*type_msg[0] = 0;

      //computes the number of elements that must be sent
      num_elements = (sizeof(my_text) / sizeof(my_text[0]));
      //for big dimensions uses this conversion: num_elements = 255*x + y
      size_array[0] = num_elements / 255; //x
      size_array[1] = num_elements - size_array[0] * 255; //y

      //create an array of int of the same size of the array that must be sent
      int my_text_int[num_elements];
      //copy the relative integers on the int array
      for (int j = 0; j < num_elements; j++) {
      my_text_int[j] = (int)my_text[j];
      //some controls
      Serial.print(my_text[j]);
      Serial.print(my_text_int[j]);
      Serial.print(" ");
      }
      Serial.println();

      //set the pointer to int array
      data = &my_text_int[0];

      //some controls
      Serial.print("size ");
      Serial.print(num_elements);
      Serial.print(" divided in: 255 * ");
      Serial.print(size_array[0]);
      Serial.print(" + ");
      Serial.println(size_array[1]);
      Serial.println("start");
      delay(3000);

      //take the time
      t1 = millis();

      //start the initialization
      initialization(laser);
      Serial.println("finish initialization");
      sleep((unsigned long)sample * 50);

      //send the "type" part
      Serial.print("sending message type... ");
      sendData(type_msg, 1, laser);
      Serial.println("done");

      //send the "dimension" part
      Serial.print("sending message dimension... ");
      sleep((unsigned long)sample * 20);
      sendData(size_array, 2, laser);
      Serial.println("done");

      //send the "data"
      Serial.print("sending message... ");
      sleep((unsigned long)sample * 50);
      sendData(data, num_elements, laser);
      Serial.println("done");

      //take the time
      t2 = millis();
      sleep((unsigned long)sample * 10);
      Serial.print("time spent: ");
      Serial.print((float)(t2 - t1) / 1000);
      Serial.println(" s");

      Serial.println("------------------------------------------------------");
    */



  } else if (flag_type_msg == 1) { //if we want to send an image
    //set the first element of type_msg to 1
    //and the last two as the image sizes
    type_msg[0] = 1;
    //BY NOW I KEEP THE SAME IMAGE SIZES BECAUSE THEY ARE USELESS
    type_msg[1] = 21;
    type_msg[2] = 28;


    delay(500);

    //take the time
    t1 = millis();

    //start the initialization
    initialization(laser);
    sleep((unsigned long)sample * 50);

    //send the "type" part
    sendData(type_msg, 3, laser);

    //send the "dimension" part
    sleep((unsigned long)sample * 20);
    sendData(my_dim, 2, laser);

    //send the "data"
    sleep((unsigned long)sample * 50);
    sendData(my_data, n, laser);


    //take the time
    t2 = millis();
    //sleep((unsigned long)sample * 100);
    delay(4000);
  }
}

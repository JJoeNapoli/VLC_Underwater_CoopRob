#!/usr/bin/env python3

import serial
import time
import numpy as np


#######################################
def main():
    t1 = time.time()
    serialPort = serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=10)

    # waits some time
    time.sleep(.05)

    myfold = "array_image_21x28_/"
    # myfold = "array_image_26x34_/"
    # myfold = "array_image_35x46_/"
    # myfold = "array_image_41x55_/"
    # myfold = "array_image_52x68_/"
    # myfold = "array_image_69x91_/"
    # myfold = "array_image_103x136_/"

    for i in range(1, 101):
        fullname = myfold+"image_num_"+str(i)+".txt"
        f = open(fullname, "r")
        print(fullname)
        while f.mode != "r":
            continue

        data = f.read().split(',')
        f.close()
        data = list(map(int, data))

        print(len(data))

        # same convertion as the arduino program
        my_size = [(len(data)//250)+1, (len(data) % 250)+1]
        print(my_size)

        correct_size = str(my_size[0]-1)+str(my_size[1]-1)+"\n"

        rcv = ""
        while rcv != "start\n":
            rcv = serialPort.readline().decode('ascii')
            print(rcv)
        if rcv == "start\n":
            print("-----started")

            serialPort.write(bytearray('A', 'ascii'))
            print("-----synchronized")
            while 1:
                serialPort.write(bytearray(my_size))
                print("-----sent my_size")

                time.sleep(0.1)

                my_received = serialPort.readline().decode('ascii')
                print(my_received)

                if my_received == correct_size:
                    # serialPort.write(bytearray("ok","ascii"))
                    break
                else:
                    # serialPort.write(bytearray("no","ascii"))
                    continue

            time.sleep(0.1)
            serialPort.write(bytearray(data))
            print("-----sent data")

            my_received = serialPort.readline()  # .decode('ascii')
            print(my_received)
            time.sleep(2)
    t2 = time.time()
    print("time elapsed: " + str(t2-t1))


if __name__ == "__main__":
    main()


# values of time delay that work : 1 2/1 1/.5 .5/.2 .2

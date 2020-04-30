#!/usr/bin/env python3

import serial
import time
import numpy as np


#######################################
def main():
    t1 = time.time()
    serialPort = serial.Serial('/dev/ttyUSB2', baudrate=115200, timeout=10)

    # waits some time
    time.sleep(.05)

    myfold = "array_image_21x28_/"
    # myfold = "array_image_26x34_/"
    # myfold = "array_image_35x46_/"
    # myfold = "array_image_41x55_/"
    # myfold = "array_image_52x68_/"
    # myfold = "array_image_69x91_/"
    # myfold = "array_image_103x136_/"
    count_tot=0
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

        rcv = ""
        type_msg = ""
        dim_msg = ""
        data_msg = ""
        count=0
        while rcv != "ready\n":
            rcv = serialPort.readline().decode('ascii')
            print("not ready but: " + rcv)
        if rcv == "ready\n":
            print("-----ready")

            type_msg = serialPort.readline().decode('ascii')
            print("-----get type_msg:\n" + type_msg)
            dim_msg = serialPort.readline().decode('ascii')
            print("-----get dim_msg:\n" + dim_msg)


            for i in range(0,len(data)):
                rcv=serialPort.readline().decode('ascii')
                data_msg+=rcv
                
                if data[i]!=int(rcv):
                    count +=1
                
            print("-----get data_msg")
            print("number of errors: " + str(count))
            print()
            if count!=0:
                count_tot+=1
            
            time.sleep(0.1)

            

            #print(data_msg)
            time.sleep(2)
    t2 = time.time()
    print("time elapsed: " + str(t2-t1))

    print("number of broken images:------->" + str(count_tot))


if __name__ == "__main__":
    main()


# values of time delay that work : 1 2/1 1/.5 .5/.2 .2

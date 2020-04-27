#!/usr/bin/env python3

import serial
import time
import numpy as np
import cv2
import random


def take_image(dimension):
    video = cv2.VideoCapture(0)
    check = False
    while check == False:
        check, frame = video.read()
        time.sleep(.05)
    video.release()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    img = cv2.resize(gray, (dimension, dimension))
    
    pic=convert_image(img,dimension)
    return pic


def show_image(img):
    cv2.imshow("Capturing", img)

    slptm = 2
    key = cv2.waitKey(slptm*1000)


def show_video():
    global video

    while 1:
        check, frame = video.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        img = cv2.resize(gray, (50, 50))
        cv2.imshow("Capturing", img)
        key = cv2.waitKey(3000)
        print("sono andato avanti")
        if key == ord('q'):
            break


def send_image(serialPort, img, dimension):
    for i in range(dimension):
        for j in range(dimension):
            if img[i, j] != 0:
                serialPort.write(bytearray(img[i, j]))
            else:
                serialPort.write(bytes(1))


def convert_image(img, dimension):
    img_list = []
    for i in range(dimension):
        for j in range(dimension):
            if img[i, j] != 0:
                img_list.append(img[i, j])
            else:
                img_list.append(1)
    return img_list


def take_info():
    randomlist = []
    for i in range(5):
        n = random.randint(1, 255)
        randomlist.append(n)
    # print(randomlist)
    return randomlist


def testgio():
    ran = take_info()
    print(type(ran))
    print(ran)
    pic = take_image(5)
    print(pic)
    print(type(pic))
    

def main1():
    serialRCV = serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=10)
    serialTRS = serial.Serial('/dev/ttyUSB2', baudrate=115200, timeout=10)

    dimension = 50

    # waits some time
    time.sleep(.5)

    rcv = ""
    count = 0
    countA=0
    countB=0
    count_succeed=0
    while 1:
        time.sleep(0.5)
        rcv = serialRCV.readline().decode('ascii')
        if rcv == "info\n":
            count += 1

            countA+=1
            string=rcv+" "+str(countA)
            print(string)
            serialTRS.write(bytearray('A', 'ascii'))
            time.sleep(0.5)
            randomList = take_info()
            print(randomList)
            serialTRS.write(bytearray(randomList))
            while 1:
                trs = ""
                trs = serialTRS.readline().decode('ascii')
                if trs == "finished\n":
                    print("---" + trs)
                    break

        elif rcv == "image\n":
            count += 1

            countB+=1
            string=rcv+" "+str(countB)
            print(string)
            serialTRS.write(bytearray('B', 'ascii'))
            time.sleep(0.5)

            img = take_image(dimension)
            
            # send_image(serialTRS, img, dimension)
            serialTRS.write(bytearray(img))
            while 1:
                trs = ""
                trs = serialTRS.readline().decode('ascii')
                if trs == "finished\n":
                    print("---" + trs)
                    break
        elif rcv=="received\n":
            count_succeed+=1
            print("++++++++++++++++++++++++++++++++++++"+rcv)


        else:
            print("I've not received a value string, I've received: " + rcv)
        # time.sleep(100)
        # break


        
        if count >0:
            print("the ratio is: " + str(count_succeed/count))
        print("------------------------------")

if __name__ == "__main__":
    main1()
    # testgio()

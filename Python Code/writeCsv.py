from time import sleep
import serial

ser = serial.Serial("COM3", 38400)
ser.flushInput()

HEADERS = "time,direction,speed,gX,gY,gZ,aX,aY,aZ\n"

with open("./data.csv", "w") as f:
        f.write(HEADERS)

while (True):
    s = str(ser.readline())[2:-3]
    print(s)
    with open("./data.csv", "a") as f:
        f.write(s)
        f.write("\n")
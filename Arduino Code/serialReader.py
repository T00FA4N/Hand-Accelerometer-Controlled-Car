from time import sleep
from threading import Thread

import serial

# The Serial Port the Arduino is connected to
SERIAL_PORT = "COM3"

def __retryConnection():
    sleep(5)
    try:
        global ser
        ser = serial.Serial(SERIAL_PORT)
        print(f"Connected to {SERIAL_PORT}")
        return True
    except:
        return False

# All the columns in the CSV file
HEADERS = "time,direction,gX,gY,gZ,aX,aY,aZ\n"

# Whether the program is able to connect to the serial port or not
portBusy = False

try:
    ser = serial.Serial(SERIAL_PORT)
    print(f"Connected to {SERIAL_PORT}")
except:
    connected = False
    for i in range(3):
        print(f"Error connecting to {SERIAL_PORT}, automatic retry ({i + 1} / 3)...")
        if __retryConnection():
            connected = True
        if not connected:
            print(
                "Error reading from serial port!\nMake sure port "
                + SERIAL_PORT
                + " is not busy, and that the Arduino IDE and Serial Monitor"
                "/Plotter are closed."
            )
            portBusy = True

def init():
    with open("./data.csv", "w") as f:
        f.write(HEADERS)
        f.close()
    th = Thread(target=readSerial)
    th.start()

def readSerial():
    while True:
        if portBusy:
            return
        # Pick up the bytes associated with the information
        data = str(ser.readline())[2:-1].replace("\\r\\n","")
        
        with open("./data.csv", "a") as f:
            f.write(data + "\n")
import serial
from time import sleep
import json
import threading

def sendJson(serial, filename):
    with open(filename) as jsonFile:
        jsonObject = json.load(jsonFile)
        #Process data before sending on serial
        serial.write(bytes(json.dumps(jsonObject), 'utf-8'))

def read_data(serialCom):
    while serialCom.is_open:
        #Get JSON from serial
        print(str(serialCom.readline(), 'utf-8'))

if __name__ == '__main__':
    serialCom = serial.Serial("COM6", 9600)
    readThread = threading.Thread(target=read_data, kwargs={"serialCom" : serialCom})
    readThread.start()

    while serialCom.is_open:
        cmd = str(input("$>"))
        if cmd.startswith("exec "):
            sendJson(serialCom, cmd[5:])
            sleep(2)
           
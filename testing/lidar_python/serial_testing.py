# send a list of bytes over serial

import serial
import time

#create serial object
ser = serial.Serial('Com6', 115200, timeout=1)

def send_bytes(ser, byte_list):
    for byte in byte_list:
        ser.write(byte)
        time.sleep(0.1)
    # read from serial
    print(ser.readline())

bytes = ["0xA5", '\x00\x00\x00\x00\x00']
#encode list as bytes
bytes = [byte.encode() for byte in bytes]

send_bytes(ser, bytes)
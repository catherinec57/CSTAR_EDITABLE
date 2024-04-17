import serial
import time
import matplotlib.pyplot as plt
import numpy as np

# Replace 'COMx' with the COM port assigned to ESP32test
port = 'COM4'  
baudrate = 115200  # Set the baud rate, 9600 is the default for the ESP32

try:
    # repeatedly try openign serial port until it is successful
    while True:
        try:
            # Opening the serial port
            ser = serial.Serial(port, baudrate, timeout=1)
            print(f"Connected to {ser.name}")
            break
        except serial.SerialException as e:
            print(f"Error: {e}")
            time.sleep(0.2)
    # Writing data to the Bluetooth device
    ser.write(b'Hello\n')
    
    # Reading data from the Bluetooth device
    while True:  # While there is data waiting to be read
        # if theres data to be read, print it
        # check if there is serial data
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').rstrip()
            print(f"Received: {data}")

        # take the user input and send it to the device
        user_input = input("Enter a command: ")
        ser.write(user_input.encode())
        
        # if user enters Ctrl+C, the program will stop 
        try:
            pass
        except KeyboardInterrupt:
            break
    
    # Closing the serial connection
    ser.close()


except serial.SerialException as e:
    print(f"Error: {e}")





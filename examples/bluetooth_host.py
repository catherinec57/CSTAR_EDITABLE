import serial
import time

# Replace 'COMx' with the COM port assigned to ESP32test
port = 'COM5'  
baudrate = 9600  # Set the baud rate, 9600 is the default for the ESP32

try:
    # Opening the serial port
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Connected to {ser.name}")

    # Writing data to the Bluetooth device
    ser.write(b'Hello\n')
    
    # Reading data from the Bluetooth device
    while True:  # While there is data waiting to be read
        data = ser.readline().decode('utf-8').rstrip()
        print(f"Received: {data}")
        
        # if user enters Ctrl+C, the program will stop 
        try:
            pass
        except KeyboardInterrupt:
            break
    
    # Closing the serial connection
    ser.close()

except serial.SerialException as e:
    print(f"Error: {e}")
import serial
import time
import matplotlib.pyplot as plt
import numpy as np

# Replace 'COMx' with the COM port assigned to ESP32test
port = 'COM5'  
baudrate = 115200  # Set the baud rate, 9600 is the default for the ESP32

try:
    # Opening the serial port
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Connected to {ser.name}")

    # Writing data to the Bluetooth device
    ser.write(b'Hello\n')
    print('hi')
    
    # Reading data from the Bluetooth device
    while True:  # While there is data waiting to be read
        data = ser.readline().decode('utf-8').rstrip()
        print(f"Received: {data}")

        numbers_list = [int(num_str) for num_str in data.split(",") if num_str.strip()]
        print(numbers_list)
        # plt.plot(numbers_list)

        if numbers_list:
            sample_rate = 2000
            time = np.arange(len(numbers_list)) / sample_rate

            # Plotting the sine wave
            plt.plot(time, numbers_list)

            # Adding labels and title to the plot
            plt.xlabel('Time (seconds)')
            plt.ylabel('Amplitude')
            plt.title('Sine Wave Plot')

            # Display the plot
            plt.show()
        else:
            print("The list is empty. Nothing to plot.")
        
        # if user enters Ctrl+C, the program will stop 
        try:
            pass
        except KeyboardInterrupt:
            break
    
    # Closing the serial connection
    ser.close()


except serial.SerialException as e:
    print(f"Error: {e}")





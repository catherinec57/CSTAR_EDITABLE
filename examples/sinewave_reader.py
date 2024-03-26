import serial
import matplotlib.pyplot as plt

# Configure the serial port
ser = serial.Serial('COMX', 9600)  # Replace 'COMX' with your Arduino's serial port

# Read data from Arduino
data = ser.readline().decode().strip()
samples = list(map(int, data.split(',')))

# Plot the received sine wave
plt.plot(samples)
plt.xlabel('Sample Index')
plt.ylabel('Amplitude')
plt.title('Received Sine Wave')
plt.show()

# Close the serial port
ser.close()

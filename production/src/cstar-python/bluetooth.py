# class for Bluetooth communication to the Robot!

import serial
import time
import multiprocessing
import numpy as np

class CstarBluetooth():
    def __init__(
            self, port: int, 
            command_queue: multiprocessing.Queue, 
            audio_pos_queue: multiprocessing.Queue, ):
        try:
            # self.ser = serial.Serial(port, 115200, timeout=1)
            self.port = port
        except serial.SerialException as e:
            raise e
        self.command_queue = command_queue
        self.audio_pos_queue = audio_pos_queue

    # add any other functions necessary here
        
    def main(self):
        # function to run on loop to send and receive data, everything that needs to happen with Bluetooth should be called here
        port = 'COM4'  
        baudrate = 115200
        while True:
            # print("running Bluetooth loop")
            ser = serial.Serial(port, baudrate, timeout=1)
            ser.write(b'running Bluetooth loop')
            print(f"running Bluetooth loop")
            # if anything in queue, send command
            if not self.command_queue.empty():
                # should be changed to send command and not print
                print(self.command_queue.get())

            # get audio data, send to queue for processing
            
            # for now, lets some random noise as np.int16 array
            self.audio_data = np.random.randint(-32768, 32767, size=44100, dtype=np.int16)
            # print(self.audio_data)
            #generate random position
            self.position = (np.random.randint(0, 20), np.random.randint(0, 20))
            self.audio_pos_queue.put((self.position, self.audio_data)) # send it over to the audio processor

    #destructor
    def __del__(self):
        # close the serial port
        # self.ser.close()
        pass

if __name__ == "__main__":
    # code to test this function if not runnign the main loop
    pass
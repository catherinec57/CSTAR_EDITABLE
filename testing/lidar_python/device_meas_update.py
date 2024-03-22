import argparse
from os import path
from rplidar import RPLidar

BAUDRATE = 115200
TIMEOUT = 1

def process_data(angle, distance):
    # Add your data processing logic here
    return angle, distance

def save_data_to_file(data):
    # Add code to save data to a file
    pass

def run(device):
    if path.exists(device):
        lidar = RPLidar(port=device, baudrate=BAUDRATE, timeout=TIMEOUT)
        try:
            for val in lidar.iter_measures():
                if val[3] != 0:
                    angle, distance = process_data(val[2], val[3])
                    print(f"Angle: {angle}, Distance: {distance} millimeters")
                    # Optionally, save data to a file
                    # save_data_to_file((angle, distance))
        except KeyboardInterrupt:
            lidar.stop()
            lidar.stop_motor()
            lidar.disconnect()
    else:
        print(f'[Error] Could not find device: {device}')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='./device_calibration.py', description='rplidar calibration', epilog='The author assumes no liability for any damage caused by use.')
    parser.add_argument('device', help="device path", type=str)
    args = parser.parse_args()
    run(args.device)


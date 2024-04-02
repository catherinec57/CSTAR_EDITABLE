import argparse
import serial
import struct
import time
import sys

SYNC_BYTE = b'\xA5'
SYNC_BYTE2 = b'\x5A'

GET_INFO_BYTE = b'\x50'
GET_HEALTH_BYTE = b'\x52'

STOP_BYTE = b'\x25'
RESET_BYTE = b'\x40'

SCAN_NORMAL_BYTE = b'\x20'
SCAN_FORCE_BYTE = b'\x21'
SCAN_EXPRESS_BYTE = b'\x82'

# Constants for data processing
DESCRIPTOR_LEN = 7
INFO_LEN = 20
HEALTH_LEN = 3
INFO_TYPE = 4
HEALTH_TYPE = 6

# Serial port settings
BAUDRATE = 115200
TIMEOUT = 1

def send_command(ser, cmd):
    ser.write(SYNC_BYTE + cmd)

def read_descriptor(ser):
    descriptor = ser.read(DESCRIPTOR_LEN)
    if len(descriptor) != DESCRIPTOR_LEN or not descriptor.startswith(SYNC_BYTE + SYNC_BYTE2):
        raise Exception('Invalid descriptor received')
    return descriptor

def read_response(ser, dsize):
    while ser.in_waiting < dsize:
        time.sleep(0.001)
    return ser.read(dsize)

def get_info(ser):
    response = send_command(ser, GET_INFO_BYTE)
    print("Response for get_info:", response)
    return response


def get_health(ser):
    response = send_command(ser, GET_HEALTH_BYTE)
    print("Response for get_health:", response)
    return response
def process_data(response):
    # Define a helper function to convert bytes to integer
    def _b2i(byte):
        return byte if sys.version_info.major == 3 else ord(byte)

    # Extracting data from the response bytes
    byte0 = _b2i(response[0])
    byte1 = _b2i(response[1])
    byte2 = _b2i(response[2])
    byte3 = _b2i(response[3])
    byte4 = _b2i(response[4])

    # Process new_scan flag
    new_scan = bool(byte0 & 0b1)
    inversed_new_scan = bool((byte0 >> 1) & 0b1)
    if new_scan == inversed_new_scan:
        print('Error: New scan flags mismatch')
        # Handle the error here, such as setting new_scan to False
        new_scan = False

    # Process quality
    quality = byte0 >> 2

    # Process check bit
    check_bit = byte1 & 0b1
    if check_bit != 1:
        print('Error: Check bit not equal to 1')
        # Handle the error here

    # Calculate angle
    angle = ((byte1 >> 1) + (byte2 << 7)) / 64.

    # Calculate distance
    distance = (byte3 + (byte4 << 8)) / 4.

    return new_scan, quality, angle, distance


    check_bit = _b2i(response[1]) & 0b1
    if check_bit != 1:
        print('Error: Check bit not equal to 1')
        # Handle the error here

    angle = ((_b2i(response[1]) >> 1) + (_b2i(response[2]) << 7)) / 64.
    distance = (_b2i(response[3]) + (_b2i(response[4]) << 8)) / 4.
    return new_scan, quality, angle, distance



def save_data_to_file(data):
    # Add code to save data to a file
    pass

def start_scan(ser, scan_type):
    if scan_type == 'normal':
        response = send_command(ser, SCAN_NORMAL_BYTE)
    elif scan_type == 'force':
        response = send_command(ser, SCAN_FORCE_BYTE)
    elif scan_type == 'express':
        response = send_command(ser, SCAN_EXPRESS_BYTE)
    else:
        raise ValueError("Invalid scan type")
    return response


def run(device, scan_type='normal'):
    try:
        with serial.Serial(device, baudrate=BAUDRATE, timeout=TIMEOUT) as ser:
            # Get device information
            info = get_info(ser)
            print("Device Info Response:", info)

            # Get device health
            health = get_health(ser)
            print("Device Health Response:", health)

            # Start scanning
            start_scan(ser, scan_type)

            while True:
                descriptor = ser.read(DESCRIPTOR_LEN)
                dsize = descriptor[2]
                response = ser.read(dsize)
                new_scan, quality, angle, distance = process_data(response)
                print(f"New Scan: {new_scan}, Quality: {quality}, Angle: {angle}, Distance: {distance}")
    except serial.SerialException:
        print(f'[Error] Could not connect to device: {device}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='./device_calibration.py', description='rplidar calibration', epilog='The author assumes no liability for any damage caused by use.')
    parser.add_argument('device', help="device path", type=str)
    args = parser.parse_args()
    run(args.device)



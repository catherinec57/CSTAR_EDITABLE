from rplidar import RPLidar
import logging

log = logging.getLogger(__name__)
logging.basicConfig(filename='lidar.log', encoding='utf-8', level=logging.DEBUG)

lidar = RPLidar('COM3', logger=log, baudrate=115200)

info = lidar.get_info()
print(info)

health = lidar.get_health()
print(health)

for i, scan in enumerate(lidar.iter_scans()):
    print('%d: Got %d measurments' % (i, len(scan)))
    if i > 10:
        break

lidar.stop()
lidar.stop_motor()
lidar.disconnect()
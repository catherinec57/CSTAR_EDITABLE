cmake_minimum_required(VERSION 3.27)
project(ESP2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ESP2
        Encoder.cpp
        Encoder.h
        ESP2.ino
        LiDAR.cpp
        LiDAR.h
        Motor_Drive.cpp
        Motor_Drive.h
        SensorFusion.cpp
        SensorFusion.h
        UART_2.cpp
        UART_2.h
        Ultrasonic.cpp
        Ultrasonic.h)

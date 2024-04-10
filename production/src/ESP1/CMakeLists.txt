cmake_minimum_required(VERSION 3.27)
project(ESP1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ESP1
        Audio.cpp
        Audio.h
        Bluetooth.cpp
        Bluetooth.h
        ESP1.ino
        IO.cpp
        IO.h
        Queue.cpp
        Queue.h
        UART.cpp
        UART.h)

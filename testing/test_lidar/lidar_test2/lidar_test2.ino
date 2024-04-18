#include <Arduino.h>
#include "lidar_test.h"
#include <queue>
#include <utility>

// Define the RX and TX pins
#define RX_PIN 16
#define TX_PIN 17

std::queue<std::pair<int, int>> AngleDistanceQueue;

bool created = false; 

// Create an instance of the LiDAR class
// LiDAR lidar(0, AngleDistanceQueue);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);
  Serial.println("setup");
  
  // Create an instance of the LiDAR class
  // LiDAR lidar(0, AngleDistanceQueue);
  delay(5000); 
  Serial.println("after delay");
}
LiDAR lidar(0, AngleDistanceQueue);

void loop() {
  // if(!created) {
  //   Serial.println("creating lidar");
  //   // LiDAR lidar(0, AngleDistanceQueue);
  //   Serial.println("created lidar"); 
  //   created = true; 
  // } else {
  // //  Serial.println(created); 

  // }
  // // Main program loop
  lidar.main();

  // Check if there's any data in the queue
  if (!AngleDistanceQueue.empty()) {
    // Process the data
    std::pair<int, int> data = AngleDistanceQueue.front();
    AngleDistanceQueue.pop();
    int angle = data.first;
    int distance = data.second;
    
    // Print the data
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(", Distance: ");
    Serial.println(distance);
  } else {
    Serial.println("q empty");
  }
  
  // delay(1000); // Wait for 1 second before the next iteration
}

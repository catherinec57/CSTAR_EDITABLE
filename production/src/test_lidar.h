#ifndef LiDAR_h //required to ensure no cicular imports
#define LiDAR_h

#include "Arduino.h"
#include <utility>
#include <queue>

struct ExpressPacket {
    float distance[10];
    float angle[10];
    bool new_scan;
    float start_angle;
    int express_trame;
};

using IntPair = std::pair<int, int>;

class LiDAR {
  public: 
    LiDAR(int& state, std::queue<IntPair>& AngleDistanceQueue); // change parameters based on what is required
     //define all methods
    void main();
    std::queue<IntPair>& AngleDistanceQueue;
    int& state;
    void start(char scan_type, int& express_trame);
    void iter_measures(char scan_type, int max_buf_meas, ExpressPacket& express_data, ExpressPacket& express_old_data, int& express_trame);
    void getHealth(String& status, int& errorCode); // Method to get health status

  private:
    bool _process_scan(uint8_t* raw, bool& new_scan, int& quality, float& angle, float& distance); // Method to process scan data
    void _send_payload_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_size); // Method to send payload command
    void _send_cmd(uint8_t cmd); // Method to send command
    std::pair<int, bool> _read_descriptor(); // Method to read descriptor packet
    uint8_t* _read_response(int dsize); // Method to read response packet
};

#endif
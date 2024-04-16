#include "Audio.h" // make sure to include header !!!
#include <Arduino.h>

#include "driver/i2s.h"
#include <queue>
#include <utility>


Audio::Audio(int& state, std::queue<int>& audio_queue) : 
    state(state),
    audio_queue(audio_queue) { //changing initialization 
  // this->audio_queue = audio_queue;

  static const i2s_port_t i2s_num = I2S_NUM_0;
  
  static const i2s_config_t i2s_config = { //i2s_driver_config_t
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_24BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
    .dma_buf_count = 8,                             // 8 buffers
    .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
    .use_apll=0,
    .tx_desc_auto_clear= true, 
    .fixed_mclk=-1    
  };  

  static const i2s_pin_config_t pin_config = {
    .bck_io_num = 19,                                 // The bit clock connectiom, goes to pin 27 of ESP32 1 BCLK
    .ws_io_num = 14,                                  // Word select, also known as word select or left right clock 26 2 LRCK
    .data_out_num = I2S_PIN_NO_CHANGE,                               // Data out from the ESP32, connect to DIN on 38357A 25 3 I2S_PIN_NO_CHANGE
    .data_in_num = 26                                 // we are not interested in I2S data into the ESP32 I2S_PIN_NO_CHANGE SDTO 25
  };

  // Serial.begin(9600);
  i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
  i2s_set_pin(i2s_num, &pin_config);                        // Tell it the pins you will be using    

  // Define the LEDC channel and pin
  const int ledPin = 18; // GPIO pin connected to the LED or other PWM device
  const int ledChannel = 0; // LEDC channel (0-15)

  // Setup PWM properties
  const int freq = 40000; // Frequency in Hertz (40 kHz is high but still common)
  const int resolution = 8; // Resolution in bits (1-16, 8 bits gives 0-255 range for duty cycle)
  
  // Configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // Attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  // Set the duty cycle (0-255) due to 8-bit resolution
  ledcWrite(ledChannel, 127); // 50% duty cycle

}

// void subtract(int int1, int int2) {
//   int2-0.5*int1;
// }

void Audio::main() {
  static const i2s_port_t i2s_num = I2S_NUM_0;
  // Implement your function here
  uint32_t audioData; // Assuming you're reading 24-bit samples
  size_t bytesRead;
  analogWrite(18, 128);
  i2s_read(i2s_num, &audioData, sizeof(audioData), &bytesRead, portMAX_DELAY);
  
  // put a value in the queue
  if (audioData!= 0) {
    audioData = value;
  }
  audio_queue.push(value);
  value++;
}

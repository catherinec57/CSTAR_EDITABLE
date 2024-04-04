//------------------------------------------------------------------------------------------------------------------------
// Create a square wave on the I2S bus, compatible with  MAX98357A and PCM5102 I2S Decoders, probably others as well.
// We will be sending a signed 16 bit integer value to the ESP32's I2S buffer.
// Note, we are not taking advantage of being able to send large buffers to the i2s_write function, we are just going to
// write data one 16 bit word at a time as fast as the i2s is writing it out.
//
// Boring copyright/usage information:
//    (c) XTronical, www.xtronical.com
//    Use as you wish for personal or monatary gain, or to rule the world (if that sort of thing spins your bottle)
//    However you use it, no warrenty is provided etc. etc. It is not listed as fit for any purpose you perceive
//    It may damage your house, steal your lover, drink your beers and more.
//
// For more information and wiring for the specific chips mentioned please visit:
//    https://www.xtronical.com/I2SAudio
//
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------
// Includes
    #include "driver/i2s.h"                     // Library of I2S routines, comes with ESP32 standard install
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------
//  Global Variables/objects
    static const i2s_port_t i2s_num = I2S_NUM_0; // i2s port number
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------
// I2S configuration structures
static const i2s_config_t i2s_config = { //i2s_driver_config_t
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
    .dma_buf_count = 8,                             // 8 buffers
    .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
    .use_apll=0,
    .tx_desc_auto_clear= true,
    .fixed_mclk=-1
};// These are the physical wiring connections to our I2S decoder board/chip from the esp32, there are other connections
// required for the chips mentioned at the top (but not to the ESP32), please visit the page mentioned at the top for
// further information regarding these other connections.
static const i2s_pin_config_t pin_config = {
    .bck_io_num = 27,                                 // The bit clock connectiom, goes to pin 27 of ESP32 1 BCLK
    .ws_io_num = 26,                                  // Word select, also known as word select or left right clock 26 2 LRCK
    .data_out_num = I2S_PIN_NO_CHANGE,                               // Data out from the ESP32, connect to DIN on 38357A 25 3 I2S_PIN_NO_CHANGE
    .data_in_num = 25                                 // we are not interested in I2S data into the ESP32 I2S_PIN_NO_CHANGE SDTO
};//------------------------------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
    i2s_set_pin(i2s_num, &pin_config);                        // Tell it the pins you will be using
}void loop()
{
    uint16_t audioData; // Assuming you're reading 16-bit samples
    size_t bytesRead;
    // Read data from the I2S interface
    i2s_read(i2s_num, &audioData, sizeof(audioData), &bytesRead, portMAX_DELAY);
    // Print the number of bytes read
    Serial.println("HIIII");
    Serial.println(audioData);
}




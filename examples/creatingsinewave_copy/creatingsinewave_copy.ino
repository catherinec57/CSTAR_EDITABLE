const int sampleRate = 8000;  
const int frequency = 440;    
const int numSamples = 800;   
const float amplitude = 1023; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < numSamples; i++) {
    int value = amplitude * sin(2 * PI * frequency * i / sampleRate);
    Serial.print(value);
    if (i < numSamples - 1) {
      Serial.print(",");
    }
  }
  Serial.println(); 
  delay(1000); 
}
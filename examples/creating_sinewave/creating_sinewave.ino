
const int sampleRate = 8000;  
const int frequency = 440;    
const int numSamples = 800;   
const float amplitude = 1023; 
String finalArray;


void setup() {
  Serial.begin(9600);
  Serial.println("Running...");
}

void loop() {
  //Serial.println("Running...");
  for (int i = 0; i < numSamples; i++) {
    int value = amplitude * sin(2 * PI * frequency * i / sampleRate);
    String strvalue = String(value);
    finalArray.concat(strvalue);
    //Serial.print(strvalue);
    if (i < numSamples - 1) {
      finalArray.concat(",");
    }
    //Serial.println(finalArray);
  }
  Serial.println(finalArray);
  Serial.println(); 
  delay(1000); 
}




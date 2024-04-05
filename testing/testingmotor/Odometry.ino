#define leftEncoderChA 33
#define leftEncoderChB 27

#define rightEncoderChA 25
#define rightEncoderChB 18

double wheelR = 36;
double PPR = 537.6;
double tickCountPerRotation = PPR * 4;
double totalRightEncoderTicks, totalLeftEncoderTicks = forwardPulses * 4;



void Rotate(travel_angle) {
  
}

void Point(int desired_angle) {
    int travel_angle = desired_angle - current_angle;
    if (travel_angle > 180) {
      travel_angle = travel_angle - 360;
    }
    Rotate(travel_angle)
    current_angle = desired_angle;
}

void DriveForward(int distance)
{
  analogWrite(IN1_MOTOR1, 255);
  analogWrite(IN2_MOTOR1, 0);
  analogWrite(IN1_MOTOR2, 255);
  analogWrite(IN2_MOTOR2, 0);
}

void calculateForwardDistance() {
    double distanceTraveledRight = (totalRightEncoderTicks / tickCountPerRotation) * (2 * pi * wheelR);
    double distanceTraveledLeft = (totalLeftEncoderTicks / tickCountPerRotation) * (2 * pi * wheelR);
    double distanceTraveled = (distanceTraveledRight + distanceTraveledLeft) / 2;
}

void countForwardTicks() {
    forwardPulses++;
}

void countBackwardTicks() {
    backwardPulses++;
}

void setup() {

  pinMode(33, OUTPUT);   // Motor PWM Pins
  pinMode(27, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(18, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}

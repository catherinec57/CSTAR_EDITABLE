#define leftEncoderChA 33
#define leftEncoderChB 27

#define rightEncoderChA 25
#define rightEncoderChB 18

double wheelR = 36;
double PPR = 537.6;
double tickCountPerRotation = PPR * 4;
double totalRightEncoderTicks, totalLeftEncoderTicks = forwardPulses * 4;

void Rotate(travel_angle) {
  while () {
    if travel_angle > 0 {
      analogWrite(IN1_MOTOR1, 255);
      analogWrite(IN2_MOTOR2, 255);
    }
    else {
      analogWrite(IN2_MOTOR1, 255);
      analogWrite(IN1_MOTOR2, 255);
    }
  }
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
  while (distance > distanceTraveled) {
    analogWrite(IN1_MOTOR1, 255);
    analogWrite(IN1_MOTOR2, 255);
  }
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
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

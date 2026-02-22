#include <Servo.h>
Servo myservo;

// Motor pins
const int lms = 3;
const int in_A1 = 4;
const int in_A2 = 5;
const int in_B1 = 8;
const int in_B2 = 7;
const int rms = 6;

// IR Sensor pin (only one used)
const int IR = A0;

// Ultrasonic pins
const int ust = 2;
const int use = 9;

// Servo pin
const int servo_pin = A5;

// Speed
int sl = 95;
int sr = 110;

// kill switch true or false
bool killswitch = false;

// Distances
long dist_front, dist_right;

void setup() {
  pinMode(lms, OUTPUT);
  pinMode(in_A1, OUTPUT);
  pinMode(in_A2, OUTPUT);
  pinMode(rms, OUTPUT);
  pinMode(in_B1, OUTPUT);
  pinMode(in_B2, OUTPUT);

  pinMode(ust, OUTPUT);
  pinMode(use, INPUT);

  pinMode(IR, INPUT);

  myservo.attach(servo_pin);
  Stop();
  delay(1000);
}

void loop() {
  CheckForBlack();
  if (killswitch) {
    Stop();
    return;
  }
  TooCloseFront();
  WallFollow();
}

long scanForward() {
  myservo.write(90);
  delay(370);
  return USSensor();
}

long scanRight() {
  myservo.write(0);
  delay(370);
  return USSensor();
}

void CheckForBlack() {
  int irValue = analogRead(IR);
  if (irValue > 500) {
    killswitch = true;
  } else {
    killswitch = false;
  }
}

void TooCloseFront() {
  dist_front = scanForward();
  if (dist_front <= 200) {
    Back5();
  }
}

void WallFollow() {
  dist_front = scanForward();
  dist_right = scanRight();

  if (dist_front > 200 && dist_front <= 700 && dist_right > 400) {
    RightHookTurn();
    ForwardDrive();
  }

  else if (dist_front > 200 && dist_right <= 400) {
    if (dist_right > 250) {
      TurnRight5();
      ForwardDrive();
    }
    else if (dist_right > 230 && dist_right <= 250) {
      ForwardDrive();
    }
    else if (dist_right <= 230) {
      TurnLeft5();
      ForwardDrive();
    }
  }
 
  else if (dist_front <= 200 && dist_right <= 400) {
    TurnLeft90();
    ForwardDrive();
  }
}

void ForwardDrive() {
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, HIGH);
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, HIGH);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(400);
  Stop();
}

void TurnLeft90() {
  digitalWrite(in_A1, HIGH);
  digitalWrite(in_A2, LOW);
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, HIGH);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(150);
  Stop();
}

void RightHookTurn() {
  sl = 140;
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, HIGH);
  digitalWrite(in_B1, HIGH);
  digitalWrite(in_B2, LOW);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(150);
  sl = 95;
  Stop();
}

void TurnLeft5() {
  digitalWrite(in_A1, HIGH);
  digitalWrite(in_A2, LOW);
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, HIGH);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(70);
  Stop();
}

void TurnRight5() {
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, HIGH);
  digitalWrite(in_B1, HIGH);
  digitalWrite(in_B2, LOW);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(70);
  Stop();
}

void Back5() {
  digitalWrite(in_A1, HIGH);
  digitalWrite(in_A2, LOW);
  digitalWrite(in_B1, HIGH);
  digitalWrite(in_B2, LOW);
  analogWrite(lms, sl);
  analogWrite(rms, sr);
  delay(350);
  Stop();
}

void Stop() {
  analogWrite(lms, 0);
  analogWrite(rms, 0);
}

long USSensor() {
  digitalWrite(ust, LOW);
  delayMicroseconds(5);
  digitalWrite(ust, HIGH);
  delayMicroseconds(10);
  digitalWrite(ust, LOW);

  long duration = pulseIn(use, HIGH, 30000);
  if (duration == 0) return 400;

  return duration * 0.34 / 2;
}

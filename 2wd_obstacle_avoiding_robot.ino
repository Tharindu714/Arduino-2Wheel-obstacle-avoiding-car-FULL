int kr = 50;
#include <Servo.h>
Servo Myservo;
#define trigPin 3          // Trig Pin Of HC-SR04
#define echoPin 2        // Echo Pin Of HC-SR04
#define MLa 10                   //left motor 1st pin
#define MLb 11                  //left motor 2nd pin
#define MRa 6              //right motor 1st pin
#define MRb 5              //right motor 2nd pin
long duration, distance;
int val = 0;        // variable for reading the pin status
int LDRInput = A0; //Set Analog Input A0 for LDR.

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);     // Set Motor Pins As O/P
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT);       // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);        //Set Echo Pin As I/P To Receive Reflected Waves
  analogWrite(8, 250);
  analogWrite(7, 250);
  Myservo.attach(13);

  //knightRider
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);

  //turning lights
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);

  //buzzer
  pinMode(37, OUTPUT);

  //headlights
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);

  //left R
  pinMode(41, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(45, OUTPUT);

  //Right R
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);

  //LDR
  pinMode(LDRInput, INPUT);
}
void loop()
{
  Serial.begin(9600);
  ldr();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);        // Receive Reflected Waves
  distance = duration / 58.2;                       // Get Distance
  //  Serial.println(distance);
  delay(10);

  if (distance > 25) {              // Condition For Absence Of Obstacle
    Myservo.write(112);
    MoveForward();
    OffLeft();
    OffRight();
  }
  else if ((distance < 10) && (distance > 0))          // Condition For Presence Of Obstacle
  {
    Stop();
    HeadlightsOff();
    BuzzerKnightRider();
    delay(200);
    knightRider();
    knightRider();
    for (int i = 20; i < 170; i++) {
      Myservo.write(i);
      delay(10);
      Myservo.write(112);
    }
    MoveBack();
    OffLeft();
    OffRight();
    BuzzerStop();
    Stop();
    delay(100);
    knightRider();
    knightRider();
    knightRider();
    turnLeft();
    delay(320);
    Stop();
    blinkLeft();
    OffRight();
    Buzzer();
    delay(100);
    blinkLeft();
    Buzzer();
    delay(100);
    blinkLeft();
    Buzzer();
    delay(100);
    blinkLeft();
    Buzzer();
    delay(100);

  } else if ((distance < 20) && (distance > 0)) {
    Stop();
    BuzzerKnightRider();
    delay(200);
    knightRider();
    knightRider();
    for (int i = 20; i < 170; i++) {
      Myservo.write(i);
      delay(10);
      Myservo.write(112);
    }
    MoveBack();
    BuzzerStop();
    Stop();
    delay(100);
    knightRider();
    knightRider();
    knightRider();
    turnRight();
    delay(320);
    Stop();
    OffLeft();
    blinkRight();
    Buzzer();
    delay(100);
    blinkRight();
    Buzzer();
    delay(100);
    blinkRight();
    Buzzer();
    delay(100);
    blinkRight();
    Buzzer();
    delay(100);
  }
}
void knightRider() {
  digitalWrite(30, HIGH);
  delay(kr);
  digitalWrite(30, LOW);

  digitalWrite(31, HIGH);
  delay(kr);
  digitalWrite(31, LOW);

  digitalWrite(32, HIGH);
  delay(kr);
  digitalWrite(32, LOW);

  digitalWrite(33, HIGH);
  delay(kr);
  digitalWrite(33, LOW);

  digitalWrite(34, HIGH);
  delay(kr);
  digitalWrite(34, LOW);

  // reverse
  digitalWrite(34, HIGH);
  delay(kr);
  digitalWrite(34, LOW);

  digitalWrite(33, HIGH);
  delay(kr);
  digitalWrite(33, LOW);

  digitalWrite(32, HIGH);
  delay(kr);
  digitalWrite(32, LOW);

  digitalWrite(31, HIGH);
  delay(kr);
  digitalWrite(31, LOW);

  digitalWrite(30, HIGH);
  delay(kr);
  digitalWrite(30, LOW);
}

void blinkLeft() {
  digitalWrite(36, HIGH);
  digitalWrite(45, HIGH);
  delay(kr);
  digitalWrite(36, LOW);
  digitalWrite(45, LOW);
}
void OffLeft() {
  digitalWrite(36, LOW);
  digitalWrite(45, LOW);
}
void blinkRight() {
  digitalWrite(35, HIGH);
  digitalWrite(40, HIGH);
  delay(kr);
  digitalWrite(35, LOW);
  digitalWrite(40, LOW);
}
void OffRight() {
  digitalWrite(35, LOW);
  digitalWrite(40, LOW);
}

void turnRight() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(44, LOW);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  delay(100);
}

void turnLeft() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(44, LOW);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  delay(100);
}

void Stop() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, LOW);
  brake();
  digitalWrite(44, LOW);
  digitalWrite(41, LOW);

}

void MoveBack() {
  digitalWrite(MRb, HIGH);     // Move Backward
  digitalWrite(MRa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
  delay(500);
  reverse();
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);

}

void MoveForward() {
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MLa, HIGH);
  digitalWrite(44, LOW);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
}

void Buzzer() {
  digitalWrite(37, HIGH);
  delay(kr);
  digitalWrite(37, LOW);
  delay(kr);
  digitalWrite(37, HIGH);
  delay(kr);
  digitalWrite(37, LOW);
}

void BuzzerKnightRider() {
  digitalWrite(37, HIGH);
}

void BuzzerStop() {
  digitalWrite(37, LOW);
}

void Headlights() {
  digitalWrite(38, HIGH);
  digitalWrite(39, HIGH);
}

void HeadlightsOff() {
  digitalWrite(38, LOW);
  digitalWrite(39, LOW);
}

void reverse() {
  digitalWrite(44, HIGH);
  digitalWrite(41, HIGH);
}
void brake() {
  digitalWrite(42, HIGH);
  digitalWrite(43, HIGH);
}


void ldr() {
  int value = analogRead(LDRInput); //Reads the Value of LDR(light).
  Serial.println(value);
  if (value < 300)
  {
    HeadlightsOff();
  }
  else
  {
    Headlights();
  }
}





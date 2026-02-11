#include <Servo.h>
const int rainSensorPin = A0;    // Analog input pin for rain sensor
const int threshold = 500;       // Value below this = rain detected
const int servoPin = 9;          // Servo signal pin

Servo clothServo;
int lastServoPos = 180;          // Track previous servo position

void setup() {
  Serial.begin(9600);
  pinMode(rainSensorPin, INPUT);

  clothServo.attach(servoPin);

  // Start with clothes out
  clothServo.write(180);
  Serial.println("System Initialized: Clothes out.");
  delay(1000);
}

void loop() {
  int rainValue = analogRead(rainSensorPin);
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  if (rainValue < threshold && lastServoPos != 0) {
    Serial.println("Rain detected! Pulling clothes in.");
    clothServo.write(0);
    lastServoPos = 0;
  } 
  else if (rainValue >= threshold && lastServoPos != 180) {
    Serial.println("No rain. Pushing clothes out.");
    clothServo.write(180);
    lastServoPos = 180;
  } 
  else {
    Serial.println("No change needed.");
  }

  delay(2000);  // Delay between checks
}
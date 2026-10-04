/*
 * Fire Fighter Robot
 * -------------------
 * Arduino-based autonomous fire detection and extinguishing robot.
 *
 * Features:
 * - Detects fire using left, right, and forward sensors
 * - Controls two DC motors for movement
 * - Activates a water pump when fire is detected
 * - Uses a servo motor to aim the water nozzle
 * - Sends an SMS notification through a GSM module
 *
 * Hardware:
 * - Arduino Uno
 * - 3 fire/flame sensors
 * - L293D/L298N motor driver
 * - 2 DC motors
 * - Water pump
 * - Servo motor
 * - GSM module (SIM800/SIM900 or compatible)
 */

#include <Servo.h>
#include <SoftwareSerial.h>

// ============================================================
// CONFIGURATION
// ============================================================

constexpr uint8_t GSM_RX_PIN = 11;
constexpr uint8_t GSM_TX_PIN = 12;

// Replace with your own number before uploading.
// Do not commit your real phone number to a public repository.
String phoneNumber = "+880XXXXXXXXXX";

constexpr uint8_t MOTOR_SPEED = 80;

constexpr uint8_t SERVO_CENTER = 90;
constexpr uint8_t SERVO_LEFT = 30;
constexpr uint8_t SERVO_RIGHT = 150;

// ============================================================
// PIN DEFINITIONS
// ============================================================

constexpr uint8_t LEFT_SENSOR = 9;
constexpr uint8_t RIGHT_SENSOR = A0;
constexpr uint8_t FORWARD_SENSOR = 8;

constexpr uint8_t LEFT_MOTOR_1 = 2;
constexpr uint8_t LEFT_MOTOR_2 = 7;

constexpr uint8_t RIGHT_MOTOR_1 = 4;
constexpr uint8_t RIGHT_MOTOR_2 = 13;

constexpr uint8_t PUMP_PIN = A2;

constexpr uint8_t LEFT_SPEED_PIN = 3;
constexpr uint8_t RIGHT_SPEED_PIN = 5;

constexpr uint8_t SERVO_PIN = 10;

// ============================================================
// OBJECTS
// ============================================================

SoftwareSerial gsm(GSM_RX_PIN, GSM_TX_PIN);
Servo waterServo;

// ============================================================
// SETUP
// ============================================================

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(FORWARD_SENSOR, INPUT);

  pinMode(LEFT_MOTOR_1, OUTPUT);
  pinMode(LEFT_MOTOR_2, OUTPUT);
  pinMode(RIGHT_MOTOR_1, OUTPUT);
  pinMode(RIGHT_MOTOR_2, OUTPUT);

  pinMode(PUMP_PIN, OUTPUT);

  analogWrite(LEFT_SPEED_PIN, MOTOR_SPEED);
  analogWrite(RIGHT_SPEED_PIN, MOTOR_SPEED);

  waterServo.attach(SERVO_PIN);
  waterServo.write(SERVO_CENTER);

  digitalWrite(PUMP_PIN, LOW);

  Serial.println("Fire Fighter Robot Starting...");
  Serial.println("Initializing GSM module...");

  delay(5000);

  gsm.begin(9600);

  delay(1000);

  Serial.println("System Ready.");
}

// ============================================================
// MAIN LOOP
// ============================================================

void loop() {
  int leftSensor = digitalRead(LEFT_SENSOR);
  int rightSensor = digitalRead(RIGHT_SENSOR);
  int forwardSensor = digitalRead(FORWARD_SENSOR);

  // No fire detected
  if (leftSensor == HIGH &&
      rightSensor == HIGH &&
      forwardSensor == HIGH) {

    stopRobot();

    digitalWrite(PUMP_PIN, LOW);
    waterServo.write(SERVO_CENTER);
  }

  // Fire detected in front
  else if (forwardSensor == LOW) {

    delay(3000);

    moveForward();

    digitalWrite(PUMP_PIN, HIGH);
    waterServo.write(SERVO_CENTER);

    Serial.println("Fire detected: FORWARD");

    sendFireAlert();
  }

  // Fire detected on left
  else if (leftSensor == LOW) {

    delay(3000);

    turnLeft();

    digitalWrite(PUMP_PIN, HIGH);
    waterServo.write(SERVO_LEFT);

    Serial.println("Fire detected: LEFT");

    sendFireAlert();
  }

  // Fire detected on right
  else if (rightSensor == LOW) {

    delay(3000);

    turnRight();

    digitalWrite(PUMP_PIN, HIGH);
    waterServo.write(SERVO_RIGHT);

    Serial.println("Fire detected: RIGHT");

    sendFireAlert();
  }

  delay(300);
}

// ============================================================
// MOTOR FUNCTIONS
// ============================================================

void stopRobot() {
  digitalWrite(LEFT_MOTOR_1, HIGH);
  digitalWrite(LEFT_MOTOR_2, HIGH);

  digitalWrite(RIGHT_MOTOR_1, HIGH);
  digitalWrite(RIGHT_MOTOR_2, HIGH);
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_1, HIGH);
  digitalWrite(LEFT_MOTOR_2, LOW);

  digitalWrite(RIGHT_MOTOR_1, HIGH);
  digitalWrite(RIGHT_MOTOR_2, LOW);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_1, HIGH);
  digitalWrite(LEFT_MOTOR_2, LOW);

  digitalWrite(RIGHT_MOTOR_1, LOW);
  digitalWrite(RIGHT_MOTOR_2, HIGH);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_1, LOW);
  digitalWrite(LEFT_MOTOR_2, HIGH);

  digitalWrite(RIGHT_MOTOR_1, HIGH);
  digitalWrite(RIGHT_MOTOR_2, LOW);
}

// ============================================================
// GSM / SMS FUNCTION
// ============================================================

void sendFireAlert() {
  Serial.println("Sending fire alert SMS...");

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"" + phoneNumber + "\"\r");
  delay(1000);

  gsm.println("Be Alert! Fire Detected. Water Spraying.");

  delay(100);

  gsm.println((char)26);

  delay(1000);

  Serial.println("Fire alert SMS sent.");
}

#include <SPI.h>
#include <Pixy2.h>
#include <Servo.h>

// TCS3200 color sensor pins
#define S0 30
#define S1 32
#define S2 34
#define S3 36
#define sensorOut 13

// Calibration
#define RED_LOW_PARA 40
#define RED_HIGH_PARA 200
#define GREEN_LOW_PARA 50
#define GREEN_HIGH_PARA 300
#define BLUE_LOW_PARA 50
#define BLUE_HIGH_PARA 300

// Distance sensor pins
//#define trigPin 10
//#define echoPin 11

int blue = 0;
int red = 0;
int green = 0;
int frequency = 0;

Pixy2 pixy;
Servo servoMotor;

int myPins[6] = {2, 3, 4, 5, 6, 7}; // ENA, IN1, IN2, IN3, IN4, ENB
float deadZone = 0.15;
bool obstacleDetected = false;
int lastCubeColor = 0; // 1: Red, 2: Green

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  // Initialize Pixy2 camera
  pixy.init();
  if (pixy.init() == 0) {
    Serial.println("Pixy2 initialization successful.");
  } else {
    Serial.println("Pixy2 initialization failed.");
  }

  // Attach the servo motor to pin 8
  servoMotor.attach(8);
   servoMotor.write(90); 
   moveRobot(100, 100);

  // Set motor control pins as outputs
  for (int i = 0; i < 6; i++) {
    pinMode(myPins[i], OUTPUT);
  }

  // Set the color sensor pins as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize distance sensor pins
 // pinMode(trigPin, OUTPUT);
 // pinMode(echoPin, INPUT);
}

void loop() {
  /*long distance = readDistance();
  
  if (distance < 20) { // Pragul de 20 cm pentru evitarea obstacolelor
    Serial.println("Obstacle detected by distance sensor!");
    moveRobot(0, 0); // Oprește robotul
    
    // Efectuează acțiuni de evitare
    servoMotor.write(120); // Exemplu: virează dreapta
    delay(500);
    moveRobot(100, 100); // Continuă înainte
    delay(1000); // Ajustează timpul de mișcare înainte
    servoMotor.write(90); // Revine la centru
  } else {
    moveRobot(100, 100); // Ajustează valorile de viteză conform dinamicii robotului
  }

  pixyCheck();

  if (obstacleDetected) {
    if (lastCubeColor == 1) { // Cub roșu
      // Deviază la dreapta
      servoMotor.write(120); // Ajustează poziția servo pentru a vira dreapta
      delay(500); // Ajustează întârzierea conform cerințelor buclei de control pentru evitarea obstacolului

      // Continuă înainte și apoi corectează la stânga
      /*while (pixyCheck() != 0); // Așteaptă până când cubul nu este detectat
      servoMotor.write(45); // Ajustează poziția servo pentru a vira stânga
      delay(500); // Ajustează întârzierea conform cerințelor buclei de control pentru corectare

      // Revine la centru
      servoMotor.write(90); // Revine la poziția centrală
    } else if (lastCubeColor == 2) { // Cub verde
      // Deviază la stânga
      servoMotor.write(45); // Ajustează poziția servo pentru a vira stânga
      delay(500); // Ajustează întârzierea conform cerințelor buclei de control pentru evitarea obstacolului

      // Continuă înainte și apoi corectează la dreapta
     /* while (pixyCheck() != 0); // Așteaptă până când cubul nu este detectat
      servoMotor.write(120); // Ajustează poziția servo pentru a vira dreapta
      delay(500); // Ajustează întârzierea conform cerințelor buclei de control pentru corectare

      // Revine la centru
      servoMotor.write(90); // Revine la poziția centrală
    }

    obstacleDetected = false;
    lastCubeColor = 0; // Resetează ultima culoare a cubului după evitarea obstacolului
  }
*/
  checkColorSensor(); // Verifică senzorul de culoare și ajustează servo în consecință
}
/*
long readDistance() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and return the distance in centimeters
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

float pixyCheck() {
  int blocks = pixy.ccc.getBlocks();
  if (blocks) {
    int signature = pixy.ccc.blocks[0].m_signature;
    if (signature == 1 || signature == 2) { // Red or green cube
      obstacleDetected = true;
      lastCubeColor = signature;
      Serial.print("Detected cube color: ");
      if (signature == 1) {
        Serial.println("Red");
      } else {
        Serial.println("Green");
      }
      return signature;
    }
  }
  return 0; // Return 0 if no blocks detected or other color detected
}
*/
void moveRobot(int leftSpeed, int rightSpeed) {
  if (leftSpeed >= 0) {
    digitalWrite(myPins[1], HIGH);
    digitalWrite(myPins[2], LOW);
  } else {
    digitalWrite(myPins[1], LOW);
    digitalWrite(myPins[2], HIGH);
  }

  if (rightSpeed >= 0) {
    digitalWrite(myPins[3], HIGH);
    digitalWrite(myPins[4], LOW);
  } else {
    digitalWrite(myPins[3], LOW);
    digitalWrite(myPins[4], HIGH);
  }

  analogWrite(myPins[0], abs(leftSpeed));
  analogWrite(myPins[5], abs(rightSpeed));
}

void checkColorSensor() {
  // Read red component
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, RED_HIGH_PARA, RED_LOW_PARA, 255, 0);
  red = frequency;

  // Read green component
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, GREEN_HIGH_PARA, GREEN_LOW_PARA, 255, 0);
  green = frequency;

  // Read blue component
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, BLUE_HIGH_PARA, BLUE_LOW_PARA, 255, 0);
  blue = frequency;

  // Print RGB values
  Serial.print("R= ");
  Serial.print(red);
  Serial.print(" G= ");
  Serial.print(green);
  Serial.print(" B= ");
  Serial.println(blue);

  // Check for white color
  if (green < -20 && blue < -20 && red < -20) {
    // Detected white color
    Serial.println("Detected color: White");
    servoMotor.write(90); // Keep servo at 90 degrees
  } else {
    // Detected any other color
    Serial.println("Detected color: Not white");
    servoMotor.write(120); // Move servo to 120 degrees
    delay(1800); // Wait for 300 ms 
    servoMotor.write(90); // Return servo to 90 degrees
  }
}

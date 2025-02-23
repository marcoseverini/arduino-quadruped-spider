#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initialize the PCA9685 servo driver
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

// Standard positions for the servos when the robot is in a neutral position
#define STANDARD_y 325
#define STANDARD_xA 315
#define STANDARD_xB 295
#define STANDARD_xC 305
#define STANDARD_xD 345

// Servo pin assignments
#define SERVO_yD 12
#define SERVO_yC 13
#define SERVO_yB 14
#define SERVO_yA 15
#define SERVO_xC 4
#define SERVO_xA 5
#define SERVO_xB 6
#define SERVO_xD 7

// Struct to define servo configurations
struct ServoConfig {
    uint8_t pin;       // Servo pin number
    int standard;      // Standard (neutral) position
    bool increasesUp;  // Defines whether an increase in value moves the servo up or down
};

// Array storing the configurations for each servo
ServoConfig servos[] = {
    {SERVO_yA, STANDARD_y, true},
    {SERVO_yB, STANDARD_y, false},
    {SERVO_yC, STANDARD_y, false},
    {SERVO_yD, STANDARD_y, true},
    {SERVO_xA, STANDARD_xA, true},
    {SERVO_xB, STANDARD_xB, false},
    {SERVO_xC, STANDARD_xC, true},
    {SERVO_xD, STANDARD_xD, false}
};

// Function to move a specific servo with an offset from its standard position
void moveServo(uint8_t servoPin, int offset) {
    for (ServoConfig &s : servos) {
        if (s.pin == servoPin) {
            int target = s.increasesUp ? (s.standard + offset) : (s.standard - offset);
            pca9685.setPWM(servoPin, 0, target);
            break;
        }
    }
}

void setup() {
    Serial.begin(9600);
    pca9685.begin();
    pca9685.setPWMFreq(50);
    delay(1000);

    sit();  // Start in the sitting position
    delay(3000);
    stand(); // Move to the standing position
    delay(3000);
}

void loop() {
    // walk(); // Uncomment to enable walking in the main loop
}

// Function to move the robot into a sitting position
void sit() {
    for (ServoConfig &s : servos) {
        moveServo(s.pin, 0);
    }
}

// Function to make the robot stand up
void stand() {
    moveServo(SERVO_yA, -120);
    moveServo(SERVO_yB, -120);
    moveServo(SERVO_yC, -120);
    moveServo(SERVO_yD, -120);
}

// Function to move all legs forward in the x-axis
void forward_x() {
    moveServo(SERVO_xA, 40);
    moveServo(SERVO_xB, 40);
    moveServo(SERVO_xC, 40);
    moveServo(SERVO_xD, 40);
}

// Function to simulate walking movement
void walk(){
    // Phase 1
    // B and C lower while A and D lift
      // B and C lower
        moveServo(SERVO_yB, -120);
        moveServo(SERVO_yC, -120);
      // A and D lift
        moveServo(SERVO_yA, -85);
        moveServo(SERVO_yD, -85);
      delay(250);
    // B and C push backward while A and D move forward
      // B and C push backward
        moveServo(SERVO_xB, -50);
        moveServo(SERVO_xC, -50);
      // A and D move forward
        moveServo(SERVO_xA, 50);
        moveServo(SERVO_xD, 50);
      delay(500);
  
    // Phase 2
    // A and D lower while B and C lift
      // A and D lower
        moveServo(SERVO_yA, -120);
        moveServo(SERVO_yD, -120);
      // B and C lift
        moveServo(SERVO_yB, -85);
        moveServo(SERVO_yC, -85);
      delay(250);
    // B and C move forward while A and D push backward
      // A and D push backward
        moveServo(SERVO_xA, -50);
        moveServo(SERVO_xD, -50);
      // B and C move forward
        moveServo(SERVO_xB, 50);
        moveServo(SERVO_xC, 50);
      delay(500);
    
}

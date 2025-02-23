#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

#define STANDARD_y 325
#define STANDARD_xA 315
#define STANDARD_xB 295
#define STANDARD_xC 305
#define STANDARD_xD 345

#define SERVO_yD 12
#define SERVO_yC 13
#define SERVO_yB 14
#define SERVO_yA 15
#define SERVO_xC 4
#define SERVO_xA 5
#define SERVO_xB 6
#define SERVO_xD 7

struct ServoConfig {
    uint8_t pin;
    int standard;
    bool increasesUp;
};

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

    sit();
    delay(3000);
    stand();
    delay(3000);
    sit();
    delay(3000);
    stand();
    delay(3000);
    sit();
    delay(3000);
    stand();
    delay(1500);
     
}

void loop() {
  // walk();
}

void sit() {
    for (ServoConfig &s : servos) {
        moveServo(s.pin, 0);
    }
}

void stand() {
    moveServo(SERVO_yA, -120);
    moveServo(SERVO_yB, -120);
    moveServo(SERVO_yC, -120);
    moveServo(SERVO_yD, -120);
}

void forward_x() {
    moveServo(SERVO_xA, 40);
    moveServo(SERVO_xB, 40);
    moveServo(SERVO_xC, 40);
    moveServo(SERVO_xD, 40);
}
 
void walk(){
  // fase 1
    // B e C si abbassano mentre A e D si alzano 
      // B e C si abbassano
        moveServo(SERVO_yB, -120);
        moveServo(SERVO_yC, -120);
        // forse inserire delay qua 
      // A e D si alzano
        moveServo(SERVO_yA, -85);
        moveServo(SERVO_yD, -85);
      delay(250);
    // B e C spingono indietro mentre A e D vanno avanti
      // B e C spingono indietro 
        moveServo(SERVO_xB, -50);
        moveServo(SERVO_xC, -50);
      // A e D vanno avanti
        moveServo(SERVO_xA, 50);
        moveServo(SERVO_xD, 50);
      delay(500);
  // fase 2
    // A e D si abbassano mentre B e C si alzano
      // A e D si abbassano
        moveServo(SERVO_yA, -120);
        moveServo(SERVO_yD, -120);
        // forse inserire delay qua 
      // B e C si alzano
        moveServo(SERVO_yB, -85);
        moveServo(SERVO_yC, -85);
      delay(250);
    // B e C vanno avanti mentre A e D spingono indietro
      // A e D spingono indietro
        moveServo(SERVO_xA, -50);
        moveServo(SERVO_xD, -50);
      // B e C vanno avanti
        moveServo(SERVO_xB, 50);
        moveServo(SERVO_xC, 50);
      
      delay(500);

}
#include <Arduino.h>

// DEFINES
#define BL_RX 10
#define BL_TX 11
#define MOT1_A 1
#define MOT1_B 2
#define MOT2_A 3
#define MOT2_B 4
#define MOT3_A 5
#define MOT3_B 6
#define RMOT_A 7
#define RMOT_B 8
// DEFINES

// LIBS
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(BL_RX, BL_TX);

#include <GyverMotor2.h>
#define GMOTOR2_NO_ACCEL
GMotor2<DRIVER2WIRE> mot1(MOT1_A, MOT1_B);
GMotor2<DRIVER2WIRE> mot2(MOT2_A, MOT2_B);
GMotor2<DRIVER2WIRE> mot3(MOT3_A, MOT3_B);
GMotor2<DRIVER2WIRE> ramp_motor(RMOT_A, RMOT_B);
// LIBS

// VARS
// VARS

// function declarations
void StopMotors();
void SetMotorsXY(byte, byte, byte);
// function declarations 

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
}

// function definitions
void SetMotorsXY(byte x, byte y, byte R) {
byte W1 = -0.5*x - sqrt(3)/2*y + R;
byte W2 = -0.5*x + sqrt(3)/2*y + R;
byte W3 = x + R;


}
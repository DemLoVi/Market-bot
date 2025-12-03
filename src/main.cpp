#include <Arduino.h>


/*==========DEFINES==========*/
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
/*==========DEFINES==========*/


/*==========LIBS==========*/
#include <SoftwareSerial.h>
SoftwareSerial BTserial(BL_RX, BL_TX);

#include <GyverMotor2.h>
#define GMOTOR2_NO_ACCEL
GMotor2<DRIVER2WIRE> mot1(MOT1_A, MOT1_B);
GMotor2<DRIVER2WIRE> mot2(MOT2_A, MOT2_B);
GMotor2<DRIVER2WIRE> mot3(MOT3_A, MOT3_B);
GMotor2<DRIVER2WIRE> ramp_motor(RMOT_A, RMOT_B);
/*==========LIBS==========*/


/*==========VARS==========*/
bool doneParsing, startParsing;
int16_t dataX, dataY;
String string_convert;
/*==========VARS==========*/


/*==========FUNC-DECL==========*/
bool parsing();
void StopMotors();
void SetMotorsXY(byte, byte, byte);
/*==========FUNC-DECL==========*/


void setup() {
  // Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  if (parsing()) SetMotorsXY(dataX, dataY, 0); // if done parsing set motors
}


/*==========FUNC-DEF==========*/
void SetMotorsXY(byte x, byte y, byte R) { // set speeds to motors
byte W1 = -0.5*x - sqrt(3)/2*y + R;        // convertation for qiwi drive
byte W2 = -0.5*x + sqrt(3)/2*y + R;
byte W3 = x + R;

mot1.setSpeed(W1);                         // set motors
mot2.setSpeed(W2);
mot3.setSpeed(W3);
}

void StopMotors() { // full stop platform
  mot1.stop();
  mot2.stop();
  mot3.stop();
}

bool parsing() {
  if (BTserial.available() > 0) {        // if data avaible
    char incomingChar = BTserial.read(); // read incoming data
    if (startParsing) {                  // start parsing
      if (incomingChar == ' ') {         // if we done reciving X data
        dataX = string_convert.toInt();  // save X data
        string_convert = "";             // clear buffer
      }
      else if (incomingChar == ';') {    // if we done reciving Y data
        dataY = string_convert.toInt();  // save Y data
        string_convert = "";             // clear buffer
        startParsing = false;            // stop parsing
        return true;                     // raturn done parsing
      } else {
        string_convert += incomingChar;  // add incoming symbol to buffer
      }
    }
    if (incomingChar == '$') {           // start parsing
      startParsing = true;              
    }
  }
  return false;                          // return parsing not done
}
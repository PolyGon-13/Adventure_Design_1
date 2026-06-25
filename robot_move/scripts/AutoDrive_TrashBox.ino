#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(10, 11);
#define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
#define DEBUG_SERIAL SerialUSB
#else
#define DEBUG_SERIAL Serial
#endif

const uint8_t DXL_ID1 = 1;
const uint8_t DXL_ID2 = 2;
const uint8_t DXL_ID3 = 3;
const uint8_t DXL_ID4 = 4;

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl_1;
DynamixelShield dxl_2;
DynamixelShield dxl_3;
DynamixelShield dxl_4;

//왼쪽 
const int TRIG1 = 4;
const int ECHO1 = 5;
//오른쪽 
const int TRIG2 = 2;
const int ECHO2 = 3;
//전방
const int TRIG3 = 6;
const int ECHO3 = 7;

long duration1, duration2, distance1, distance2, distance3, duration3, duration;
int distance;

void setup() {
  DEBUG_SERIAL.begin(115200);

  dxl_1.begin(57600);
  dxl_2.begin(57600);
  dxl_3.begin(57600);
  dxl_4.begin(57600);

  dxl_1.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_2.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_3.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl_4.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  dxl_1.ping(DXL_ID1);
  dxl_2.ping(DXL_ID2);
  dxl_3.ping(DXL_ID3);
  dxl_4.ping(DXL_ID4);

  dxl_1.torqueOff(DXL_ID1);
  dxl_1.setOperatingMode(DXL_ID1, OP_VELOCITY);
  dxl_1.torqueOn(DXL_ID1);

  dxl_2.torqueOff(DXL_ID2);
  dxl_2.setOperatingMode(DXL_ID2, OP_VELOCITY);
  dxl_2.torqueOn(DXL_ID2);

  dxl_3.torqueOff(DXL_ID3);
  dxl_3.setOperatingMode(DXL_ID3, OP_VELOCITY);
  dxl_3.torqueOn(DXL_ID3);

  dxl_4.torqueOff(DXL_ID4);
  dxl_4.setOperatingMode(DXL_ID4, OP_VELOCITY);
  dxl_4.torqueOn(DXL_ID4);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
}

void loop() {
  driveSensor(TRIG1, ECHO1);
  distance1 = distance;
  driveSensor(TRIG2, ECHO2);
  distance2 = distance;
  driveSensor(TRIG3, ECHO3);
  distance3 = distance;

  if (distance3 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, 0);
    dxl_2.setGoalVelocity(DXL_ID2, 0);
    dxl_3.setGoalVelocity(DXL_ID3, 0);
    dxl_4.setGoalVelocity(DXL_ID4, 0);
    delay(10000);
  }
  else if (distance1 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, 200);
    dxl_2.setGoalVelocity(DXL_ID2, 200);
    dxl_3.setGoalVelocity(DXL_ID3, 200);
    dxl_4.setGoalVelocity(DXL_ID4, 200);
  }
  else if (distance2 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, -200);
    dxl_2.setGoalVelocity(DXL_ID2, -200);
    dxl_3.setGoalVelocity(DXL_ID3, -200);
    dxl_4.setGoalVelocity(DXL_ID4, -200);
  }
  else if ((distance1 > 50) && (distance2 > 50 ) && (distance3 > 50 )) {
    dxl_1.setGoalVelocity(DXL_ID1, -200);
    dxl_2.setGoalVelocity(DXL_ID2, 200);
    dxl_3.setGoalVelocity(DXL_ID3, -200);
    dxl_4.setGoalVelocity(DXL_ID4, 200);
  }
}

void driveSensor(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.4;
}

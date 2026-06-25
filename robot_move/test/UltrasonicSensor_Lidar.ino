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

#include <Servo.h>  //서보 라이브러리를 불러온다
#define TRIG 12
#define ECHO 13
Servo servo;
 
int servoDirection = 1, rad = 0; // rad는 각도를 의미합니다.

const uint8_t DXL_ID1 = 1;
const uint8_t DXL_ID2 = 2;
const uint8_t DXL_ID3 = 3;
const uint8_t DXL_ID4 = 4;

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl_1;
DynamixelShield dxl_2;
DynamixelShield dxl_3;
DynamixelShield dxl_4;

const int TRIG1 = 9;
const int ECHO1 = 8;
const int TRIG2 = 7;
const int ECHO2 = 6;
const int TRIG3 = 5;
const int ECHO3 = 4;

long duration1, duration2, distance1, distance2, distance3, duration3, duration;
int distance;
long distance5;

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

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(14); //서보모터 핀은 9번
}
void lidar(int TrigPin, int EchoPin);

void loop() {
  driveSensor(TRIG1, ECHO1);
  distance1 = distance;
  driveSensor(TRIG2, ECHO2);
  distance2 = distance;
  driveSensor(TRIG3, ECHO3);
  distance3 = distance;


  if (distance5 <= 20 ) {
    dxl_1.setGoalVelocity(DXL_ID1, 0);
    dxl_2.setGoalVelocity(DXL_ID2, 0);
    dxl_3.setGoalVelocity(DXL_ID3, 0);
    dxl_4.setGoalVelocity(DXL_ID4, 0);
}


  if (distance3 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, 0);
    dxl_2.setGoalVelocity(DXL_ID2, 0);
    dxl_3.setGoalVelocity(DXL_ID3, 0);
    dxl_4.setGoalVelocity(DXL_ID4, 0);
  }
  if (distance1 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, 200);
    dxl_2.setGoalVelocity(DXL_ID2, 200);
    dxl_3.setGoalVelocity(DXL_ID3, 200);
    dxl_4.setGoalVelocity(DXL_ID4, 200);
  }
  if (distance2 <= 50 ) {
    dxl_1.setGoalVelocity(DXL_ID1, -200);
    dxl_2.setGoalVelocity(DXL_ID2, -200);
    dxl_3.setGoalVelocity(DXL_ID3, -200);
    dxl_4.setGoalVelocity(DXL_ID4, -200);
  }
  if ((distance1 > 50) && (distance2 > 50 ) && (distance3 > 50 )) {
    dxl_1.setGoalVelocity(DXL_ID1, -200);
    dxl_2.setGoalVelocity(DXL_ID2, 200);
    dxl_3.setGoalVelocity(DXL_ID3, -200);
    dxl_4.setGoalVelocity(DXL_ID4, 200);
  }
  delay(100);
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

void lidar(int TrigPin, int EchoPin){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);  //2uS 동안 멈춤
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);  //10uS 동안 동작
  digitalWrite(TRIG, LOW);
 
  //5800이면 1m 입니다. 최대 기다리는 시간은 1,000,000 입니다.
  // 5800을 58로 나누게 되면 cm 단위가 됩니다.
  long distance5 = pulseIn(ECHO, HIGH, 5800) / 58; //5800uS 동안 기다렸으므로 1미터 측정이 된다.
  Serial.print("r");
  Serial.print(rad);
  Serial.print("d");
  Serial.println(distance5);
 
  rad += servoDirection;
  if (rad > 180) {
    rad = 179;
    servoDirection = -1;
  }
  else if (rad < 0) {
    rad = 1;
    servoDirection = 1;
  }
  servo.write(rad);
  delay(60); //서보모터가 움직이는 걸리는 시간을 줍니다.
}

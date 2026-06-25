int sw1 = 2;
int sw2 = 3;
int sw3 = 4;
#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
//====================================DC
int in1 = 5;  //in1 7번 포트로 제어 (OUT1)
int in2 = 6;  //in2 5번 포트로 제어 
 
void setup() {
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  servo.attach(7);     //맴버함수인
  servo.write(90);// 90이 쓰레기동 닫힌 상태 180이 쓰레기통 열린 상태(예상)
  //=====================================DC
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  Serial.begin(9600);

}
 
void loop() {
  Serial.print(digitalRead(sw1));
  Serial.print(digitalRead(sw2));
  Serial.println(digitalRead(sw3));
  
  if(digitalRead(sw3) == LOW){ //1스위치가 눌리면
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);   
    delay(800);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    servo.write(180);
    delay(800);
    servo.write(90);
    delay(1000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);   
    delay(750);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  }
  
  
  if(digitalRead(sw1) == LOW){ //2스위치가 눌리면
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);   
    delay(800);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    servo.write(180);
    delay(800);
    servo.write(90);
    delay(1000);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);   
    delay(750);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  }
  
  else if(digitalRead(sw2) == LOW){ //3스위치가 눌리면
    servo.write(180);
    delay(1000);
    servo.write(90);
  }else{
    servo.write(90);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  }
}

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);

const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int StepZ = 4;
const int DirZ = 7;

const int Step23 = 9;
const int Dir23 = 8;

char state;

void setup() {
  Serial.begin(9600);
  mySerial.begin(2400);
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
  pinMode(StepY,OUTPUT);
  pinMode(DirY,OUTPUT);
  pinMode(StepZ,OUTPUT);
  pinMode(DirZ,OUTPUT);
  
  pinMode(Step23,OUTPUT);
  pinMode(Dir23,OUTPUT);
}

void loop() {
  //if (Serial.available() > 0){  //입력시 동작 시리얼통신 이용할 때 없앨것
 if (mySerial.available() > 0){    // 수신되었는지 상태 확인
  state = mySerial.read();

  if (state=='5'){
  
   digitalWrite(DirX, LOW); // set direction, HIGH for clockwise, LOW for anticlockwise
   digitalWrite(DirY, LOW);

 // X, Y 동시에 반시계 3바퀴 회전
   for(int x = 0; x<600; x++) { 
    digitalWrite(StepX,HIGH);
    digitalWrite(StepY,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepX,LOW); 
    digitalWrite(StepY,LOW); 
    delayMicroseconds(3000);
   }
   delay(1000);

    


 // 23 회전
   digitalWrite(Dir23, HIGH);  // 액츄에이터 내려감 : high
   for(int y = 0; y<5; y++){
   for(int x = 0; x<10000; x++) {
    digitalWrite(Step23,HIGH);
    delayMicroseconds(200);
    digitalWrite(Step23,LOW); 
    delayMicroseconds(50);
   }}
   
   delay(1000);

   digitalWrite(DirY, HIGH);
   digitalWrite(DirZ, LOW);
   for(int x = 0; x<600; x++) {
    digitalWrite(StepY,HIGH);
    digitalWrite(StepZ,HIGH);
    delayMicroseconds(500);
    digitalWrite(StepY,LOW);
    digitalWrite(StepZ,LOW);
    delayMicroseconds(3000);
   }
   delay(1000);

   digitalWrite(Dir23, LOW);  // 액츄에이터 올라감
   for(int y = 0; y<5; y++){
   for(int x = 0; x<10000; x++) {
    digitalWrite(Step23,HIGH);
    delayMicroseconds(200);
    digitalWrite(Step23,LOW); 
    delayMicroseconds(50);
   }}
   delay(1000);}
}
  delay(1000);
exit(0);}

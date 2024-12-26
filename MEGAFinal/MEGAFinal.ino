#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);    //Rx, Tx 설정

//모터핀
#define PWMA 12    //A모터속도
#define DIRA1 34 
#define DIRA2 35  //A모터방향
#define PWMB 8    //B모터속도
#define DIRB1 37 
#define DIRB2 36  //B모터방향
#define PWMC 6   //C모터속도
#define DIRC1 43 
#define DIRC2 42  //C모터방향
#define PWMD 5    //D모터속도
#define DIRD1 A4  //26  
#define DIRD2 A5  //27  //D모터방향

#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA1,HIGH); digitalWrite(DIRA2,LOW);analogWrite(PWMA,pwm);}while(0)
#define MOTORA_STOP(x)         do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,LOW); analogWrite(PWMA,0);}while(0)
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA1,LOW);digitalWrite(DIRA2,HIGH); analogWrite(PWMA,pwm);}while(0)

#define MOTORB_FORWARD(pwm)    do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,HIGH);analogWrite(PWMB,pwm);}while(0)
#define MOTORB_STOP(x)         do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,LOW); analogWrite(PWMB,0);}while(0)
#define MOTORB_BACKOFF(pwm)    do{digitalWrite(DIRB1,HIGH);digitalWrite(DIRB2,LOW); analogWrite(PWMB,pwm);}while(0)

#define MOTORC_FORWARD(pwm)    do{digitalWrite(DIRC1,HIGH); digitalWrite(DIRC2,LOW);analogWrite(PWMC,pwm);}while(0)
#define MOTORC_STOP(x)         do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,LOW); analogWrite(PWMC,0);}while(0)
#define MOTORC_BACKOFF(pwm)    do{digitalWrite(DIRC1,LOW);digitalWrite(DIRC2,HIGH); analogWrite(PWMC,pwm);}while(0)

#define MOTORD_FORWARD(pwm)    do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,HIGH);analogWrite(PWMD,pwm);}while(0)
#define MOTORD_STOP(x)         do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,LOW); analogWrite(PWMD,0);}while(0)
#define MOTORD_BACKOFF(pwm)    do{digitalWrite(DIRD1,HIGH);digitalWrite(DIRD2,LOW); analogWrite(PWMD,pwm);}while(0)

#define SERIAL  Serial

#define LOG_DEBUG

#ifdef LOG_DEBUG
#define M_LOG SERIAL.print
#else
#define M_LOG 
#endif

#define MAX_PWM   200
#define MIN_PWM   130
int Motor_PWM = 200;

//제어모터운동 매크로정의


//    ↑A-----B↑   
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
void ADVANCE()
{
  MOTORA_FORWARD(40);MOTORB_FORWARD(40);    
  MOTORC_FORWARD(40);MOTORD_FORWARD(40);    
}

//    ↓A-----B↓   
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void BACK()
{
  MOTORA_BACKOFF(40);MOTORB_BACKOFF(40);
  MOTORC_BACKOFF(40);MOTORD_BACKOFF(40);
}
//    =A-----B↑   
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void LEFT_1()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}

//    ↓A-----B↑   
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void LEFT_2()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↓A-----B=   
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void LEFT_3()
{
  MOTORA_BACKOFF(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_BACKOFF(Motor_PWM);
}
//    ↑A-----B=   
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void RIGHT_1()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    ↑A-----B↓   
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void RIGHT_2()
{
  MOTORA_FORWARD(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_FORWARD(Motor_PWM);
}
//    =A-----B↓   
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void RIGHT_3()
{
  MOTORA_STOP(Motor_PWM);MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM);MOTORD_STOP(Motor_PWM);
}
//    =A-----B=  
//     |  =  |
//     |  =  |
//    =C-----D=
void STOP()
{
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

void UART_Control()
{
  char Uart_Date=0;
 if(SERIAL.available())
  {
   Uart_Date = SERIAL.read();
  }
  switch(Uart_Date)
  {
     case 'A':  ADVANCE(); M_LOG("Run!\r\n");        break;
     case 'B':  RIGHT_1();  M_LOG("Right up!\r\n");     break;
     case 'C':  RIGHT_2();  M_LOG("Right!\r\n");        break;
     case 'D':  RIGHT_3();  M_LOG("Right down!\r\n");   break;
     case 'E':  BACK();     M_LOG("Run!\r\n");        break;
     case 'F':  LEFT_3();   M_LOG("Left down!\r\n");    break;
     case 'G':  LEFT_2();   M_LOG("Left!\r\n");       break;
     case 'H':  LEFT_1();   M_LOG("Left up!\r\n");  break;
     case 'Z':  STOP();     M_LOG("Stop!\r\n");       break;
     case 'L':  Motor_PWM = 240;                      break;
     case 'M':  Motor_PWM = 130;                       break;
   }
}
void IO_init()
{
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA1, OUTPUT);pinMode(DIRA2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB1, OUTPUT);pinMode(DIRB2, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC1, OUTPUT);pinMode(DIRC2, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD1, OUTPUT);pinMode(DIRD2, OUTPUT);
  STOP();
}

int trigPin=44; //디지털핀 PL1
int echoPin=45; //디지털핀 PL2
int data;
float duration, distance;

void setup()
{
  SERIAL.begin(9600);
  IO_init();
  mySerial.begin(2400);
  pinMode(echoPin,INPUT);
  pinMode(trigPin, OUTPUT);
  distance=40;
//  SERIAL.print("Start");
}



void loop()
{
  //UART_Control();
  
  
  data=Serial.read();
  if (data=='9'){
    ADVANCE();
  }
  if (data=='1')    // 호수인식 -> 파이썬으로부터 '1'이란 데이터를 받음
  {
    STOP();    // 멈춤
    delay(1000);
    RIGHT_2();
    while(distance >= 20){
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
  
      duration = pulseIn(echoPin, HIGH);
      distance = ((float)(340*duration) / 10000 ) / 2;
      delay(100);
      }    // 오른쪽 문앞으로. 
    }
    if (distance <= 20){
      STOP();    // 문앞에서 정지.
      delay(1000);
      mySerial.write('5');
      delay(7000);    // 계산 필요.
      LEFT_2();    // 원래있던 장소로. 거리 센서 필요?
      while(distance <=50){
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
  
        duration = pulseIn(echoPin, HIGH);
        distance = ((float)(340*duration) / 10000 ) / 2;
        delay(100);
      }
      if (distance >= 50){
        ADVANCE();    //왔던 장소로 돌아가기??
        delay(3000);
        STOP();
        exit(0);
      }
    }
  }
  

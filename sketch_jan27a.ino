#include <Servo.h>
int A_1A=6;
int A_1B=11;
int B_1A=3;
int B_1B=5;

int TrigPin=8;
int EchoPin =9;
int ServoPin=10;

Servo servo;

int motorASpeed=150;
int motorBSpeed=150;

void setup() {
  Serial.begin(9600);
  pinMode(A_1A,OUTPUT);
  pinMode(A_1B,OUTPUT);
  pinMode(B_1A,OUTPUT);
  pinMode(B_1B,OUTPUT);
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,LOW);

  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);

  servo.attach(ServoPin);

  servo.write(90);
  delay(1000);
}

void loop() {
  int cm = getStableDistanceCM();
  long leftDistance = 0;
  long rightDistance =0;
  if (cm<25){
    stop();
    delay(500);

    servo.write(150);
    delay(500);
    leftDistance=getStableDistanceCM();
    delay(500);

    servo.write(30);
    delay(500);
    leftDistance = getStableDistanceCM();

    servo.write(90);
    delay(1000);
    back();
    delay(300);

    if (leftDistance>rightDistance)
    {
      left();
    }
    else 
    {
      right();
    }

    delay(500);
  }
  else{
    forward();
  }
    
  
}

float getDistanceCM()
{
  digitalWrite(EchoPin,LOW);
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);

  float distance = pulseIn(EchoPin,HIGH) /29.0/2.0;

  return distance;
  }

  float getStableDistanceCM()
  {
    int CmSum=0;
    for (int i=0;i<10;i++){
      CmSum +=getDistanceCM();
      }
      return CmSum/10;
   }

void forward()
{
  analogWrite(A_1A,motorASpeed);
  analogWrite(A_1B,0);

  analogWrite(B_1A,motorBSpeed);
  analogWrite(B_1B,0);
  }    

void back()
{
  analogWrite(A_1A,0);
  analogWrite(A_1B,motorASpeed);

  analogWrite(B_1A,0);
  analogWrite(B_1B,motorBSpeed);
  }    
void left()
{
  analogWrite(A_1A,motorASpeed);
  analogWrite(A_1B,0);

  analogWrite(B_1A,0);
  analogWrite(B_1B,0);
  }  
void right()
{
  analogWrite(A_1A,0);
  analogWrite(A_1B,0);

  analogWrite(B_1A,motorBSpeed);
  analogWrite(B_1B,0);
  }    
void stop()
{
  analogWrite(A_1A,0);
  analogWrite(A_1B,0);

  analogWrite(B_1A,0);
  analogWrite(B_1B,0);
  }    

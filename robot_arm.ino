#include <SoftwareSerial.h>

#include <Servo.h>


const int SERVOS = 4;

Servo MyServo[SERVOS];
int PIN[SERVOS],MAX[SERVOS],MIN[SERVOS],INITANGLE[SERVOS],ANA[SERVOS];
int Value[SERVOS],Idle[SERVOS];
int PreviousAngle[SERVOS],CurrentAngle[SERVOS];
int Servo_Moving[SERVOS]={0,0,0,0};

SoftwareSerial MySerial(12,13);

int BT_Servo=0;
int BT_Move=0;

void Move_Manu();
void Move_BT();
void CheckSoftSerial();
void setup() {
   MySerial.begin(9600);
   Serial.begin(9600);
   Move_lnit();

}

void loop() {
  Move_Manu();
  Move_BT();

}
void Move_lnit()
{
  PIN[0]=9;
  MIN[0]=0;
  MAX[0]=170;
  INITANGLE[0]=70;
  ANA[0]=3;

  PIN[1]=6;
  MIN[1]=30;
  MAX[1]=175;
  INITANGLE[1]=140;
  ANA[1]=2;

  PIN[2]=5;
  MIN[2]=40;
  MAX[2]=160;
  INITANGLE[2]=80;
  ANA[2]=0;

  PIN[3]=10;
  MIN[3]=60;
  MAX[3]=160;
  INITANGLE[3]=80;
  ANA[3]=1;

  for(int i=0;i<SERVOS;i++)
  {
    MyServo[i].attach(PIN[i]);
    MyServo[i].write(INITANGLE[i]);
    Value[i]=0;
    Idle[i]=0;
    PreviousAngle[i]=INITANGLE[i];
    }
  }
  void Move_Manu()
  {
    for (int i=0;i<SERVOS;i++)
    {
      Value[i]=analogRead(ANA[i]);
      CurrentAngle[i]=MyServo[i].read();

      if(Value[i]>612)
      {
        Idle[i]=0;
        if(CurrentAngle[i]<MAX[i])
        {++CurrentAngle[i];};
        if(!MyServo[i].attached())
        {MyServo[i].attach(PIN[i]);}
        MyServo[i].write(CurrentAngle[i]);
        }
      else if(Value[i]<412)
      {
        Idle[i]=0;
        if(CurrentAngle[i]>MIN[i])
        {--CurrentAngle[i];};
        if(!MyServo[i].attached())
        {MyServo[i].attach(PIN[i]);}
        MyServo[i].write(CurrentAngle[i]);
        }   
       else{++Idle[i];}
       {
        if (Idle[i]>100)
        {
          MyServo[i].detach();
          Idle[i]=0;
          }
        }
        for (int i=0;i<SERVOS;i++)
        {
          if(!MyServo[i].attached())
          {MyServo[i].attach(PIN[i]);}
          MyServo[i].write(CurrentAngle[i]);
          }
      }   delay(20);
    }
    void Move_BT(){
      SoftSerial();

      for(int i=0;i<SERVOS;i++)
      {
        CurrentAngle[i]+=Servo_Moving[i];
        CurrentAngle[i] = CurrentAngle[i]>MAX[i]?--CurrentAngle[i]:CurrentAngle[i];
        CurrentAngle[i] = CurrentAngle[i]<MIN[i]?++CurrentAngle[i]:CurrentAngle[i];
        MyServo[i].write(CurrentAngle[i]);
        delay(20);
        }
      }
     void SoftSerial()
     {
      String Str="";

      if (MySerial.available())
      {
        for (int i =0;i<2;i++)
        {
          Str+=(char)MySerial.read();
          }
          int Value = Str.toInt();
          BT_Servo=Value/10;

          int Angle = Value%10;
          if(Angle==2){BT_Move=-1;}
          else{BT_Move=0;}

          Servo_Moving[BT_Servo]=BT_Move;
        }
      }

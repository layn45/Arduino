//#include <Wire.h>
#include <Servo.h>

const int SERVOS = 4;
Servo MyServo[SERVOS];
int MoveAngle[4]={90,152,90,60};
int Pin[4]={9,6,5,10};

int SaveAngle[10][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int Btn=0;
boolean Flag=0;

void ReadServo(byte Num,int ANA);
void ReadMove(int Num,int Angle);

void setup() {
  Serial.begin(9600);

  for (int i=0;i<4;i++)
  {
    MyServo[i].write(MoveAngle[i]);
    }
   pinMode(8,INPUT_PULLUP);
   pinMode(9,INPUT_PULLUP);

}

void loop() {
  ReadServo(0,analogRead(3));
  ReadServo(1,analogRead(2));
  ReadServo(2,analogRead(0));
  ReadServo(3,analogRead(1));

  if(digitalRead(8)==0)
  {
    if(Flag==1)
    {
      Btn=0;
      Flag=0;
      }
     for(int i=0;i<4;i++)
     {
      SaveAngle[Btn][i]=MoveAngle[i];
      }
      Btn++;
      Serial.println("Move save")
      delay(500);
    }
    if (digitalRead(9)==0)
    {
      for(int n=0;n<3;n++){
        for(int i =0;i<Btn;i++){
          for(int j=0;j<4;j++){
            ReadMove(j,SaveAngle[i][j]);
            delay(20);
          }
          delay(500);
        }
      }
      Flag=1;
      Serial.println("Repeat move");
      delay(1000);
          }
          delay(25);
        }
       void ReadServo(byte Num,int ANA)
       {
        if (ANA>900)
        {
          MoveAngle[Num]+=1;
          if(Num==0)
          {
            if(MoveAngle[Num]>180)
            {
              MoveAngle[Num]=180;
              }
            }
            else if(Num==1)
            {
              if(MoveAngle[Num]>165)
              {
                MoveAngle[Num]=165;
                }
              }
              else if(Num==3)
              {
                if (MoveAngle[Num]>180)
                {
                  MoveAngle[Num]=180;
                  }
                }
          }
          else if(ANA<200)
          {
            MoveAngle[Num]-=1;
            if(Num==0)
            {
              if(MoveAngle[Num]<30)
              {
                MoveAngle[Num]=0;
                }
              }
              else if(Num==2)
              {
                if(MoveAngle[Num]<=90)
                {
                  MoveAngle[Num]=60;
                  }
                }
            }
        }
      }
      }
}

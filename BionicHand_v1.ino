#include <Servo.h>

int EMG1 = A3;
int EMG2 = A2;

int a=2;
int b=3;

int deget1=5;
int deget2=6;
int deget3=7;
int deget4=8;
int deget5=9;

Servo motor[6];

int MOTOR_PIN[6];
int pos[6];

int senzor1;
int senzor2;

float lp_alpha1 = 0.01;
float lp_out1 = 0;

float lp_alpha2 = 0.01;
float lp_out2 = 0;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  for(int i=1;i<6;i++){
    pos[i] = 40;
    MOTOR_PIN[i]=i+4;
    motor[i].attach(MOTOR_PIN[i]);
  }
  Serial.begin(9600);
}

float low_pass1(float x) {
  lp_out1 = lp_out1 + lp_alpha1 * (x - lp_out1);
  return lp_out1;
}

float low_pass2(float x) {
  lp_out2 = lp_out2 + lp_alpha2 * (x - lp_out2);
  return lp_out2;
}

void loop() {
  senzor1 = low_pass1(analogRead(EMG1));
  senzor2 = low_pass2(analogRead(EMG2));
  if(senzor1-senzor2>50){ 
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    for(int i=1;i<6;i++){
      if(pos[i] > 110) pos[i] = 110;
      else pos[i]+=5;
      motor[i].write(pos[i]);
    }
  }
  else if(senzor2-senzor1>50){
    for(int i=1;i<6;i++){
      if(pos[i] < 0) pos[i] = 0;
      else pos[i]-=5;
      motor[i].write(pos[i]);
    }
    digitalWrite(b,HIGH);
    digitalWrite(a,LOW);
  }
  else{
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
  }
  Serial.print("Senzor 1: ");
  Serial.print(senzor1);
  Serial.print(", Senzor 2: ");
  Serial.print(senzor2);
  Serial.print(".\n");
  
}

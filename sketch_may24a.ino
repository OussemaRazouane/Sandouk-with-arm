#include <Servo.h>

// Moteur imin
#define ad 5
#define rd 6

// Moteur isar
#define ag 9
#define rg 10

//servo
#define s1pin 3
#define s2pin 11
Servo s1;
Servo s2;
int s1Val=0,s2Val=0;//tous les servo sont a l etat 0

//SERVO OR MOTOR
bool changer=1;

//speed
#define speed 180
void Avancer(int sp) {
  analogWrite(ag, sp); //full forward drive for left side motors
  analogWrite(rg,0);   //zero reverse drive for left side motors
  analogWrite(ad,sp);  //full forward drive for right side motors
  analogWrite(rd,0);    //zero reverse drive for right side motors
}

void Reculer(int sp) {
    analogWrite(ag, 0);   //zero forward drive for left side motors
    analogWrite(rg,sp); //full reverse drive for left side motors
    analogWrite(ad,0);    //zero forward drive for right side motors
    analogWrite(rd,sp);  //full reverse drive for right side motors

}
void Gauche(int sp) {
    analogWrite(ag, 0);   //zero forward drive for left side motors
    analogWrite(rg,sp); //full reverse drive for left side motors
    analogWrite(ad,sp);    //zero forward drive for right side motors
    analogWrite(rd,0);  //full reverse drive for right side motors
}
void Droite(int sp) {
    analogWrite(ag, sp);   //zero forward drive for left side motors
    analogWrite(rg,0); //full reverse drive for left side motors
    analogWrite(ad,0);    //zero forward drive for right side motors
    analogWrite(rd,sp);  //full reverse drive for right side motors
}
void Stop() {
  analogWrite(ad, 0);
  analogWrite(ag, 0);
  analogWrite(rg, 0);
  analogWrite(rd, 0);
}
int verif(int val){
  if(val>180){
    return 180;
  }else if(val<0){
    return 0;
  }
  return val;
}
void setup() {
  //motor setup
  pinMode(ad, OUTPUT);
  pinMode(rd, OUTPUT);
  pinMode(ag, OUTPUT);
  pinMode(rg, OUTPUT);

  //servo setup
  s1.attach(s1pin);  // attaches the servo on pin s1pin to the servo object
  s2.attach(s2pin);
  
  //Bluttoth
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    char donnee=Serial.read();
    switch(donnee){
      case 'F':
        if (changer){
          Avancer(speed);
        }else{
          s1Val++;
          s1Val=verif(s1Val);
          s1.write(s1Val);
        }
        break;
      case 'B':
         if (changer){
          Reculer(speed);
        }else{
          s1Val--;
          s1Val=verif(s1Val);
          s1.write(s1Val);
        }
        break;
      case 'R':
        if (changer){
          Droite(speed);
        }else{
          s2Val++;
          s2Val=verif(s2Val);
          s2.write(s2Val);
        }
        break;
      case 'L':
        if (changer){
          Gauche(speed);
        }else{
          s2Val--;
          s2Val=verif(s2Val);
          s2.write(s2Val);
        }
        break;
      case 'V':
        changer=0;
        break;
      case 'v':
        changer=1;
        break;
      default:
        Stop();
        break;
    }
  }
}
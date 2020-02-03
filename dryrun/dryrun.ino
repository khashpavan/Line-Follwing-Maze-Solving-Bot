#define leftFarSensor     13
#define leftNearSensor    12
#define CenterSensor      10
#define CenterSensor2     9
#define rightNearSensor   7
#define rightFarSensor    6
 

int leftFarReading;
int leftNearReading;
int CenterReading;
int CenterReading2;
int rightNearReading;
int rightFarReading;

 int leftNudge;
int replaystage;
int rightNudge;


char path[30] = {};
int pathLength;
int readLength;


/*int redPin = 6;
int greenPin = 9;
int bluePin = 10;*/

#define leapTime 100
 
#define leftMotor1  3
#define leftMotor2  2
 
#define rightMotor1 4
#define rightMotor2 5
 
void straight();
void HLHL();
void LLLL();
void LHHL();
void turnLeft();
void turnRight();
void HLLH();
void done();
void LLHL();
void HLLL();
void turnAround();
void readSensors();

void setup() {
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(CenterSensor, INPUT);
  pinMode(CenterSensor2, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
   
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  analogWrite(A0,130);
  analogWrite(A1,130);

}

void loop() {
  readSensors();
 
  if(leftFarReading == 0 && (CenterReading==1 || CenterReading2 == 1) && rightFarReading == 0 ){
      straight();    
    }

  else if(leftFarReading == 1  && rightFarReading == 0){
      turnLeft();    
     
    }
  else if(rightFarReading == 1 && CenterReading2 == 1){
    if(leftFarReading == 1){
        HLHL();
       delay(leapTime);
      LLLL();
      delay(20);
     
      readSensors();
     if (leftFarReading == 1 && CenterReading ==1 && CenterReading2 == 1 && rightFarReading == 1){
        done();        
        }
       
      else if(leftFarReading ==0 ){
        turnLeft();      
        }
     
      }
     else{
     HLHL();
     delay(leapTime-80);
     LLLL();
      readSensors();
      if(CenterReading == 0 && CenterReading2 == 0){
        turnRight();
        }        
       
      }
   }
  else{
    turnAround();
   
    }
}

void readSensors(){
  leftFarReading     = digitalRead(leftFarSensor);
  leftNearReading    = digitalRead(leftNearSensor);      
  CenterReading = digitalRead(CenterSensor);
  CenterReading2 = digitalRead(CenterSensor2);
  rightNearReading   = digitalRead(rightNearSensor);
  rightFarReading    = digitalRead(rightFarSensor);
  /*Serial.println(leftFarReading);
  Serial.println(leftNearReading);
  Serial.println(CenterReading);
  Serial.println(CenterReading2);
  Serial.println(rightNearReading);
  Serial.println(rightFarReading);*/
 
   
}



void HLHL()
{
  //Serial.println("straight");
digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
}
void LLLL()
{
digitalWrite(leftMotor1, LOW);
digitalWrite(leftMotor2, LOW);
digitalWrite(rightMotor1, LOW);
digitalWrite(rightMotor2, LOW);
}
void LHHL()
{
digitalWrite(leftMotor1, LOW);
digitalWrite(leftMotor2, HIGH);
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
}
void HLLH()
{
 
digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
digitalWrite(rightMotor1, LOW);
digitalWrite(rightMotor2, HIGH);
}
void LLHL()
{
digitalWrite(leftMotor1, LOW);
digitalWrite(leftMotor2, LOW);
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
}
void HLLL()
{
   
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}
void LHLL()
{
   
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}



void straight(){
 
  //readSensors();
  if(digitalRead(CenterSensor2) == 0 &&  leftFarReading == 0 && rightFarReading == 0){
    LLHL();
    delay(3);
    return;
  }
  if(digitalRead(CenterSensor) == 0 && leftFarReading == 0 && rightFarReading == 0){
    HLLL();
    delay(3);
    return;
  }
  HLHL();
  delay(10);
  LLLL();
  delay(30);


}
void turnLeft(){
  /*LHHL();
  delay(180);*/

  while(digitalRead(leftNearSensor)==1){
   LHHL();
    delay(10);
   LLLL();
    delay(20);
  }
 
 
  while(!(digitalRead(CenterSensor)==1 && digitalRead(leftFarSensor) ==0 )){
     LHHL();
     delay(10);
    LLLL();
    delay(20);
   
  }  
 
  }

void turnRight(){
  HLLH();
  delay(60);
 
  while(digitalRead(rightNearSensor)==1){
     HLLH();
     delay(10);
     LLLL();
    delay(20);
  }  
  while(!(digitalRead(CenterSensor2)==1 && digitalRead(rightFarSensor) ==0 )){
    HLLH();
    delay(10);
    LLLL();
    delay(20);
   }
  }

void turnAround(){
    HLHL();
    delay(60);
    HLLH();
    while(!(CenterReading == 1 && CenterReading2 == 1)){
     delay(10);
     LLLL();
     delay(20);
     readSensors();
     HLLH();
     
     
     
     }
 
  }  
void done(){
  LLLL();
  delay(3000);
 
 
  }  

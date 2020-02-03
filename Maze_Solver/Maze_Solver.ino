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

float leftFarReading_; 
float leftNearReading_;
float CenterReading_;
float CenterReading2_; 
float rightNearReading_; 
float rightFarReading_;


 int leftNudge; 
int replaystage; 
int rightNudge; 


char path[30] = {};
int pathLength;
int readLength;


/*int redPin = 6;
int greenPin = 9;
int bluePin = 10;*/

#define leapTime 110 
 
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
void shortPath();
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
      delay(40);
      
      readSensors();
     if ((leftFarReading == 1 || leftNearReading == 1) && CenterReading ==1 && CenterReading2 == 1 && (rightNearReading == 1 || rightFarReading == 1 )){
        done();        
        }
        
      else if(leftFarReading ==0 ){ 
        turnLeft();      
        }
     
      }
     else{
      HLHL();
      delay(leapTime-65);
      LLLL();
      readSensors();
      if(CenterReading == 0 && CenterReading2 == 0){
        turnRight();
        } 
       else{
        path[pathLength]='S';
        pathLength++;
        if(path[pathLength-2]=='B'){
          shortPath();
          }
        
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

/*void moveinch(int n){
 while(n>0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(8);

    n = n-1;
 }}
*/
/*void sensorsAVG(){
  int h = 6;

  leftCenterReading_ = 0;
  leftNearReading_ = 0;
  leftFarReading_ = 0;
  centerReading_ = 0;
  rightCenterReading_ = 0;
  rightNearReading_ = 0;
  rightFarReading_ = 0;
  
  while(h>=0){  
  leftCenterReading_  += digitalRead(leftCenterSensor);
  leftNearReading_    += digitalRead(leftNearSensor);
  leftFarReading_    += digitalRead(leftFarSensor);
  centerReading_     += digitalRead(CenterSensor);
  rightCenterReading_ += digitalRead(rightCenterSensor);
  rightNearReading_   += digitalRead(rightNearSensor);
  rightFarReading_    += digitalRead(rightFarSensor); 
   
  h-=1;
  }

  leftCenterReading_ /= 6;
  leftNearReading_ /= 6;
  leftFarReading_ /= 6;
  centerReading_ /= 6;
  rightCenterReading_ /= 6;
  rightNearReading_ /= 6;
  rightFarReading_ /= 6;
  
  
  
  }*/


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
  delay(2);
  LLLL();
  delay(8);


}
void turnLeft(){
  LHHL();
  delay(30);

  while(digitalRead(leftNearSensor)==1){ 
   LHHL(); 
    delay(7); 
   LLLL();
    delay(20); 
  } 
 
  
  while(!(digitalRead(CenterSensor)==1 && digitalRead(leftFarSensor) ==0 )){
     LHHL();
     delay(7);
    LLLL();
    delay(20);
    
  }


  if(replaystage==0){
  path[pathLength]='L';
  pathLength++;
  if(path[pathLength-2]=='B'){
    shortPath();
    }
  }
  
  }

void turnRight(){
  HLLH();
  delay(70);
  
  while(digitalRead(rightNearSensor)==1){ 
     HLLH(); 
     delay(7); 
     LLLL();
    delay(20); 
  }  
  while(!(digitalRead(CenterSensor2)==1 && digitalRead(rightFarSensor) ==0 )){
    HLLH(); 
    delay(7); 
    LLLL(); 
    delay(20); 
   }

  if(replaystage==0){
  path[pathLength]='R';
  pathLength++;
  if(path[pathLength-2]=='B'){
    shortPath();
    }
  }
  }

void turnAround(){
    HLHL();
    delay(20);
    HLLH();
    while(!(CenterReading == 1 && CenterReading2 == 1)){
     delay(7);
     LLLL();
     delay(20);
     readSensors();
     HLLH();
     
     }
  path[pathLength]='B';
  pathLength++;
  straight(); 
  
  }  
void done(){
  LLLL();

  replaystage=1;
  path[pathLength]='D';
  pathLength++;

  printPath();
  delay(6000);

  replay();
  
  
  }

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    //Serial.println("test6");
    shortDone=1;
  }
  
  //path[pathLength+1]='D';
  //path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}

void replay(){
   readSensors();
  if(leftFarReading == 0 && (CenterReading==1 || CenterReading2 == 1) && rightFarReading == 0){
    straight();
  }
  else{
    if(path[readLength]=='D'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}

void endMotion(){
    delay(500);
  endMotion();
}

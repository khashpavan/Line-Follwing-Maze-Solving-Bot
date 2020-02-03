#define leftFarSensor     A4 
#define leftNearSensor    A3
#define CenterSensor      A2
#define rightNearSensor   A1 
#define rightFarSensor    A0
#define COMMON_ANODE 

int leftFarReading; 
int leftNearReading;
int CenterReading; 
int rightNearReading; 
int rightFarReading; 

 int leftNudge; 
int replaystage; 
int rightNudge; 

int redPin = 6;
int greenPin = 9;
int bluePin = 10;

#define leapTime 200 
 
#define leftMotor1  2
#define leftMotor2  4 
 
#define rightMotor1 12 
#define rightMotor2 8

#define led 13 
 
char path[30] = {}; 
int pathLength; 
int readLength; 
void straight();
void HLHL();
void LLLL();
void LHHL();
void turnLeft();
void turnRight();
void HLLH();
void LLHL();
void HLLL();
void done();
void shortPath();
void turnAround();
void readSensors();
void leftHandWall();

void setup()
{ 
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT); 
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(CenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
    
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
 pinMode(12, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  digitalWrite(12,HIGH); 
  Serial.begin(9600);
  digitalWrite(led, HIGH);
  digitalWrite(7, HIGH);
  delay(1000);
  analogWrite(3,90);
  analogWrite(5,100);
}
void loop(){ 
   readSensors();                                                                                      
  if(leftFarReading==0 && rightFarReading==0)
  {
     straight();
  } 
  else{                                                                                               
    leftHandWall();                                                                                    
  } 
 
} 

void readSensors(){ 
  leftFarReading     = digitalRead(leftFarSensor); 
  leftNearReading    = digitalRead(leftNearSensor);      
  CenterReading = digitalRead(CenterSensor); 
  rightNearReading   = digitalRead(rightNearSensor); 
  rightFarReading    = digitalRead(rightFarSensor);   
}

void leftHandWall(){ 
  //LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
  if(leftFarReading==1){ 
    HLHL(); 
    delay(leapTime); 
    readSensors(); 
       
      if(leftFarReading==0 && rightFarReading==0){
        turnLeft(); 
      } 
      else{ 
        done(); 
      } 
  } 
  //TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
   /* if( leftFarReading==1 && rightFarReading==1)
    { 
      HLHL(); 
      delay(leapTime); 
      readSensors(); 
          if(leftFarReading==1 || rightFarReading==1){ 
               done(); 
            } 
          if(leftFarReading==0 && rightFarReading==0){  
               turnLeft(); 
            } 
    } */
  //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR 
  else{ 
  if(rightFarReading==1){ 
    HLHL(); 
    delay(30); 
    readSensors(); 
     
    /*if(leftFarReading==1){  
       delay(leapTime-30); 
      readSensors(); 
       */
      if(rightFarReading==1 && leftFarReading==1){ 
        done(); 
      } 
      if(CenterReading==1){ 
        straight();
        path[pathLength]='S';
        pathLength++;
        if(path[pathLength-2]=='B') 
          shortPath();}
       else{
        turnRight();
        } 
    
     /*delay(leapTime-30); 
    readSensors(); 
    if(leftFarReading==0 && CenterReading==0 && rightFarReading==0){ 
      turnRight(); 
      return; 
    } 
   path[pathLength]='S'; 
    pathLength++; 
    if(path[pathLength-2]=='B'){ 
    
    shortPath(); 
     } 
    straight(); 
  }*/
  //UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU 
  readSensors(); 
  if(leftFarReading==0 && CenterReading==0 && rightFarReading==0 && leftNearReading==0 && rightNearReading==0){ 
    turnAround(); 
  } 
 
}
}}
//ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
void done(){ 
  LLLL(); 
  replaystage=1; 
  path[pathLength]='D'; 
  pathLength++; 
  
 delay(500); 
  replay(); 
} 
//llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll
void turnLeft()
{ 
   while(digitalRead(leftNearSensor)==1){ 
   LHHL(); 
    delay(20); 
   LLLL();
    delay(10); 
  } 
   while(digitalRead(CenterSensor)==1){ 
  LHHL(); 
    delay(20); 
   LLLL();
    delay(10);
   }
   HLHL();        //move straight
     if(replaystage==0){ 
    path[pathLength]='L'; 
     
    pathLength++; 
      if(path[pathLength-2]=='B'){ 
     
        shortPath(); 
      } 
  } 
} 
//rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
void turnRight(){ 
 
     
  while(digitalRead(rightNearSensor)==1){ 
     HLLH(); 
     delay(20); 
     LLLL();
    delay(10); 
  }  
   while(digitalRead(CenterSensor)==1){
    HLLH(); 
    delay(20); 
    LLLL(); 
    delay(10); 
   }
   HLHL();
   
  if(replaystage==0){ 
  path[pathLength]='R'; 
  Serial.println("r"); 
  pathLength++; 
  Serial.print("Path length: "); 
  Serial.println(pathLength); 
    if(path[pathLength-2]=='B'){ 
      Serial.println("shortening path"); 
      shortPath(); 
    } 
  } 
  
} 
 void straight(){
  HLHL;
  delay(10); 
  if( digitalRead(leftNearSensor)==1){  
    LLHL(); 
    delay(5);
     HLHL(); 
  } 
  if(digitalRead(rightNearSensor)==1){ 
     HLLL(); 
     delay(5);
    HLHL();  
  } 
   
    HLHL(); 
    delay(5); 
} 
void turnAround(){ 
   while(digitalRead(CenterSensor)==1){ 
    LHHL(); 
    delay(2); 
     LLLL(); 
    delay(1); 
  } 
  HLHL();
  path[pathLength]='B'; 
  pathLength++; 
  straight(); 
  } 
 
void shortPath(){ 
 int shortDone=0; 
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){ 
    pathLength-=3; 
    path[pathLength]='B'; 
    Serial.println("test1"); 
    shortDone=1; 
  } 
    
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){ 
    pathLength-=3; 
    path[pathLength]='R'; 
    Serial.println("test2"); 
      shortDone=1; 
  } 
    
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){ 
    pathLength-=3; 
    path[pathLength]='B'; 
    Serial.println("test3"); 
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
    Serial.println("test5"); 
    shortDone=1; 
  } 
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){ 
    pathLength-=3; 
    path[pathLength]='S'; 
    Serial.println("test6"); 
    shortDone=1; 
  } 
   path[pathLength+1]='D'; 
  path[pathLength+2]='D'; 
  pathLength++; 
  Serial.print("Path length: "); 
  Serial.println(pathLength); 
  printPath(); 
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
 void replay(){ 
   readSensors(); 
  if(leftFarReading==0 && rightFarReading==0){ 
    straight(); 
  } 
  else{ 
    if(path[readLength]=='D'){ 
       HLHL(); 
    delay(100); 
     LLLL(); 
      endMotion(); 
    } 
    if(path[readLength]=='L'){ 
     HLHL(); 
    delay(leapTime); 
      turnLeft(); 
    }
     if(path[readLength]=='R'){ 
       HLHL(); 
    delay(leapTime); 
    turnRight(); 
    } 
    if(path[readLength]=='S'){ 
       HLHL(); 
      delay(leapTime); 
    straight(); 
    } 
     
    readLength++; 
  } 
     
  replay(); 
   
} 
 void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

 void HLHL()
{
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
  
void endMotion()
{  
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(500);
  endMotion();
}

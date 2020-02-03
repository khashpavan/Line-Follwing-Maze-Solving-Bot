const int lineFollowSensor0 = 12; //Using Digital input
const int lineFollowSensor1 = 18; //Using Analog Pin A4 as Digital input
const int lineFollowSensor2 = 17; //Using Analog Pin A3 as Digital input
const int lineFollowSensor3 = 16; //Using Analog Pin A2 as Digital input
const int lineFollowSensor4 = 19; //Using Analog Pin A5 as Digital input
const int farRightSensorPin = 0;  //Analog Pin A0
const int farLeftSensorPin = 1;   //Analog Pin A1
int LFSensor[5]={0, 0, 0, 0, 0};
int farRightSensor = 0;
int farLeftSensor = 0;
LFSensor[0] = digitalRead(lineFollowSensor0);
LFSensor[1] = digitalRead(lineFollowSensor1);
LFSensor[2] = digitalRead(lineFollowSensor2);
LFSensor[3] = digitalRead(lineFollowSensor3);
LFSensor[4] = digitalRead(lineFollowSensor4);
farRightSensor = analogRead(farRightSensorPin);
farLeftSensor = analogRead(farLeftSensorPin);
void readLFSsensors()
void testSensorLogic(void) 
{
  Serial.print (farLeftSensor);
  Serial.print (" <== LEFT RIGH==> ");
  Serial.print (farRightSensor);
  Serial.print (" mode: ");
  Serial.print (mode);
  Serial.print (" error:");
  Serial.println (error);
}
void loop()
{
  readLFSsensors();
  switch (mode)
  {
    case NO_LINE:
       motorStop();
       goAndTurn (LEFT, 180);
       break;
    case CONT_LINE:
       runExtraInch();
       readLFSsensors();
       if (mode == CONT_LINE) mazeEnd();
       else goAndTurn (LEFT, 90); // or it is a "T" or "Cross"). In both cases, goes to LEFT
       break;
    case RIGHT_TURN:
       runExtraInch();
       readLFSsensors();
       if (mode == NO_LINE) goAndTurn (RIGHT, 90);
       break;
    case LEFT_TURN:
       goAndTurn (LEFT, 90);
       break;
    case FOLLOWING_LINE:
       followingLine();
       break;
  }
}
void runExtraInch(void)
{
  motorPIDcontrol();
  delay(extraInch);
  motorStop();
}
void goAndTurn(int direction, int degrees)
{
  motorPIDcontrol();
  delay(adjGoAndTurn);
  motorTurn(direction, degrees);
}
char path[100] = " ";
unsigned char pathLength = 0; // the length of the path
int pathIndex = 0; // used to reach an specific array element.
path = [LBLLLBSBLLBSLL]
and pathLengh = 14
path = [LBLLLBSBLLBSLL] ==> LBL = S
path = [SLLBSBLLBSLL] ==> LBS = R
path = [SLRBLLBSLL] ==> RBL = B
path = [SLBLBSLL] ==> LBL = S
path = [SSBSLL] ==> SBS = B
path = [SBLL] ==> SBL = R
path = [RL]
unsigned int status = 0; // solving = 0; reach Maze End = 1
void mazeSolve(void)
{
    while (!status)
    {
        readLFSsensors();  
        switch (mode)
        {   
          case NO_LINE:  
            motorStop();
            goAndTurn (LEFT, 180);
            recIntersection('B');
            break;
          
          case CONT_LINE: 
            runExtraInch();
            readLFSsensors();
            if (mode != CONT_LINE) {goAndTurn (LEFT, 90); recIntersection('L');} // or it is a "T" or "Cross"). In both cases, goes to LEFT
            else mazeEnd(); 
            break;
            
         case RIGHT_TURN: 
            runExtraInch();
            readLFSsensors();
            if (mode == NO_LINE) {goAndTurn (RIGHT, 90); recIntersection('R');}
            else recIntersection('S');
            break;   
            
         case LEFT_TURN: 
            goAndTurn (LEFT, 90); 
            recIntersection('L');
            break;   
         
         case FOLLOWING_LINE: 
            followingLine();
            break;      
        
         }
    }
} 
void recIntersection(char direction)
{
  path[pathLength] = direction; // Store the intersection in the path variable.
  pathLength ++;
  simplifyPath(); // Simplify the learned path.
}
void simplifyPath()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if(pathLength < 3 || path[pathLength-2] != 'B')
    return;
  int totalAngle = 0;
  int i;
  for(i=1;i<=3;i++)
  {
    switch(path[pathLength-i])
    {
      case 'R':
        totalAngle += 90;
  break;
      case 'L':
  totalAngle += 270;
  break;
      case 'B':
  totalAngle += 180;
  break;
    }
  }
  // Get the angle as a number between 0 and 360 degrees.
  totalAngle = totalAngle % 360;
  // Replace all of those turns with a single one.
  switch(totalAngle)
  {
    case 0:
  path[pathLength - 3] = 'S';
  break;
    case 90:
  path[pathLength - 3] = 'R';
  break;
    case 180:
  path[pathLength - 3] = 'B';
  break;
    case 270:
  path[pathLength - 3] = 'L';
  break;
  }
  // The path is now two steps shorter.
  pathLength -= 2;
  
} 
void loop() 
{
  ledBlink(1);
  readLFSsensors(); 
  
  mazeSolve(); // First pass to solve the maze
  ledBlink(2);
  while (digitalRead(buttonPin) { }
  pathIndex = 0;
  status = 0;
  
  mazeOptimization(); // Second Pass: run the maze as fast as possible
  ledBlink(3);
  while (digitalRead(buttonPin) { }
  mode = STOPPED;
  status = 0; // 1st pass
  pathIndex = 0;
  pathLength = 0;
}
void mazeOptimization (void)
{
  while (!status)
  {
    readLFSsensors();  
    switch (mode)
    {
      case FOLLOWING_LINE:
        followingLine();
        break;    
      case CONT_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case LEFT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;   
    }    
   }  
}
void mazeTurn (char dir) 
{
  switch(dir)
  {
    case 'L': // Turn Left
       goAndTurn (LEFT, 90);      
       break;   
    
    case 'R': // Turn Right
       goAndTurn (RIGHT, 90);     
       break;   
       
    case 'B': // Turn Back
       goAndTurn (RIGHT, 800);     
       break;   
       
    case 'S': // Go Straight
       runExtraInch(); 
       break;
  }
}
const int adj = 0; 
float adjTurn = 8;
int adjGoAndTurn = 800;
THRESHOLD = 150
const int power = 250; 
const int iniMotorPower = 250; 
int extraInch = 200; 

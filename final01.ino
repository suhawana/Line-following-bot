int CenterSensor     =  A3;
int leftNearSensor   =  A2;
int leftFarSensor  =    A1;
int rightNearSensor =   A4;
int rightFarSensor   =  A5;



// IR Sensor readings
int CenterReading;
int leftNearReading;
int leftFarReading;
int rightNearReading;
int rightFarReading;
int threshold = 150;

int red_led=2;


int left_motor_forward =8;
int left_motor_backward =9;
int right_motor_forward=6;
int right_motor_backward=7;
int left_motor_pwm=10;
int right_motor_pwm=5;


int set_point = 2560;
int max_speed = 200;
//set Max Speed Value
float Kp = 0.0075;//set Kp Value
float Ki =0.0008;//set Ki Value
float Kd =0.55 ;//set Kd Value

int proportional=0;
int integral=0;
int derivative=0;
int last_proportional=0;
int right_speed=0;
int left_speed=0;
int sensors_sum=0;
int sensors_average=0;
int sensors[5]={0,0,0,0,0};
int Position=0;
int error_value=0;


char path[100]={};
char direction;
int pathlength=0;
int pathindex=0;
int shortDone=0;



void pid_calc() 
{
   
  
  proportional=Position-set_point;
  integral = integral + proportional; 
  derivative = proportional - last_proportional; 
  last_proportional = proportional;    
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd);  
                                              //Restricting the error value between +256. 

  left_speed=max_speed-error_value;
  right_speed=max_speed+error_value;

  if(left_speed<0)
  {
    left_speed=0;
  }
  if(left_speed>200)
  {
    left_speed=200;
  }
  if(right_speed<0)
  {
    right_speed=0;
  }
  if(right_speed>200)
  {
    right_speed=200;
  }
}


void Stop()
{
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,LOW);
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  intersection('E');
  Serial.println("straight/n");

}

void forward()
{
  
  digitalWrite(left_motor_forward,HIGH);
  digitalWrite(right_motor_forward,HIGH);
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  analogWrite(left_motor_pwm,left_speed);
  analogWrite(right_motor_pwm,right_speed);
  intersection('S');
  Serial.println("striaght/n");
}


void u_turn() //turn around
{
  
  left_turn();
  left_turn();
  intersection('B');
 Serial.println("backward/n");
  
}




void right_turn()  //hard right turn
{
 
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,0);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,1);
  analogWrite(left_motor_pwm,left_speed);   
  analogWrite(right_motor_pwm,right_speed);
  intersection('R');
  Serial.println("right/n");
  
    //you may have to vary the delay for perfect right turn..
  
}

void left_turn()    //hard left turn
{
  
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,right_speed);
  analogWrite(right_motor_pwm,left_speed);
  intersection('L');
  Serial.println("left/n");
  
    //you may have to vary the delay for perfect right turn..
  
}

void intersection(char direction){

  path[pathlength]=direction;
  pathlength++;

  shortpath();
  for(int i=0;i<pathlength;i++){
    Serial.print(path[i]);
  }

}

void shortpath(){

  if(pathlength>=3 && path[pathlength-2]=='B')
  {
    shortDone=0;
    if(path[pathlength-3] == 'L' && path[pathlength - 1] == 'R')
  {
    pathlength -= 3;
    path[pathlength] = 'B';
    shortDone=1;
  }
  if(path[pathlength-3] == 'L' && path[pathlength - 1] == 'S' && shortDone == 0)
  {
    pathlength -= 3;
    path[pathlength] = 'R';
    shortDone = 1;
  }
  if(path[pathlength-3] == 'R' && path[pathlength - 1] == 'L' && shortDone == 0)
  {
    pathlength-=3;
    path[pathlength] = 'B';
    shortDone=1;
  }
  if(path[pathlength-3] == 'S' && path[pathlength - 1] == 'L' && shortDone == 0)
  {
    pathlength -= 3;
    path[pathlength] = 'R';
    shortDone = 1;
  }
  if(path[pathlength-3] == 'S' && path[pathlength - 1] =='S' && shortDone == 0)
  {
    pathlength-=3;
    path[pathlength] = 'B';
    shortDone=1;
  }
  if(path[pathlength-3] == 'L' && path[pathlength - 1] =='L' && shortDone == 0)
  {
    pathlength -= 3;
    path[pathlength] = 'S';
    shortDone = 1;
  }

}

  else if((path[pathlength-2]=='L' && path[pathlength-3]=='R') || (path[pathlength-2]=='R'&& path[pathlength-3]=='L') && shortDone ==0 ){
    pathlength-=3;
    shortDone=1;
  }
  
}


void readSensors()  //accepts input from sensors
{
  CenterReading      =    analogRead(CenterSensor);
  leftNearReading    =    analogRead(leftNearSensor);
  leftFarReading     =    analogRead(leftFarSensor);
  rightNearReading   =    analogRead(rightNearSensor);
  rightFarReading    =    analogRead(rightFarSensor); 
}


void setup() {

  Serial.begin(9600);
  
  
pinMode  (A1, INPUT);
pinMode  (A2, INPUT);
pinMode  (A3, INPUT);
pinMode  (A4, INPUT);
pinMode  (A5, INPUT);

pinMode (5, OUTPUT);
pinMode (6, OUTPUT);
pinMode (7, OUTPUT);
pinMode (8, OUTPUT);
pinMode (9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(red_led,OUTPUT);
}

void loop ()  
{
  readSensors();
  pid_calc();
    
  if(CenterReading>threshold  && leftNearReading<threshold && leftFarReading<threshold  )
  {
    forward();
   // Serial.print();
  }

         
  else if (leftNearReading>threshold && leftFarReading>threshold)
    {
      left_turn();
     // Serial.print();
    }

  else if(rightNearReading>threshold &&  rightFarReading>threshold && CenterSensor<threshold && leftNearReading<threshold)
    {
     right_turn();
     //Serial.print();
    }




  else if (CenterReading>threshold && leftNearReading>threshold && rightNearReading>threshold)
    {
      u_turn();
     // Serial.print();
    }
   
  else if (CenterReading>threshold  && leftNearReading>threshold && rightNearReading>threshold)
   { forward();
     delay (10);
     Stop();
     readSensors();
     if (leftNearReading>threshold && CenterReading<threshold && rightNearReading<threshold)
      {
        Stop();
        digitalWrite(red_led,HIGH);
        delay(2560);

      }
         else
          {
            left_turn();
          }  
   }
   
}      
  

//============================================================================
//  Ultrasonic Sensor PID Project
//  Always keep the robot car 20 cm away from an obstacle.
//=============================================================================

/*Set motor constant*/
const int left_motor_start = 56;
const int right_motor_start = 41;

/*Set motor port*/
int Right_motor_en = 10; 
int Left_motor_en = 5; 

int Right_motor_go = 9; 
int Right_motor_back = 8; 

int Left_motor_go = 7; 
int Left_motor_back = 6; 

/*Set Button port*/
int key = 13; // Active Low

/*Set BUZZER port*/
int beep = 12; // Active High

/*Ultrasonic sensor variables*/
const int trigPin = A0;
const int echoPin = A1;

/*PID Parameters*/
double Kp = 2;

double Ki = 0.3;

double Kd = 0.2;

double desired = 20;

double actual = 0;

double error = actual - desired;

double last_error = 0;

double derivative = error - last_error;

double integral = 0;

double integral_limit = 20;

int pid_correction = 0;

void setup()
{
  //Initialize motor drive for output mode
  pinMode(Left_motor_go,OUTPUT);
  pinMode(Left_motor_back,OUTPUT);
  pinMode(Right_motor_go,OUTPUT);
  pinMode(Right_motor_back,OUTPUT);
  pinMode(Right_motor_en, OUTPUT);
  pinMode(Left_motor_en, OUTPUT);

  pinMode(key,INPUT);// Set button as input
  pinMode(beep,OUTPUT);// Set buzzer as output

  digitalWrite(beep,LOW);// set buzzer mute
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600); // Starts the serial communication
}

double get_distance()
{
  double duration;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  return duration * 0.034 / 2;
}

void get_pid_correction()
{
  actual = get_distance();

  error = actual - desired;

  integral += error;

  if (last_error * error < 0) // Overshoot case
  {
    integral = 0;
  }
  
  if (integral > integral_limit) // Curb integral part
  {
    integral = integral_limit;
  }

  derivative = error - last_error;
  
  pid_correction = (int)(Kp * error + Ki * integral + Kp * derivative);

  last_error = error;
}

int check_value(int val)
{
  if (val > 255)
  {
    return 255;
  }
  else if (val < 0)
  {
    return 0;
  }
  else
  {
    return val;
  }
}

void run() // go ahead 
{
  get_pid_correction();

  if (pid_correction > 0) // need to move forward
  {
    digitalWrite(Right_motor_go,HIGH);
    digitalWrite(Right_motor_back,LOW); 
  
    digitalWrite(Left_motor_go,HIGH);
    digitalWrite(Left_motor_back,LOW);
  }
  else // need to move backward
  {
    digitalWrite(Right_motor_go,LOW);
    digitalWrite(Right_motor_back,HIGH); 
  
    digitalWrite(Left_motor_go,LOW);
    digitalWrite(Left_motor_back,HIGH);

    pid_correction = -1 * pid_correction;
  }

  analogWrite(Left_motor_en, check_value(left_motor_start + pid_correction));
  analogWrite(Right_motor_en, check_value(right_motor_start + pid_correction));
  
  delay(10);
}

void stop() // stop
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW); 
  
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);

  analogWrite(Left_motor_en,0);
  analogWrite(Right_motor_en,0);
  
  delay(100);
}

void keysacn()
{
  while(digitalRead(key))// When the button is not pressed -- HIGH
  {
    delay(20);
  }
  
  while(!digitalRead(key))// When the button is pressed
  {
    delay(20);
  }
    
  delay(10); //delay 10ms
  
  digitalWrite(beep,HIGH);//The buzzer sounds
  
  delay(50); //delay 50ms
 
  digitalWrite(beep,LOW);//mute

  delay(1000); //delay 1s
}

void loop()
{
    keysacn();//Press the button to start

    while(digitalRead(key))// When the button is not pressed
    {
      run();
    }

    while(!digitalRead(key))// When the button is pressed
    {
      stop();
        
      delay(20);
    }  
}



//============================================================================
//  Path Tracking Project
//=============================================================================

/*Set motor constants*/
const int left_motor_start = 56; // static: 68
const int right_motor_start = 43; // static : 52

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

/*IR sensor*/
const int Sensor_right = A3;     // Set Right Line Walking Infrared sensor port
const int Sensor_left = A2;      // Set Left Line Walking Infrared sensor port

int SR;    // State of Right Line Walking Infrared sensor
int SL;    // State of Left Line Walking Infrared sensor

int ir_correction_left = 0;
int ir_correction_right = 0;

int increase_speed = 17;

bool destination = false;

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

  pinMode(Sensor_right, INPUT);
  pinMode(Sensor_left, INPUT);
}

void get_ir_correction()
{
  SR = digitalRead(Sensor_right);
  SL = digitalRead(Sensor_left);
    
  if (SL == LOW && SR == HIGH)// Left sensor against white undersurface and right against black undersurface , the car left off track and need to adjust to the right.
  {
    ir_correction_left = increase_speed;
    ir_correction_right = -1 * increase_speed;
  }
    
  else if (SR == LOW && SL ==  HIGH) // Rihgt sensor against white undersurface and left against black undersurface , the car right off track and need to adjust to the left.
  {
    ir_correction_left = -1 * increase_speed;
    ir_correction_right = increase_speed;
  }
  else
  {
    ir_correction_left = 0;
    ir_correction_right = 0;

    if (SR == HIGH && SL == HIGH)
    {
      destination = true;
    }
  }
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

void spin()
{
  digitalWrite(Right_motor_go,HIGH);
  digitalWrite(Right_motor_back,LOW); 
  
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
  
  analogWrite(Left_motor_en, 100);
  analogWrite(Right_motor_en, 80);
}

void run() // go ahead 
{
  get_ir_correction();

  if (destination)
  {
    spin();

    delay(2000);

    while (1)
    {
    stop();
    }
  }
  digitalWrite(Right_motor_go,HIGH);
  digitalWrite(Right_motor_back,LOW); 
  
  digitalWrite(Left_motor_go,HIGH);
  digitalWrite(Left_motor_back,LOW);
  
  analogWrite(Left_motor_en, check_value(left_motor_start + ir_correction_left));
  analogWrite(Right_motor_en, check_value(right_motor_start + ir_correction_right));
  
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
  while(digitalRead(key))// When the button is not pressed
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
    
    get_ir_correction();
    
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



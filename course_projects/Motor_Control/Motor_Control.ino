//============================================================================
//  Motor Control Project
//  Once the key is pressed, the robot car moves forward for 3 sec, spins for 2 sec then stop.
//=============================================================================

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

/*Set motor constants*/  
const int left_motor_start = 56; // left motor start speed
const int right_motor_start = 43; // right motor start speed

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
}

void spin()
{
  digitalWrite(Right_motor_go,HIGH);
  digitalWrite(Right_motor_back,LOW); 
  
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
  
  analogWrite(Left_motor_en, 100);
  analogWrite(Right_motor_en, 80);

  delay(10);
}

void run() // go ahead 
{
  digitalWrite(Right_motor_go,HIGH);
  digitalWrite(Right_motor_back,LOW); 
  
  digitalWrite(Left_motor_go,HIGH);
  digitalWrite(Left_motor_back,LOW);
  
  analogWrite(Left_motor_en, 100);
  analogWrite(Right_motor_en, 80);
  
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
  
  delay(10);
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

    run();

    delay(3000);

    spin();

    delay(2000);

    stop();
}



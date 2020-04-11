//============================================================================
//  PWM Experiment
//  Use PWM to control the tone of the speaker
//=============================================================================

/*Set speaker port*/
int beep = 12;

void setup() 
{
  pinMode(beep, OUTPUT);

  digitalWrite(beep, LOW);
}

void pwm(int high, int t)
{
  for (int i = 0; i <t *1000; i++)
  {
    digitalWrite(beep, HIGH);
    delayMicroseconds(high);

    digitalWrite(beep, LOW);
    delayMicroseconds(100 - high);
  }
}

void loop() 
{
  for (int i = 0; i <= 10; i++)
  {
    pwm(i * 10, 10);

    delay(1000);
  }
}

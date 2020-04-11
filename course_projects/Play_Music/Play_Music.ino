//============================================================================
//  Serial Communication Project
//  Use computer keyboard to play music on the robot car speaker
//=============================================================================

/*Set speaker port*/
int beep = 12;

// Scale: C, D, E, F, G, A, B
int tones[] = {261, 294, 329, 349, 392, 440, 493, 523};

char incomingByte;

void setup() 
{
  pinMode(beep, OUTPUT);

  Serial.begin(9600);
}

void play(int frequency)
{
  tone(beep, frequency);

  delay(200);

  noTone(beep);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    
    if (incomingByte == 'c')
    {
      play(tones[0]);
    }
    else if (incomingByte == 'd')
    {
      play(tones[1]);
    }
    else if (incomingByte == 'e')
    {
      play(tones[2]);
    }
    else if (incomingByte == 'f')
    {
      play(tones[3]);
    }
    else if (incomingByte == 'g')
    {
      play(tones[4]);
    }
    else if (incomingByte == 'a')
    {
      play(tones[5]);
    }
    else if (incomingByte == 'b')
    {
      play(tones[6]);
    }
    else if (incomingByte ==' ')
    {
      delay(200);
    }
  }
}

//============================================================================
//  IR Experiment
//=============================================================================

/*IR sensor*/
const int Sensor_right = A3;     // Set Right Line Walking Infrared sensor port
const int Sensor_left = A2;      // Set Left Line Walking Infrared sensor port

double SR;    // State of Right Line Walking Infrared sensor
double SL;    // State of Left Line Walking Infrared sensor

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(Sensor_right, INPUT);
  pinMode(Sensor_left, INPUT);
}

void measure()
{ 
  SR = digitalRead(Sensor_right);
  SL = digitalRead(Sensor_left);

  Serial.print("Left sensor: ");
  Serial.println(SL);

  Serial.print("Right sensor: ");
  Serial.println(SR);

  Serial.println();

  delay(1000);
}

void loop()
{
  measure();  
}




int left_ir = A5;
int right_ir = A4;


void setup() {
  // put your setup code here, to run once:

  pinMode(left_ir, INPUT);
  pinMode(right_ir, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int left_ir_value = digitalRead(left_ir);
  int right_ir_value = digitalRead(right_ir);

  Serial.print("left: ");
  Serial.println(left_ir_value);

  Serial.print("right");
  Serial.println(right_ir_value);

  Serial.println();

  delay(1000);
}

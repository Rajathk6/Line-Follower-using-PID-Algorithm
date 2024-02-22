const int LIN1 = 6; //left motor pin 1
const int LIN2 = 7; //left motor pin 2
const int LEN = 5; //left motor enable
const int RIN1 = 8; //right motor pin 1
const int RIN2= 9; //right motor pin 2
const int REN = 10; //right motor enable

void setup() {
  //setup the pinmode to output as we want an output
  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(RIN1, OUTPUT);
  pinMode(RIN2, OUTPUT);
  pinMode(REN, OUTPUT);
}
void loop() {

  analogWrite(LEN, 255);  // left enable pin is responsible for left motor speed
  analogWrite(REN, 255); // right enable pin is responsible for right motor speed

  digitalWrite(LIN1, HIGH); // left pin 1 when given high moves the left motor forward
  digitalWrite(LIN2, LOW); // left pin 2 when given high moves the left motor backward 
  digitalWrite(RIN1, LOW); // right pin 1 when given high moves the left motor forward
  digitalWrite(RIN2, HIGH); // right pin 2 when given high moves the left motor backward
  
}




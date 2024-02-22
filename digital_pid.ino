float Kp = 3;  // 1.77  1.991149
float Ki = 0.6;  // 0.26  0.3208651
float Kd = 5;   // 3.6  2.52248420
int initial_motor_speed = 200;   // 80 150

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int sensor[3] = {0, 0, 0};


void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup() {
  pinMode(5, OUTPUT);  // PWM Pin 1
  pinMode(10, OUTPUT); // PWM Pin 2
  pinMode(6, OUTPUT);  // Left Motor Pin 1
  pinMode(7, OUTPUT);  // Left Motor Pin 2
  pinMode(8, OUTPUT);  // Right Motor Pin 1
  pinMode(9, OUTPUT);  // Right Motor Pin 2
  Serial.begin(9600);
}

void loop() {
  read_sensor_values();
  calculate_pid();
  motor_control();
}

void read_sensor_values() {
  sensor[0] = digitalRead(A0);
  sensor[1] = digitalRead(A1);
  sensor[2] = digitalRead(A2);

if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1)) {
    error = 2;
} 
else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1)) {
    error = 1;
} 
else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0)) {
    error = 0;
} 
else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0)) {
    error = -1;
} 
else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0)) {
    error = -2;
} 
Serial.print(sensor[0]);
Serial.print("\t");
Serial.print(sensor[1]);
Serial.print("\t");
Serial.print(sensor[2]);
Serial.println(error);
}

void calculate_pid() {
    P = error;
    I = I + previous_I;
    D = error - previous_error;
    PID_value = (Kp * P) + (Ki * I) + (Kd * D);
    previous_I = I;
    previous_error = error;
}

void motor_control() {
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed + PID_value;
  int right_motor_speed = initial_motor_speed - PID_value;

  // The motor speed should not exceed the max PWM value
  constrain(left_motor_speed, 0, 255);
  constrain(right_motor_speed, 0, 255);

  analogWrite(5, initial_motor_speed + PID_value); // Left Motor Speed
  analogWrite(10, initial_motor_speed - PID_value); // Right Motor Speed
  
  if (error ==-2|| error ==-1) {
    // right motor F left motor R
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
  // else if (error ==-1) {
  //   // right motor F left motor R
  //   digitalWrite(6, HIGH);
  //   digitalWrite(7, LOW);
  //   digitalWrite(8, HIGH);
  //   digitalWrite(9, LOW);
  // }
  else if (error ==2 || error ==1) {
    // right motor R left motor F
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  // else if (error ==1) {
  //   // right motor R left motor F
  //   digitalWrite(6, LOW);
  //   digitalWrite(7, HIGH);
  //   digitalWrite(8, LOW);
  //   digitalWrite(9, HIGH);
  // }
  else {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
}

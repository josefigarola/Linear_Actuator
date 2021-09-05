// Motor A connections
// int enA = 9;
// int in1 = 9;
// int in2 = 10;
// encoder
int a = 2;
int b = 3;
volatile int pos = 0;
int ant = 0;

void setup() {
  // Set all the motor control pins to outputs
  // pinMode(enA, OUTPUT);
  // pinMode(in1, OUTPUT);
  // pinMode(in2, OUTPUT);
  pinMode(a,INPUT);
  pinMode(b,INPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(a),readEncoder,LOW);
  
  // Turn off motors - Initial state
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);

  Serial.print("LISTO");
}

void loop() {
  // directionControl();
  // delay(1000);
  // speedControl();
  // delay(1000);
  if(pos != ant){
    Serial.println(pos);
    ant = pos;
  }
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  // analogWrite(enA, 255);
  // analogWrite(enB, 255);

  // Turn on motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
  
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);*/
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    delay(20);
  }
  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

}


void readEncoder(){
  int  = analogRead(enA);
  if(digitalRead(b) == HIGH){
    pos++;
  }
  else{
    pos--;
  }
}

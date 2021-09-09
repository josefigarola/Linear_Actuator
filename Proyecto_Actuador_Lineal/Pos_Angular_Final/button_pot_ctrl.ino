//DC motor controlled by PWM and H-bridge direction change by a interrupt button

//Motor
#define EN 11
#define in1 9
#define in2 10
const int maxSteps = 255;//motor internal steps
//buttons
#define spin 4
//encoder phases
int A = 2;
int B = 3;
unsigned char stateA;
unsigned char stateB;
unsigned char prevA;
//position variables
volatile int Ant=0;
volatile int pos=0;
bool IsCW = true;
//time variables
const int timeTreshold = 5; // spin control can be modified
unsigned long currentTime;
unsigned long loopTime;//time taken on a spin
//motor variables
boolean buttonState = LOW;
int PWM_rot = 0;
int pressed = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN, OUTPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(spin, INPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);

  attachInterrupt(digitalPinToInterrupt(A),encoder,RISING);
  
  //set initial rotation direction
  //time
  currentTime = millis();
  loopTime = currentTime;
  parar();
  Serial.begin(9600);
  Serial.println("PWM   Pos");
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(A0);
  int pwmOut = map(potValue, 0, 1023, 0, 255);

  analogWrite(EN, pwmOut);//send pwm signal to H-bridge

  //Read button-debounce
  if(digitalRead(spin) == true){
    pressed = !pressed;
  }
  while(digitalRead(spin) == true);
  delay(20);

  //if button is pressed - change motor direction 
  if(pressed == true & PWM_rot == 0){
    //Serial.println("clockwise");
    clockwise();
  }
  //if button is pressed - change motor direction
  if(pressed == false & PWM_rot == 1){
    //Serial.println("counterclockwise");
    counterclockwise();
  }
  //encoder();
  if(pos != Ant){
    //Serial.print("Pos: ");
    Serial.print(pwmOut);
    Serial.print("    ");
    Serial.println(pos);
    Ant = pos;
  }
}

void parar(){
  analogWrite(EN, 0); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void clockwise(){
  digitalWrite(in1, HIGH); //adelante ina = 1 out 1 = voltage
  digitalWrite(in2, LOW);
  PWM_rot = 1;
  delay(20);
}
void counterclockwise(){
  digitalWrite(in1, LOW); //adelante ina = 1 out 1 = voltage
  digitalWrite(in2, HIGH);
  PWM_rot = 0;
  delay(20);
}

void encoder(){
  if (digitalRead(B) == HIGH){
    pos--;
  }
  else{
   pos++;
  }
}
/*void encoder(){
  currentTime = millis();
  if(currentTime >= (loopTime + timeTreshold)){
    stateA = digitalRead(A);
    stateB = digitalRead(B);
    if(stateA != prevA){
      if(stateB){//clockwise
        IsCW = true;
        if(pos+1 <= maxSteps) pos++;
      }else{//counterclockwise
        IsCW = false;
        if(pos-1 >= 0) pos--;
      }
    }
    prevA = stateA;//refresh states
    if(Ant != pos){
      Ant = pos;//refresh position
      Serial.print("Position: ");
      Serial.println(pos);
    }
    loopTime = currentTime;//refresh time
  }
}*/

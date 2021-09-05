//////////////////////////////////////////////////////////
//Programa para identificar un motor de DC 
//Jose Miguel Figarola Prado
//////////////////////////////////////////////////////////
//Libreria para el Timer
#include <TimerOne.h>
////////////////////////////////////////////////////////////////

//Declaracion de pines de la placa de Arduino 
//Pines para el giro del motor
const int Pin_1A=13; //Pin Digital del Arduino
const int Pin_2A=12; //Pin Digital del Arduino
const int Pin_EN=11; //Pin PWM del Arduino
const int interruptPin=2; //Pin de interrupcion del Arduino

//Contador de pulsos del Encoder
long unsigned int counter = 0;
//Variable del valor de la señal PWM 
int DutyCycle=0;
//Variable que registre la velocidad en RPM del motor
double Velocidad_en_RPM=0;
//Variable Tiempo
float tiempo=0;

//Funcion del contador
void counting(){
   counter++;
}

//Funcion de RPM
void ISR_RevolucionesPorMinuto(){
   //Velocidad_en_RPM=60*counter/(No.Ranuras_Encoder*T)
   Velocidad_en_RPM=60*counter/(334*0.02);
   tiempo=tiempo+0.02;
 }

//Configuracion de los pines
void setup(){
  //Pines de la placa Arduino en modo de salida
  pinMode(Pin_1A,OUTPUT);
  pinMode(Pin_1A,OUTPUT);
  pinMode(Pin_EN,OUTPUT);
  //Pines de la placa Arduino en modo entrada
  pinMode(interruptPin,INPUT);
  //Giro del motor
  digitalWrite(Pin_1A,LOW);
  digitalWrite(Pin_2A,HIGH);
  
  //Interrupcion(es)
  //La interrupcion Encoder, cada vez que detectemos un flanco
  //de subida en el pin 2 se produce una interrupcion
  attachInterrupt(digitalPinToInterrupt(interruptPin),counting,RISING);
  //Timer 1 del Arduino
  //20000 microsegundos = 0.02 segundos
  Timer1.initialize(20000);

  Timer1.attachInterrupt(ISR_RevolucionesPorMinuto);
  
  Serial.begin(9600);  
}

void loop(){
  //Generacion de la señal PWM
  DutyCycle=random(100,255); //Valor aleatorio de PWM
  analogWrite(Pin_EN,DutyCycle);
  delay(random(100,200));

  counting();
  ISR_RevolucionesPorMinuto();

  Serial.print(DutyCycle);
  Serial.print(" t");
  Serial.println(Velocidad_en_RPM);
  //Se reinicia el contador
  counter=0;

}//Fin del void loop

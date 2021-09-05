const int sensorPin = A0;

void setup()
{
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
}

void loop()
{
   auto raw = analogRead(sensorPin);
   Serial.println(raw);   
   delay(100);
}

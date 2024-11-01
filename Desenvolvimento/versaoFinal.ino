const int buzzerSensor = 4;   // Pino I/O do buzzer
const int pinLED = 7;        // Pino do LED
const int pinSensorTouch = 8; // Pino I/O do sensor capacitivo touch
const int pinMotor = 9;       // Pino I/O do motor de vibr-ação
const int echoPin = 10;      // Pin de recebimento (echo) do sensor ultrassônico
const int trigPin = 11;      // Pin de envio (trigger) do sensor ultrassonico
const int echoPin2 = 12;      // Pin de recebimento (echo) do sensor ultrassônico
const int trigPin2 = 13;      // Pin de envio (trigger) do sensor ultrassonico

long distancia;
long distancia2;


void setup()
{
  pinMode(buzzerSensor, OUTPUT);
  pinMode(pinMotor, OUTPUT);
  pinMode(pinSensorTouch, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(pinLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

 /*
  if (digitalRead(pinSensorTouch) == HIGH) {
    digitalWrite(pinLED, HIGH);
    digitalWrite(buzzerSensor, LOW);
  }
  else{
      digitalWrite(pinLED, LOW);
    digitalWrite(buzzerSensor, HIGH);

  }
  */
  
  distancia = atividadeSensor(trigPin, echoPin);

  distancia2 = atividadeSensor(trigPin2, echoPin2);
  

  Serial.print("Sensor 1 - Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  Serial.print("Sensor 2 - Distancia: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  
if(distancia2 < 50 || distancia < 50 ){
  analogWrite(pinMotor, 255);
  delay(10);

}else if (distancia2 < 100 || distancia < 100 ){
  analogWrite(pinMotor, 200);
  delay(30);

}else if (distancia2 < 150 || distancia < 150 ){
  analogWrite(pinMotor, 150);
  delay(50);
  
}else{
  analogWrite(pinMotor, 100);
  delay(60);
}
  
  delay(100);
}

long microssegundosParaCentimetros(long microssegundos){
	return microssegundos / 29 / 2;
}


      
long atividadeSensor(int trig, int echo){
  long duration;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  return microssegundosParaCentimetros(duration);
}

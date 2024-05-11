const int buzzerSensor = 4;   // Pino I/O do buzzer
const int pinSensorTouch = 8; // Pino I/O do sensor capacitivo touch
const int pinMotor = 9;       // Pino I/O do motor de vibr-ação
const int pinLED = 10;        // Pino do LED
const int trigPin2 = 13;      // Pin de envio (trigger) do sensor ultrassonico
const int echoPin2 = 12;      // Pin de recebimento (echo) do sensor ultrassônico

long distancia;
long distancia2;
long duration;

void setup()
{
  pinMode(buzzerSensor, OUTPUT);
  pinMode(pinMotor, OUTPUT);
  pinMode(pinSensorTouch, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(pinLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

 
  if (digitalRead(pinSensorTouch) == HIGH) {
    digitalWrite(pinLED, HIGH);
    digitalWrite(buzzerSensor, LOW);
  }
  else{
      digitalWrite(pinLED, LOW);
    digitalWrite(buzzerSensor, HIGH);

  }
  distancia2 = atividadeSensor(trigPin2, echoPin2);


  
  Serial.print("Sensor 2 - Distancia: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  
  if(distancia2 < 10 ){
    analogWrite(pinMotor, 255);
    delay(10);

  }else if (distancia2 < 20 ){
    analogWrite(pinMotor, 180);
    delay(30);
  }else{
    analogWrite(pinMotor, 90);
    delay(60);
  }
  
  delay(100);
}

long microssegundosParaCentimetros(long microssegundos){
	return microssegundos / 29 / 2;
}


      
long atividadeSensor(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  return distancia = microssegundosParaCentimetros(duration);
}
const int buzzerSensor = 4;   // Pino I/O do buzzer
const int pinLED = 7;        // Pino do LED
const int pinSensorTouch = 8; // Pino I/O do sensor capacitivo touch
const int pinMotor = 9;       // Pino I/O do motor de vibração
const int echoPin2 = 11;      // Pin de recebimento (echo) do sensor ultrassônico
const int trigPin2 = 12;      // Pin de envio (trigger) do sensor ultrassonico

long distancia2;

unsigned long tempoUltimoToque = 0;  // Variável para armazenar o tempo do último toque
bool alarmeDisparado = false;  

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
    Serial.print("tocou ihu");
    tempoUltimoToque = millis();  
    alarmeDisparado = false;      
    digitalWrite(buzzerSensor, LOW);  
  } 
  else {
    if (millis() - tempoUltimoToque >= 60000 && !alarmeDisparado) {
      alarmeDisparado = true; 
      for (int i = 0; i < 5; i++) {
        digitalWrite(buzzerSensor, HIGH);
        delay(100);
        digitalWrite(buzzerSensor, LOW);
        delay(100);
      }
    }
  }

  
  

  distancia2 = atividadeSensor(trigPin2, echoPin2);
  

  
  Serial.print("Sensor 2 - Distancia: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  
if(distancia2 < 50 ){
  analogWrite(pinMotor, 255);
  delay(10);

}else if (distancia2 < 100 ){
  analogWrite(pinMotor, 200);
  delay(30);

}else if (distancia2 < 150 ){
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

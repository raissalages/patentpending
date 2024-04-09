// Link https://www.tinkercad.com/things/6i8jJUGNK9Q-testedoissensoresultrassonicos
const int trigPin1 = 8;
const int echoPin1 = 7;
const int trigPin2 = 13;
const int echoPin2 = 12;

long distancia;
long distancia1;
long distancia2;
long duration;

void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(gatePin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

 
  // Sensor 1
  distancia1 = atividadeSensor(trigPin1, echoPin1);
  
  // Sensor 2
  distancia2 = atividadeSensor(trigPin2, echoPin2);

  // Imprimir as distâncias
  Serial.print("Sensor 1 - Distancia: ");
  Serial.print(distancia1);
  Serial.println(" cm");
  
  Serial.print("Sensor 2 - Distancia: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  
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

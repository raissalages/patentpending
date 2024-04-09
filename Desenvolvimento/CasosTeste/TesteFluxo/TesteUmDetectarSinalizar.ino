
const int sensorMaxDistance = 330;  // Maximum distance that the sensor can detect
const int sensorMinDistance = 5;    // Minimum distance that the sensor can detect
const int motorDeVibracaoPino = 10; // Vibration Motor Pin
const int pingPin = 7;              // Trigger Pin of Ultrasonic Sensor

int flag, proporcaoDaDistancia;
long duracao, distanciaEmCm;
double porcentagemDaDistancia;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  pinMode(motorDeVibracaoPino, OUTPUT);
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  // read the time of the pulse
  duracao = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  distanciaEmCm = microsegundosParaCentimetros(duracao);

  // if the distance is different from the previous distance, calculate the proportion of the distance and turn on the vibration motor
  if (flag != distanciaEmCm)
  {
    porcentagemDaDistancia = (double)distanciaEmCm / sensorMaxDistance;

    proporcaoDaDistancia = porcentagemDaDistancia * 12;
    Serial.print("Pin Proportion: ");
    Serial.print(proporcaoDaDistancia);
    Serial.println();

    // if the distance is less than 5 distanciaEmCm or more than 330 distanciaEmCm, turn off the vibration motor
    if (distanciaEmCm <= sensorMaxDistance && distanciaEmCm >= sensorMinDistance)
    {
      for (int i = 0; i <= proporcaoDaDistancia; i++)
      {
        analogWrite(motorDeVibracaoPino, 255 - (porcentagemDaDistancia * 255));
        Serial.print(255 - (porcentagemDaDistancia * 255));
        Serial.println();
      }
      delay(300);
    }
    else
    {
      analogWrite(motorDeVibracaoPino, 0);
    }
  }
  // update the flag with the current distance
  flag = distanciaEmCm;

  Serial.print(distanciaEmCm);
  Serial.print("Distancia em cm:");
  Serial.println();

  delay(100);
}

long microsegundosParaCentimetros(long microsegundos)
{
  return microsegundos / 29 / 2;
}

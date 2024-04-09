#include <Adafruit_NeoPixel.h>

// Led Strip Logic
const int numeroDePixels = 12;
const int pinoDoLed = 2;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(numeroDePixels, pinoDoLed, NEO_GRB + NEO_KHZ800);

const int sensorMaxDistance = 330;  // Maximum distance that the sensor can detect
const int sensorMinDistance = 5;    // Minimum distance that the sensor can detect
const int motorDeVibracaoPino = 10; // Vibration Motor Pin
const int pingPin = 7;              // Trigger Pin of Ultrasonic Sensor

int flag, proporcaoDaDistancia;
long duracao, distanciaEmCm;
double porcentagemDaDistancia;

void setup()
{
  ledStrip.begin(); // Initialize the ledStrip
  ledStrip.show();

  Serial.begin(9600);
  pinMode(motorDeVibracaoPino, OUTPUT);
}

void loop()
{
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
  distanciaEmCm = microssegundosParaCentimetros(duracao);

  // if the distance is different from the previous distance, calculate the proportion of the distance and turn on the vibration motor
  if (flag != distanciaEmCm)
  {
    porcentagemDaDistancia = (double)distanciaEmCm / sensorMaxDistance;
    proporcaoDaDistancia = porcentagemDaDistancia * 12;

    Serial.print("Proporcao de distancia: ");
    Serial.println(proporcaoDaDistancia);
    ledStrip.clear();
    ledStrip.show();
    // if the distance is less than 5 cm or more than 330 cm, turn off the vibration motor
    if (distanciaEmCm <= sensorMaxDistance && distanciaEmCm >= sensorMinDistance)
    {
      for (int i = 0; i <= proporcaoDaDistancia; i++)
      {
        analogWrite(motorDeVibracaoPino, 255 - (porcentagemDaDistancia * 255));
        ledStrip.setPixelColor(i, ledStrip.Color(255 - (porcentagemDaDistancia * 255), 0, 0));
        ledStrip.show();
        Serial.print("Quantidade relativa analogica para o motor de vibracao: ");
        Serial.println(255 - (porcentagemDaDistancia * 255));
      }
      delay(300);
    }
    else
    {
      analogWrite(motorDeVibracaoPino, 0);
      ledStrip.clear();
      ledStrip.show();
    }
  }
  // update the flag with the current distance
  flag = distanciaEmCm;

  Serial.print("Distancia em cm:");
  Serial.println(distanciaEmCm);

  delay(100);
}

long microssegundosParaCentimetros(long microssegundos)
{
  return microssegundos / 29 / 2;
}

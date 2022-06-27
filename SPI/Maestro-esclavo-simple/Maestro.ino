/* PROGRAMA DE LA ARDUINO MAESTRA */

#include<SPI.h>
#define PUSLADOR 2
#define LED 4

int ValorPulsador;

void setup (void)

{
  Serial.begin(115200);

  pinMode(PUSLADOR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  SPI.begin(); // Inicializamos el protocolo SPI
  SPI.setClockDivider(SPI_CLOCK_DIV8); // Colocamos el divisor del reloj en 8
  digitalWrite(SS, HIGH); // Esclavo deshabilitado
}

void loop(void)
{
  // Variables para guardar la data a enviar/recibir
  byte Enviar, Recibido;

  ValorPulsador = !digitalRead(PUSLADOR);

  if (ValorPulsador == HIGH)
  {
    Enviar = 1; // Se enviara un 1 al esclavo
  }
  else
  {
    Enviar = 0; // Se enviara un 0 al esclavo
  }

  // Le decimos al esclavo que queremos enviar data
  digitalWrite(SS, LOW);

  Recibido = SPI.transfer(Enviar);
  /* Se envian los datos al esclavo y si este nos envia datos lo guardamos en Recibido*/

  if (Recibido == 1)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  digitalWrite(SS, HIGH); // Esclavo deshabilitado
}

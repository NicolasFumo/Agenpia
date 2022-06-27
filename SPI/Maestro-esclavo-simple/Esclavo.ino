/* PROGRAMA DE LA ARDUINO ESCLAVA*/

#include<SPI.h>
#define PUSLADOR 2
#define LED 4

// Variables volatiles porque seran manejadas por la funcion ISR(Interrupt Service Routines)
volatile boolean Recibido; // Indica si se recibio algun valor
volatile byte EsclavoRecibido, EsclavoEnviar; // valor leido y enviado al maestro

int ValorPulsador; // Lectura del pulsador

void setup()

{
  Serial.begin(115200);

  pinMode(PUSLADOR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  pinMode(MISO, OUTPUT); // Salida de datos

  // Habilita el bus SPI en modo esclavo
  // usando el registro SPCR del microcontrolador
  SPCR |= _BV(SPE); 

  Recibido = false; // por defecto no se recibio un valor

  SPI.attachInterrupt(); // Se asigna la funcion ISR como interrupcion externa

}

/* Funcion que se ejecuta al recibir datos*/
ISR (SPI_STC_vect)
{
  // SPDR es el bus donde llegan o se envian datos
  EsclavoRecibido = SPDR;
  Recibido = true;
}

void loop()
{
  if (Recibido)
  {
    if (EsclavoRecibido == 1)
    {
      digitalWrite(LED, HIGH);
    }
    else
    {
      digitalWrite(LED, LOW);
    }

    ValorPulsador = !digitalRead(PUSLADOR);

    if (ValorPulsador == HIGH)
    {
      EsclavoEnviar = 1;

    } else
    {
      EsclavoEnviar = 0;
    }

    SPDR = EsclavoEnviar;

    Recibido = false;
  }
}

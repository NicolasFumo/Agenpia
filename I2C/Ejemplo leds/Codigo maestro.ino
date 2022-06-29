#include <Wire.h>

void setup() {
  // Unimos este dispositivo al bus I2C
  Wire.begin();
}

byte pin[] = {2, 3, 4, 5, 6};
byte estado = 0;

void loop() {
  for (int i = 0; i < 5; i++)
  {
    // Comenzamos la transmisión al dispositivo 1
    Wire.beginTransmission(1);

    // Enviamos un byte, será el pin a encender
    Wire.write(pin[i]);

    // Enviamos un byte, L pondrá en estado bajo y H en estado alto
    Wire.write(estado);

    // Paramos la transmisión
    Wire.endTransmission();

    // Esperamos 1 segundo
    delay(1000);
  }

  // Cambiamos el estado
  if (estado == 0)
  {
    estado = 1;
  }
  else
  {
    estado = 0;
  }
}

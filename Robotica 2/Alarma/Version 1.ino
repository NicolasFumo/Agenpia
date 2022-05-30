#define pulsaPuerta 5
#define pulsaVentana 6
#define pulsaActiva 7

#define ledVerde 2
#define ledAmarillo 3
#define ledRojo 4

#define desactivado 0
#define activada 1
#define disparo 2

int estado = 0;

void setup() {
  pinMode(pulsaPuerta, INPUT_PULLUP);
  pinMode(pulsaVentana, INPUT_PULLUP);
  pinMode(pulsaActiva, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
}

void loop() {
  if (digitalRead(pulsaActiva) == LOW) {
    if (estado == desactivado) {
      estado = activada;
    }
    else {
      estado = desactivado;
    }
    delay(200);
  }

  if (estado == activada && digitalRead(pulsaVentana) == LOW) {
    estado = disparo;
  }
  if (estado == activada && digitalRead(pulsaPuerta) == LOW) {
    estado = disparo;
  }

  switch (estado) {
    case activada:
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
      break;
    case desactivado:
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, HIGH);

      break;
    case disparo:
      digitalWrite(ledAmarillo, HIGH);
      break;
  }
}



#define pinLedVerde 2
#define pinLedRojo 3
#define pinLedAmarillo 7
#define pinPulsaActivar 4
#define pinPulsaSensor 5
#define pinZumbador 6
#define pinPulsaVentana 8

#define Desactivada 0
#define Activada 1
#define DisparoPuerta 2
#define DisparoVentana 3

int PulsaActivar = 0;
int PulsaPuerta = 0;
int PulsaVentana = 0;

int Estado = Desactivada;

void setup() {
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinLedAmarillo, OUTPUT);
  pinMode(pinPulsaActivar, INPUT_PULLUP);
  pinMode(pinPulsaSensor, INPUT_PULLUP);
  pinMode(pinPulsaVentana, INPUT_PULLUP);
  pinMode(pinZumbador, OUTPUT);
}

void loop() {
  PulsaActivar = digitalRead(pinPulsaActivar);
  PulsaPuerta = digitalRead(pinPulsaSensor);
  PulsaVentana = digitalRead(pinPulsaVentana);

  if (PulsaPuerta == LOW && Estado == Activada) {
    Estado = DisparoPuerta;
  }
  if (PulsaVentana == LOW && Estado == Activada) {
    Estado = DisparoVentana;
  }

  if (PulsaActivar == LOW) { // Si apreto pulsador para activar/desactivar
    if (Estado == Desactivada) { // si la alarma esta desactivada
      Estado = Activada; // activo la alarma

      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
    }
    else { // si no está desactivada
      Estado = Desactivada; // desactivo la alarma

      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
      delay(200);
      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
    }
    delay(300); // delay anti-rebote
  }

  switch (Estado) {
    case Desactivada:
      digitalWrite(pinLedVerde, HIGH);
      digitalWrite(pinLedRojo, LOW);
      break;
    case Activada:
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedRojo, HIGH);
      digitalWrite(pinLedAmarillo, LOW);
      break;
    case DisparoPuerta:
      digitalWrite(pinZumbador, HIGH);
      digitalWrite(pinLedAmarillo, HIGH);
      break;
    case DisparoVentana:
      digitalWrite(pinZumbador, HIGH);
      digitalWrite(pinLedAmarillo, HIGH);
      break;
  }
}

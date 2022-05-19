#define pinLedVerde 2
#define pinLedRojo 3
#define pinPulsaActivar 4
#define pinPulsaSensor 5
#define pinZumbador 6

int PulsaActivar = 0;
// 0-> Desac. 1-> Activada
int Estado = 0;

void setup() {
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinPulsaActivar, INPUT_PULLUP);
  pinMode(pinPulsaSensor, INPUT_PULLUP);
  pinMode(pinZumbador, OUTPUT);
}

void loop() {
  PulsaActivar = digitalRead(pinPulsaActivar);

  if (PulsaActivar == LOW) { // Si apreto pulsador para activar/desactivar
    if (Estado == 0) { // si la alarma esta desactivada
      Estado = 1; // activo la alarma
      
      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
    }
    else { // si no está desactivada
      Estado = 0; // desactivo la alarma

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
    case 0:
      digitalWrite(pinLedVerde, HIGH);
      digitalWrite(pinLedRojo, LOW);
      break;
    case 1:
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedRojo, HIGH);
      break;
  }
}

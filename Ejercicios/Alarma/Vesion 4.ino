#define pinLedVerde 2
#define pinLedRojo 3
#define pinLedAmarillo 7
#define pinPulsaActivar 4
#define pinPulsaSensor 5
#define pinZumbador 6
#define pinPulsaVentana 8

#define Boton_1 0xF30CFF00
#define Boton_2 0xE718FF00
#define Boton_3 0xA15EFF00
#define SENSOR 9

#define Desactivada 0
#define Activada 1
#define DisparoPuerta 2
#define DisparoVentana 3

#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C
#include <IRremote.h>      // importa libreria IRremote

int PulsaActivar = 0;
int PulsaPuerta = 0;
int PulsaVentana = 0;

int Estado = Desactivada;

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7



void setup() {
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinLedAmarillo, OUTPUT);
  pinMode(pinPulsaActivar, INPUT_PULLUP);
  pinMode(pinPulsaSensor, INPUT_PULLUP);
  pinMode(pinPulsaVentana, INPUT_PULLUP);
  pinMode(pinZumbador, OUTPUT);

  lcd.setBacklightPin(3, POSITIVE); // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
  lcd.clear();

  IrReceiver.begin(SENSOR, DISABLE_LED_FEEDBACK);
}

void loop() {
  PulsaActivar = digitalRead(pinPulsaActivar);
  PulsaPuerta = digitalRead(pinPulsaSensor);
  PulsaVentana = digitalRead(pinPulsaVentana);

  if (IrReceiver.decode()) {        // si existen datos ya decodificados
    if (IrReceiver.decodedIRData.decodedRawData == Boton_1){
      Estado = Activada; // enciende o apaga componente rojo
      
      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
    }
    

    if (IrReceiver.decodedIRData.decodedRawData == Boton_2){
      Estado = Desactivada; // desactivo la alarma

      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
      delay(200);
      digitalWrite(pinZumbador, HIGH);
      delay(200);
      digitalWrite(pinZumbador, LOW);
    }
    
    if (IrReceiver.decodedIRData.decodedRawData == Boton_3)   // si codigo recibido es igual a Boton_3
    Estado = DisparoPuerta; // enciende o apaga componente azul
    
    IrReceiver.resume();        // resume la adquisicion de datos
  }
  delay (100);

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

      lcd.setCursor(0, 0);
      lcd.print("Est:Desactivada ");

      break;
    case Activada:
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedRojo, HIGH);
      digitalWrite(pinLedAmarillo, LOW);

      lcd.setCursor(0, 0);
      lcd.print("Est:Activada     ");
      lcd.setCursor(0, 1);
      lcd.print("                ");

      break;
    case DisparoPuerta:
      digitalWrite(pinZumbador, HIGH);
      digitalWrite(pinLedAmarillo, HIGH);

      lcd.setCursor(0, 1);
      lcd.print("Disparo Puerta  ");

      break;
    case DisparoVentana:
      digitalWrite(pinZumbador, HIGH);
      digitalWrite(pinLedAmarillo, HIGH);

      lcd.setCursor(0, 1);
      lcd.print("Disparo ventana ");
      break;
  }
}

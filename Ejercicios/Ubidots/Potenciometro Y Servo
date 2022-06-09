#include <Ubidots.h>
#include <Servo.h>      // incluye libreria de Servo

Servo servo1;     // crea objeto

int PULSOMIN = 450;    // pulso minimo en microsegundos
int PULSOMAX = 2550;    // pulso maximo en microsegundos

#define  UBIDOTS_TOKEN ""  // Token extraido de la cuenta de ubidots
#define  WIFI_SSID "Agenpia"      // Nombre red WIFI
#define  WIFI_PASS "agenpia2019"      // Contraseña red WIFI
#define NOMBRE_DISPOSITIVO "" // Nombre con el que veremos a nuestra placa en ubidots
#define PINSERVO D8

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

int valorPotenciometro = 0;
int valor = 0;
int valorServo = 0;

void setup() {
  pinMode(D4, OUTPUT);
  
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
  
  Serial.begin(115200);
  
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
}

void loop() {
  valorPotenciometro = analogRead(A0);

  Serial.println(valorPotenciometro);

  ubidots.add("potenciometro", valorPotenciometro); // Agregamos la variable para ser enviada
  bool enviado = false;

  enviado = ubidots.send(NOMBRE_DISPOSITIVO); // Enviamos toda la data a ubidots

  if (enviado) {
    // Si se enviaron correctamente el IF va a dar verdadero
    Serial.println("Valores enviados al servidor");
  }
  else {
    // Si hubo algun error, puedo mostrar un mensaje en consola
    Serial.println("Error al enviar");
  }

  // recibir datos
  valor = ubidots.get(NOMBRE_DISPOSITIVO, "led");
  if (valor != ERROR_VALUE) {
    Serial.print("Valor del led: ");
    Serial.println(valor);
    if (valor == 0) {
      digitalWrite(D4, HIGH);
    }
    else {
      digitalWrite(D4, LOW);
    }
  }
  else {
    Serial.println("Error obteniendo el valor del led");
  }

  valorServo = ubidots.get(NOMBRE_DISPOSITIVO, "led");
  if (valorServo != ERROR_VALUE) {
    Serial.print("Valor del servo: ");
    Serial.println(valorServo);
    servo1.write(valorServo);
  }
  else {
    Serial.println("Error obteniendo el valor del servo");
  }

  delay(1000);
}

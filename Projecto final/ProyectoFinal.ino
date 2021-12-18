#include <Ubidots.h>
#include <Servo.h>      // incluye libreria de Servo
#include <DHT.h>
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C
#include <FS.h>          // Esta libreria debe estar primero para que todo funcione
#include <WiFiManager.h>

#define  UBIDOTS_TOKEN "BBFF-JoYDxBYA1UPCUc9Z4EZAyQha6u4qR9"  // Token extraido de la cuenta de ubidots
#define NOMBRE_DISPOSITIVO "trabajo-final" // Nombre con el que veremos a nuestra placa en ubidots
#define PINSERVO D5

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
DHT dht(D3, DHT11);
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);
Servo servo1;     // crea objeto

int controlLuz = 0;
int servo = 0;
int PULSOMIN = 450;    // pulso minimo en microsegundos
int PULSOMAX = 2500;    // pulso maximo en microsegundos

void setup() {
  WiFiManager wifiManager;

  //Habilita el reinicio luego de configurar una red wifi
  wifiManager.setBreakAfterConfig(true);

  //Resetea la red wifi cada vez que se enciende - Para testeo
  wifiManager.resetSettings();
  
  if (!wifiManager.autoConnect("clase final", "PassRed1")) {
    Serial.println("Fallo al conectar, reiniciando para reprogramar red");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  //si llegaste hasta aquí, estas conectado a la red
  Serial.println("Conectado! :)");
  
  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
  lcd.setBacklightPin(3, POSITIVE); // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
  lcd.clear();      // limpia pantalla
  dht.begin();
  Serial.begin(115200);
}

void loop() {
  // LECTURA DATOS
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  controlLuz = ubidots.get(NOMBRE_DISPOSITIVO, "luz");
  if (controlLuz != ERROR_VALUE) {
    if (controlLuz == 1) {
      digitalWrite(D0, LOW);
      digitalWrite(D4, HIGH);
    }
    else {
      digitalWrite(D0, HIGH);
      digitalWrite(D4, LOW);
    }
  }
  else {
    Serial.println("Error con led");
  }

  servo = ubidots.get(NOMBRE_DISPOSITIVO, "servo");
  if (servo != ERROR_VALUE) {
    servo1.write(servo);    // ubica el servo a 0 grados
  }
  else {
    Serial.println("Error obteniendo el valor");
  }

  // PROCESAMIENTO



  // SALIDA
  lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
  lcd.print("Temp: ");
  lcd.setCursor(11, 0);
  lcd.print(temperatura);
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.setCursor(11, 1);
  lcd.print(humedad);

  ubidots.add("humedad", humedad); // Agregamos la variable para ser enviada
  ubidots.add("temperatura", temperatura);

  bool enviado = false;
  enviado = ubidots.send(NOMBRE_DISPOSITIVO); // Enviamos toda la data a ubidots

  if (enviado) {
    Serial.println("Valores enviados al servidor");
  }
  else {
    Serial.println("Error al enviar");
  }

  delay(1000);
}

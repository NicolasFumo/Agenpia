#include <Ubidots.h>
#define  UBIDOTS_TOKEN ""  // Token extraido de la cuenta de ubidots
#define  WIFI_SSID ""      // Nombre red WIFI
#define  WIFI_PASS ""      // Contraseña red WIFI
#define NOMBRE_DISPOSITIVO "" // Nombre con el que veremos a nuestra placa en ubidots

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

int valorPotenciometro = 0;
int valor = 0;

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Descomentar para ver mensajes de ubidot por consola
}

void loop() {
  valorPotenciometro = analogRead(A0);
  Serial.println(valorPotenciometro);
  // ubidots.add("nombreEnUbidots", nombreVariable);
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


  valor = ubidots.get(NOMBRE_DISPOSITIVO, "nombreVariable");
  if (valor != ERROR_VALUE) {
    Serial.println(valor);
  }
  else {
    Serial.println("Error obteniendo el valor");
  }

  delay(1000);
}

#include <FS.h>          // Esta libreria debe estar primero para que todo funcione
#include <WiFiManager.h>

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;

  //Habilita el reinicio luego de configurar una red wifi
  wifiManager.setBreakAfterConfig(true);

  //Resetea la red wifi cada vez que se enciende - Para testeo
  wifiManager.resetSettings();
  
  if (!wifiManager.autoConnect("NombreRed", "PassRed")) {
    Serial.println("Fallo al conectar, reiniciando para reprogramar red");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  //si llegaste hasta aquí, estas conectado a la red
  Serial.println("Conectado! :)");


  Serial.println("local ip");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Todo tu codigo aqui
}

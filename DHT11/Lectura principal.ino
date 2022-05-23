#include <DHT.h>
#include <DHT_U.h>

DHT sensor (5, DHT11);

float temperatura;
float humedad;
float sensTermica;

void setup() {
  sensor.begin();
  Serial.begin(9600);
}

void loop() {
  // temperatura = sensor.readTemperature(true); // ºF
  temperatura = sensor.readTemperature(); // ºC
  humedad = sensor.readHumidity();
  // sensTermica = sensor.computeHeatIndex(temperatura, humedad); // ºF
  sensTermica = sensor.computeHeatIndex(temperatura, humedad, false); // ºC

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Humedad: ");
  Serial.println(humedad);

  Serial.print("Sensacion termica: ");
  Serial.println(sensTermica);

  delay(1000);
}

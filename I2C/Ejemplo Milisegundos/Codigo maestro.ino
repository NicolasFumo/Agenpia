#include <Wire.h>

void setup() {
  Wire.begin();        // unirse al bus i2c como master
  Serial.begin(9600);  // configurar monitor serie a 9600
}

void loop() {

  Wire.beginTransmission(23); // Comunicarse con esclavo #23
  Wire.write('S');
  Wire.endTransmission();

  Wire.requestFrom(23, 1);    // Solicitar 1 byte del esclavo #23
  
  byte len = Wire.read();
  
  Wire.requestFrom(23, (int)len);  // Solicitar 'len' byte del esclavo #23
  
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}

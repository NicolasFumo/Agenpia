#include <EEPROM.h>

int numero = 0;

void setup() {
  Serial.begin(9600);

  // bueno para guardar de byte en byte
  EEPROM.write(0, 15); // escribir en una celda de la EEPROM
  EEPROM.read(0); // leer una celda especifica de la EEPROM

  // bueno para tipos que requieren mas de un byte de memoria
  // int -> 2, float -> 4, char [n] -> n espacios en memoria
  EEPROM.put(0, numero);  // escribe datos solo si son diferentes a los que ya
                          // existen en memoria (ahorra escrituras)
  
  EEPROM.get(0, numero);  // lee un dato en memoria del tipo en que se
                          // declaro la variable
}

void loop() {
  // nada por aqui
}

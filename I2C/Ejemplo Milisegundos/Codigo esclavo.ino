#include <Wire.h>

String message;
bool S = false;

void setup() {
  Wire.begin(23);                // unirse al bus i2c con la direccion #23
  Wire.onRequest(eventoSolicitud); // registrar evento de solicitud de datos
  Wire.onReceive(eventoRecepcion); // registrar evento de recepcion de datos
}


void loop() {
  delay(100);
}

void eventoRecepcion(){
    if( Wire.read() == 'S' ){
      S = true;
      message = String( millis() ) + '\n';
    } 
}

// function that executes whenever data is requested by master
void eventoSolicitud() {

  if( S == true ){
    Wire.write(message.length());
    S = false;
  }
  else{
    Wire.println(message);
  }
}

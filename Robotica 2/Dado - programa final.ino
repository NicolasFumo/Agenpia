#define Pulsador 9

byte  numero[10][8] =
{
  { 1, 1, 1, 1, 1, 1, 0, 0 }, // 0
  { 0, 1, 1, 0, 0, 0, 0, 0 }, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0 }, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0 }, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0 }, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0 }, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0 }, // 6
  { 1, 1, 1, 0, 0, 0, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
  { 1, 1, 1, 0, 0, 1, 1, 0 } // 9
};

int nroAleatorio;

void setup() {
  for ( int i = 2; i <= 8 ; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(Pulsador, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  
}
void loop() {

  if(digitalRead(Pulsador) == LOW){
    nroAleatorio = random(0,10);
    delay(300);
  }  
  
  for (int i = 0; i <= 6; i++) {
    digitalWrite(i+2, numero[nroAleatorio][i]);
  }  
}

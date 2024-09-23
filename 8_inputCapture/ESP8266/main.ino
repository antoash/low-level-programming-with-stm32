/*
  This code is used to generate a signal with a rising and falling edge. 
  A Blue LED is connected just to show the transition in state.
*/

#define D1 5

void setup() {
  pinMode(D1, OUTPUT);
}

void loop() {

  digitalWrite(D1, LOW);
  delayMicroseconds(2500000);
  digitalWrite(D1, HIGH);
  delayMicroseconds(5000000);

}

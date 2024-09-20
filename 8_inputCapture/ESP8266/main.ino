#define D1 5

void setup() {
  pinMode(D1, OUTPUT);
}

void loop() {

  digitalWrite(D1, LOW);
  delayMicroseconds(2500000);
  digitalWrite(D1, HIGH);
  delayMicroseconds(5000000);
  digitalWrite(D1, LOW);
  delayMicroseconds(2500000);

}

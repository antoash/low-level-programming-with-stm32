#define LED 16
void setup() {
    // Set baud rate + switch Rx/Tx pins to D7/D8 
    Serial.begin(115200);
    Serial.swap();
    pinMode(LED, OUTPUT);
}

void loop() {
    // Send using UART over Rx/Tx (D7/D8)
    
    delay(5000);
    
    Serial.print("H");
    delay(5000);
    digitalWrite(LED, LOW);

    Serial.print("I");
    delay(5000);
    digitalWrite(LED, HIGH);

    Serial.print("\n");
    delay(5000);
    digitalWrite(LED, LOW);
    
    Serial.print("\r");
    delay(5000);
    digitalWrite(LED, HIGH);

}
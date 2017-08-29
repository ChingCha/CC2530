void setup() {
  Serial.begin(9600);
}

void loop() {

    Serial.write(01);
    delay(1000);
    Serial.write(02);
    delay(1000);
    Serial.write(03);
    delay(1000);
    Serial.write(04);
    delay(1000);
    
}  


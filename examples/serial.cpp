#include <Arduino.h>
#include <avr/io.h>
#include <header.h>

bool ledState = false;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);   
}

void loop() {   
    Serial.println("Hello World!");
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState); 
    // digitalWrite(LED_PIN, HIGH);  
    delay(30); // this must be replaced by millis()
}

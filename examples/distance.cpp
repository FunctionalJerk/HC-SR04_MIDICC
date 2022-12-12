/* 
taken from https://www.14core.com/didispark-attiny85-with-ultrasonic-hc-sr04-sensor/
*/


#include <Arduino.h>
#include <NewPing.h> //Iclud Arduino Pin Library
#define TRIGGER_PIN 3 //HCR04 Trigger set to pin 3
#define ECHO_PIN 5 // HCR04 Echo set to Pin 5
#define RED_PIN 0 // Red light set to Pin 0
#define GREEN_PIN 1 // Green Light set to Pin 1
#define BLUE_PIN 4 // Blue light set to Pin 4 
#define DISTANCE 60 // Distance value
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, DISTANCE); 
 
void setup() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}
void loop() {
    uint8_t distance = sonar.ping_cm();
    if (distance) {
    uint8_t greenValue = map(distance, 1, DISTANCE, 0, 255);  // Mapping the distance range of 0 to 255 Pulse with Modulation value for the green LED
    uint8_t redValue = 255 - greenValue;
    analogWrite(GREEN_PIN, greenValue);
    analogWrite(RED_PIN, redValue);
    digitalWrite(BLUE_PIN, LOW);
    } else {
    digitalWrite(GREEN_PIN, LOW); // GREEN LIGHT Off Out of reading distance range
    digitalWrite(RED_PIN, LOW);   // RED LIGHT off
    digitalWrite(BLUE_PIN, HIGH); // BLUE LIGHT On
    }
    delay(100);
}
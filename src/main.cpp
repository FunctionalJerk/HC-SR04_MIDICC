#include <Arduino.h>
#include <HCSR04.h>
#include <bitset>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define DISTANCE 100
#define TOGGLE_PIN_A 14
#define TOGGLE_PIN_B 15


UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN, DISTANCE); 

float dist = 50.0;
float sens = 0.0;
float lastVal = 0.0; 
const float thresh = 0.5F;

std::bitset<2> toggleState{"01"};

bool ledState = LOW; 

uint8_t midiCur = 0;          // Current state of the midi value; delete 0 if 0 pots
uint8_t midiPre = 0;          // Previous state of the midi value; delete 0 if 0 pots

// MIDI Assignments 
const byte midiCh = 1;   //* MIDI channel to be used
const byte cc = 23;       //* cc-no

void setup() {
  Serial.begin(31250); //**  Baud Rate 31250 for MIDI class compliant jack | 115200 for Hairless MIDI
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TOGGLE_PIN_A, INPUT);
  pinMode(TOGGLE_PIN_B, INPUT);
  digitalWrite(13, LOW);
}

byte getToggleState() {
  toggleState[0] = digitalRead(TOGGLE_PIN_A);
  toggleState[1] = digitalRead(TOGGLE_PIN_B);
  return toggleState;
}

void loop() {
  
  sens = distanceSensor.measureDistanceCm();
  dist = constrain(sens, 0.0F, 50.0F);

  getToggleState();

  switch (toggleState)  {
    case 01:
      midiCur = map(dist, 0.0F, 50.0F, 0, 127);
      break;

    case 10:
      midiCur = map(dist, 0.0F, 50.0F, 127, 0);
      break;
    
    case 11:
      midiCur = 0;        
      break;

    default: 
      midiCur = 64;        
  }  

  if (abs(dist - lastVal) > (thresh)) { 
    if (midiPre != midiCur) {

      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState);

      usbMIDI.sendControlChange (cc, midiCur, midiCh);
      lastVal = dist; 
      midiPre = midiCur;
    }
  }
  while(usbMIDI.read()) {}
}
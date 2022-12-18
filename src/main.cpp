#include <Arduino.h>
#include <HCSR04.h>

#define TRIG_PIN 11
#define ECHO_PIN 12
#define DISTANCE 100
// #define MIDI_NAME {'P', 'h', 'o', 'e', 'n', 'i,', 'g', 's', ' ', 'U', 'S', 'B'}
// #define MIDI_NAME_LEN 12

// struct usb_string_descriptor_struct usb_product_name

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN, DISTANCE);  // Initialize sensor that uses digital pins 11(trig) and 12(echo).

float dist = 50.0;
float sens = 0.0;
float lastVal = 0.0; 
const float thresh = 0.5F;

bool ledState = LOW; 

uint8_t midiCur = 0;          // Current state of the midi value; delete 0 if 0 pots
uint8_t midiPre = 0;          // Previous state of the midi value; delete 0 if 0 pots

// MIDI Assignments 
const byte midiCh = 1;   //* MIDI channel to be used
const byte note = 0;     //* Lowest note to be used; 36 = C2; 60 = Middle C
const byte cc = 23;       //* cc-no

void setup() {
  Serial.begin(31250); //**  Baud Rate 31250 for MIDI class compliant jack | 115200 for Hairless MIDI
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {

  sens = distanceSensor.measureDistanceCm();
  dist = constrain(sens, 0.0F, 50.0F);

  // midiCur = map(dist, 0.0, 55.0, 0, 127);
  midiCur = map(dist, 0.0F, 50.0F, 0, 127);
  // midiCur = (int)midiCur;

  if (abs(dist - lastVal) > (thresh)) { 
    if (midiPre != midiCur) {
      
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState);
      usbMIDI.sendControlChange (cc, midiCur, midiCh);
      lastVal = dist; 
      midiPre = midiCur;
    }
  }
  while(usbMIDI.read()){}
}
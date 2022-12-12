#include <iostream>
#include <Arduino.h>
#include <avr/io.h>
#include <SoftwareSerial.h>
#include <NewPing.h> 
#include <header.h>

namespace std;

// MIDI_CREATE_DEFAULT_INSTANCE();
// Variables:
byte cc = 0;
byte lastValue;   // define the "lastValue" variables
byte lastAValue;
byte thresh = 8;  //try 4 or 8
byte threshA = 2; 
// int chNum = 4;
bool ledState = HIGH;
//float analogValue = 0.0; // define variables for the controller data
// int note = 60;
// short mode = 0;
// bool button = false;
// unsigned long timer = 0; 

int arr[] = {
  0,  // Bank Select (MSB) - Allows user to switch bank for patch selection. Program change used with Bank Select. MIDI can access 16,384 patches per MIDI channel.
  6,  // Data Entry (MSB) - Controls Value for NRPN or RPN parameters.
  64, // Damper Pedal on/off - On/off switch that controls sustain pedal. Nearly every synth will react to CC 64. (See also Sostenuto CC 66)
  65, // Portamento on/off - On/off switch
  66, // Sostenuto Pedal on/off - On/off switch – Like the Sustain controller (CC 64), However, it only holds notes that were “On” when the pedal was pressed.
  67, // Soft Pedal on/off - On/off switch - Lowers the volume of notes played.
  68, // Legato FootSwitch - On/off switch - Turns Legato effect between 2 subsequent notes on or off.
  69, // Hold 2 -	Another way to “hold notes” (see MIDI CC 64 and MIDI CC 66). However notes fade out according to their release parameter rather than when the pedal is released.
  82, // General Purpose MIDI CC Controller - Generic on/off switch - ≤63 off, ≥64 on
  88, // High Resolution Velocity Prefix - Extends the range of possible velocity values
  96, // (+1) Data Increment - Usually used to increment data for RPN and NRPN messages.
  97  // (-1) Data Increment - Usually used to increment data for RPN and NRPN messages.
};

SoftwareSerial midiSerial(0, 1); // digital pins that we'll use for soft serial RX & TX
NewPing sonar(TRIGGER_PIN, ECHO_PIN, DISTANCE); 

// boolean includes(int array[], int element);
boolean includes(int array[], int element) {
 for (int i = 0; i <= MAX_CH; i++) {
      if (array[i] == element) {
        return true;
      }
    }
  return false;
}

void setup() {
  //  launch MIDI
  // midiSerial.begin(31250);
  Serial.begin(9600);
  // pinMode(RED_PIN, OUTPUT);
  // pinMode(GREEN_PIN, OUTPUT);
  // pinMode(BLUE_PIN, OUTPUT);+
  // timer = 0;
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

// Continuous Controller Function
void controlChange(byte ChannelByte, byte ControlNumber, byte ControlValue){
  midiSerial.write(ChannelByte + 0xb0);
  midiSerial.write(ControlNumber);
  midiSerial.write(ControlValue);
}

// // Continuous Note Function
// void noteChange(byte ChannelByte, byte NoteNumber, byte NoteValue){
//   midiSerial.write(ChannelByte + 0xb0);
//   midiSerial.write(NoteNumber);
//   midiSerial.write(NoteValue);
// }

void loop() {
  // timer = millis();
  // this must run continuous, 
  // as soon as millis() exists
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState); 
  // digitalWrite(LED_PIN, HIGH); 
  // chNum = analogRead(AIN_PIN);

  // cc = sonar.ping_cm(); // wrong!?
  Serial.println(cc);
  Serial.println("Hallo!");
  cc = constrain(cc, 0, 254);  
  if(abs(cc - lastValue) > (thresh)) {
    controlChange(0, CH_NUM, cc);
    lastValue = cc;
  }  
  delay(30); // this must be replaced by millis()
}

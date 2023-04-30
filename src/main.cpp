#include <Arduino.h>
#include <NewPing.h>
#include <avr/io.h>
#include <midi_serialization.h>
#include <usbmidi.h>
#include "header.h"

NewPing sonar(TRIG_PIN, ECHO_PIN, MAXVAL); 

int dist = 2500;                    // distance measured by sensor 
int lastVal = 2400;                 // last measured distance
// int diff = 100;                  // absolute difference between dist and lastVal
const int thresh = 325;             // 1 step / cc val = 13 in distance // 52 equals 4 'semitones' 

signed char midiCur = 0;            // Current state of the midi value
signed char midiPre = 67;           // Previous state of the midi value
const signed char midiDef = 69;     // default state of the midi value

void sendCC(uint8_t channel, uint8_t control, uint8_t value) {
	USBMIDI.write(0xB0 | (channel & 0xf));
	USBMIDI.write(control & 0x7f);
	USBMIDI.write(value & 0x7f);
}

void setup() {

}

void loop() {

	USBMIDI.poll();

	while (USBMIDI.available()) {
        USBMIDI.read();	
    }
    
    dist = sonar.ping();
    dist = constrain(dist, MIN_DIST, MAX_DIST); 
    midiCur = map(dist, MIN_DIST, MAX_DIST, 0, 127);

    if (abs(dist - lastVal) <= thresh) { 
        if (midiCur != midiPre) {
	        sendCC(MID_CH, CH_NUM, midiCur);
            lastVal = dist; 
            midiPre = midiCur;
        }
    } 
    // else {         
    //     if ((midiPre - midiDef) < 0) { 
    //             midiCur = midiPre + 1;
    //             lastVal = lastVal + 13;
    //             sendCC(midiCh, ccNo, midiCur);
    //         } else if ((midiPre - midiDef) > 0) { 
    //             midiCur = midiPre - 1;
    //             lastVal = lastVal - 13;
    //             sendCC(midiCh, ccNo, midiCur);
    //         }
    //     lastVal = dist;
    //     midiPre = midiCur;
    //     delay(100);
    // }
	USBMIDI.flush();
}

/*
Wenn "else", dann im nächsten durchgang IMMER "if"

*/
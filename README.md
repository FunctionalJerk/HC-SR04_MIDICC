
# MIDI Sensor

The current state of this project is a working prototype, that is based on a `teensy3.2` and a `HC-SR04` proximity sensor.
For cost reduction, this project will someday run on a Digistump Digispark / (Attiny85).

## ToDo

- add Switch ('up<->down', 'down<->up', 'note / cc / both')
- smoothing
- add DIN-MIDI
- add Fritzing.png
- make Digistump work

## ressources

[teensy-midi](https://www.pjrc.com/teensy/td_midi.html)

# Teensyduino

## Requirements

Working in VSCode, you dont have the option of changing the USB-type to USB-MIDI. 
In order to do so, execute following commands: (as described by user *ivankravets* [here](https://community.platformio.org/t/teensy2-0-usb-type-midi/511/2) )
```bash
cd ~/.platformio/packages/framework-arduinoteensy/cores/teensy/
rm -rf usb_serial
cp -r ../usb_midi .
```

# Digistump

You need to fix the SoftwareSerial.cpp file of your library as described [here](https://community.platformio.org/t/project-inspection-error-register-r24-r26-r28-or-r30-required/18648/3). 
I don't understand what's happening here, but it does the trick. 

If you encounter an error like `usb_open(): Permission denied. For Linux, copy file, copy file https://github.com/micronucleus/micronucleus/blob/master/commandline/49-micronucleus.rules to /etc/udev/rules.d.`

```bash
git clone git@github.com:micronucleus/micronucleus.git
cp micronucleus/commandline/49-micronucleus.rules /etc/udev/rules.d/49-micronucleus.rules
udevadm control --reload-rules
```

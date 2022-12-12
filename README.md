
Todo: 
- replace delay() with milis () (really? -> check if needed)
- check pin numbers

You need to fix the SoftwareSerial.cpp file of your library as described [here](https://community.platformio.org/t/project-inspection-error-register-r24-r26-r28-or-r30-required/18648/3). 
I don't understand what's happening here, but it does the trick. 

If you encounter an error like `usb_open(): Permission denied. For Linux, copy file, copy file https://github.com/micronucleus/micronucleus/blob/master/commandline/49-micronucleus.rules to /etc/udev/rules.d.`

```bash
git clone git@github.com:micronucleus/micronucleus.git
cp micronucleus/commandline/49-micronucleus.rules /etc/udev/rules.d/49-micronucleus.rules
udevadm control --reload-rules
```
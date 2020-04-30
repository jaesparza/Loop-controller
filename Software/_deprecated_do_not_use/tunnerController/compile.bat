arduino-cli compile --fqbn arduino:avr:mega tunnercontroller.ino
::C:\Users\ja\Documents\GitHub\Loop-Controller\Software\tunnerController

arduino-cli board list


arduino-cli upload -p COM17 --fqbn arduino:avr:mega

rename the file to the expected format...

C:\Users\ja\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\ja\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -v -patmega328p -carduino -PCOM17 -b57600 -D -Uflash:w:C:\Users\ja\AppData\Local\Temp\arduino_build_188707/tunnerController.ino.hex:i 



C:\Users\ja\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\ja\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -v -patmega328p -carduino -PCOM17 -b57600 -D -Uflash:w:C:\Users\ja\Documents\GitHub\Loop-Controller\Software\tunnerController\tunnerController.ino.arduino.avr.mega.hex:i


Compile with the correct settings for the particular micro


arduino-cli board list
arduino:avr:mini
arudino-cli core install arduino:avr

arduino-cli listall
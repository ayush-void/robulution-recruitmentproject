VOICE CONTROLLED ARMBOT🤖

This is a robotic project in which we have tried to build an arm which can pickup and 
drop objects on our voice command.To make it more efficient we have mounted the arm on 
a movable chassis which too move on our voice control.It can be controlled using your phone 
or laptop using browser-based speech to command.

Here is the process how to star the bot:-

Access the control panel at http://[ESP32-IP]:

Directional buttons (Forward/ Backward/Left/Right/Stop)

Arm movement (Rotate,pick,drop,up down)

Voice command button

Real-time response

Hardware Components:-
1. Esp32 Dev boards    -1
2. BO Motors           -4
3. L298N Motor Driver  -1
4. PCA9685 Servo Driver-1
5. SG90 Servo Motor    -3
6. MG995R Servo Motor  -3
7. 7.4V Battery        -1

Libraries & Frameworks (Arduino)

ESPAsyncWebServer - for hosting a web server on the ESP32 

ESPAsyncTCP - asynchronous TCP library required by AsyncWebServer

Wire.h - for 12C communication with PCA9685

Adafruit_PWMServoDriver - to control servos via PCA9685

Servo.h - to control any additional servos directly from ESP32 pins.

ArduinoJSON - for structured data handling.

Web Technologies (for the Control UI)

HTML - structure of the control web page

CSS - basic styling for buttons, sliders, and voice control interface

JavaScript - to handle button clicks, slider events, and voice recognition (using Web Speech API)

The Bot is not completed yet due to some hardware malfunction aiming to complete it soon.
Any suggestions are most welcome.

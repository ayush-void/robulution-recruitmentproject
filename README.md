🤖 VOICE CONTROLLED ARMBOT

This is a robotics project where we’ve built a robotic arm capable of picking up and dropping objects using voice commands. To make it even more versatile, we’ve mounted the arm on a movable chassis that can also be controlled via voice.
The entire system can be operated through your phone or laptop using a browser-based control panel with speech-to-command functionality.



📖 How to Start the Bot:

1. Connect to the ESP32 Wi-Fi network.


2. Access the control panel by visiting:
http://[ESP32-IP]


3. Use the following controls:

Directional Buttons — Move the bot: Forward, Backward, Left, Right, Stop.

Arm Movement Controls — Rotate the base, pick up objects, drop them, move the arm up and down.

Voice Command Button — Speak commands directly from your browser.

Real-Time Response — Immediate feedback and control over Wi-Fi.





---

🛠️ Hardware Components:

ESP32 Dev Board — 1

BO Motors — 4

L298N Motor Driver — 1

PCA9685 Servo Driver — 1

SG90 Servo Motors — 3

MG995R Servo Motors — 3

7.4V Battery Pack — 1



---

📚 Libraries & Frameworks (Arduino):

ESPAsyncWebServer — for hosting a web server on the ESP32

ESPAsyncTCP — asynchronous TCP library required by AsyncWebServer

Wire.h — for I2C communication with the PCA9685

Adafruit_PWMServoDriver — to control servos via PCA9685

Servo.h — to control any additional servos directly from ESP32 pins

ArduinoJSON — for structured data handling



---

🌐 Web Technologies (for the Control UI):

HTML — structure of the control web page

CSS — basic styling for buttons, sliders, and the voice control interface

JavaScript — to handle button clicks, slider movements, and voice recognition using the Web Speech API



---

⚠️ Project Status:

The bot is not fully completed yet due to some hardware malfunctions.
I’m working on resolving those issues and aim to finish it soon.

Suggestions, ideas, and contributions are most welcome! 🚀


---

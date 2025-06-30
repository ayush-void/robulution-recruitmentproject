#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// PCA9685 driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Web server
WebServer server(80);

// Servo pulse ranges (adjust if needed for your servos)
#define SERVO_MIN  110
#define SERVO_MAX  530
#define SERVO_HOME 320

void setup() {
  Serial.begin(115200);
  delay(1000);

  // I2C initialization (SDA = 14, SCL = 15)
  Wire.begin(14, 15);
  pwm.begin();
  pwm.setPWMFreq(50);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address:");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", handleRoot);
  server.on("/set", handleSetServo);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Robotic Arm Control</title>";
  html += "<style>body{font-family:sans-serif;background:#f0f0f0;padding:20px;}";
  html += "h2{color:#333;}button{padding:10px 20px;font-size:18px;margin:5px;border-radius:8px;border:none;}";
  html += "input[type=range]{width:80%;}</style>";
  html += "</head><body><h2>Robotic Arm Control Panel</h2>";

  // Servo sliders
  for (int i = 0; i < 6; i++) {
    html += "Servo " + String(i) + ": ";
    html += "<input type='range' min='" + String(SERVO_MIN) + "' max='" + String(SERVO_MAX)
         + "' value='" + String(SERVO_HOME) + "' id='servo" + String(i)
         + "' oninput='updateServo(" + String(i) + ",this.value)'>";
    html += "<span id='val" + String(i) + "'>" + String(SERVO_HOME) + "</span><br><br>";
  }

  html += "<button onclick='startListening()'>🎙️ Voice Command</button>";
  html += "<p id='status'></p>";

  // JavaScript for sliders + voice
  html += "<script>";
  html += "function updateServo(servo, val) {";
  html += "document.getElementById('val'+servo).innerText=val;";
  html += "fetch('/set?s='+servo+'&v='+val);}";
  html += "function startListening(){";
  html += "var r=new(window.SpeechRecognition||window.webkitSpeechRecognition)();";
  html += "r.lang='en-US';r.start();";
  html += "document.getElementById('status').innerText='Listening...';";
  html += "r.onresult=function(e){var c=e.results[0][0].transcript.toLowerCase();";
  html += "document.getElementById('status').innerText='You said: '+c;";
  html += "if(c.includes('pick')){fetch('/set?s=4&v=" + String(SERVO_MIN) + "');}";
  html += "else if(c.includes('drop')){fetch('/set?s=4&v=" + String(SERVO_MAX) + "');}";
  html += "else if(c.includes('home')){for(let i=0;i<6;i++){fetch('/set?s='+i+'&v=" + String(SERVO_HOME) + "');}}";
  html += "else{document.getElementById('status').innerText='Unknown command: '+c;}};}";
  html += "</script></body></html>";

  server.send(200, "text/html", html);
}

void handleSetServo() {
  if (server.hasArg("s") && server.hasArg("v")) {
    int servoNum = server.arg("s").toInt();
    int value = server.arg("v").toInt();
    if (servoNum >= 0 && servoNum < 6 && value >= SERVO_MIN && value <= SERVO_MAX) {
      pwm.setPWM(servoNum, 0, value);
      Serial.printf("Servo %d set to %d\n", servoNum, value);
      server.send(200, "text/plain", "OK");
      return;
    }
  }
  server.send(400, "text/plain", "Invalid Command");
}
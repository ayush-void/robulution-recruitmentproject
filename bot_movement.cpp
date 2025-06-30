#include <WiFi.h>
#include <WebServer.h>

// Motor pins
#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 15

// Wi-Fi credentials
const char* ssid = "Vivo";
const char* password = "Princeraj";

WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopBot();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Command URLs
  server.on("/", handleRoot);
  server.on("/forward", []() { forward(); server.send(200, "text/plain", "Forward"); });
  server.on("/backward", []() { backward(); server.send(200, "text/plain", "Backward"); });
  server.on("/left", []() { left(); server.send(200, "text/plain", "Left"); });
  server.on("/right", []() { right(); server.send(200, "text/plain", "Right"); });
  server.on("/stop", []() { stopBot(); server.send(200, "text/plain", "Stop"); });

  server.begin();
}

void loop() {
  server.handleClient();
}

// Motor control functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopBot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// HTML UI with mic support
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Bot Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    button { font-size: 24px; padding: 12px 20px; margin: 10px; }
    .mic-btn { background-color: #4CAF50; color: white; }
  </style>
</head>
<body>
  <h2>ESP32 Wi-Fi Bot</h2>
  <button onclick="sendCommand('forward')">Forward</button><br>
  <button onclick="sendCommand('left')">Left</button>
  <button onclick="sendCommand('stop')">Stop</button>
  <button onclick="sendCommand('right')">Right</button><br>
  <button onclick="sendCommand('backward')">Backward</button><br><br>

  <button class="mic-btn" onclick="startVoice()">🎤 Voice Command</button>

  <script>
    function sendCommand(cmd) {
      fetch('/' + cmd);
    }

    function startVoice() {
      const recog = new webkitSpeechRecognition();
      recog.lang = 'en-US';
      recog.start();
      recog.onresult = function(event) {
        const command = event.results[0][0].transcript.toLowerCase();
        if (['forward', 'backward', 'left', 'right', 'stop'].includes(command)) {
          sendCommand(command);
          alert("Voice: " + command);
        } else {
          alert("Invalid voice command: " + command);
        }
      };
    }
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}
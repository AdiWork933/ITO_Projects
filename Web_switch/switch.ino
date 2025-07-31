#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your mobile hotspot credentials
const char* SSID     = "______SSID_____";
const char* PASSWORD = "_____password_______";

// D1 on NodeMCU is GPIO5
const uint8_t SIGNAL_PIN = 5;  // GPIO5

ESP8266WebServer server(80);

bool isOn = false;          // ON means drive pin LOW
bool timerActive = false;
unsigned long timerEndMs = 0;

String htmlPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP8266 Web Switch</title>
<style>
  :root{
    --bg:#0f172a; --fg:#e2e8f0; --accent:#22c55e; --danger:#ef4444; --muted:#94a3b8;
  }
  body{
    font-family: system-ui, -apple-system, Segoe UI, Roboto, Ubuntu, Cantarell, sans-serif;
    background: var(--bg); color: var(--fg);
    display:flex; min-height:100vh; align-items:center; justify-content:center;
    padding:20px;
  }
  .card{
    background:#1e293b; border-radius:16px; padding:24px; max-width:480px; width:100%;
    box-shadow:0 10px 30px rgba(0,0,0,.2);
  }
  h2{margin-top:0; font-weight:600;}
  .state{font-size:18px; margin:18px 0;}
  .row{display:flex; flex-wrap:wrap; gap:8px; margin-bottom:12px;}
  button{
    flex:1 1 auto; min-width:90px; border:none; border-radius:10px; padding:12px 16px;
    font-size:16px; cursor:pointer; transition:transform .08s ease;
  }
  button:active{transform:scale(.98);}
  .on{background:var(--accent); color:#00330e;}
  .off{background:var(--muted); color:#0f172a;}
  .cancel{background:var(--danger);}
  .muted{color:var(--muted);}
  input[type="number"]{
    width:100%; padding:10px 12px; border-radius:8px; border:1px solid #334155;
    background:#0f172a; color:var(--fg);
  }
  .small{font-size:14px; color:var(--muted);}
  .hidden{display:none !important;}
</style>
</head>
<body>
  <div class="card">
    <h2>ESP8266 Web Switch</h2>

    <div class="state">
      Current State: <strong id="state">...</strong><br>
      Timer: <strong id="timer">—</strong>
    </div>

    <div class="row">
      <button class="on"  onclick="setState('on')">Turn ON</button>
      <button class="off" onclick="setState('off')">Turn OFF</button>
    </div>

    <hr style="border:none;border-top:1px solid #334155; margin:18px 0;">

    <div class="small muted">Quick ON Timers</div>
    <div class="row">
      <button onclick="startTimer(60)">1m</button>
      <button onclick="startTimer(5*60)">5m</button>
      <button onclick="startTimer(10*60)">10m</button>
      <button onclick="startTimer(30*60)">30m</button>
      <button onclick="startTimer(60*60)">1h</button>
    </div>

    <div class="small muted" style="margin-top:12px;">Custom (seconds / minutes / hours)</div>
    <div class="row">
      <input id="custom_val" type="number" min="1" placeholder="Enter number">
    </div>
    <div class="row">
      <button onclick="startCustom('s')">Start (sec)</button>
      <button onclick="startCustom('m')">Start (min)</button>
      <button onclick="startCustom('h')">Start (hr)</button>
    </div>

    <div class="row">
      <button id="cancelBtn" class="cancel hidden" onclick="cancelTimer()">Cancel Timer</button>
    </div>

    <div class="small muted" style="margin-top:16px;">Pin logic: ON = LOW, OFF = HIGH</div>
  </div>

<script>
function setState(state){
  fetch('/set?state=' + state).then(()=>updateStatus());
}
function startTimer(sec){
  fetch('/timer?sec=' + sec).then(()=>updateStatus());
}
function startCustom(unit){
  const n = parseInt(document.getElementById('custom_val').value || '0', 10);
  if (!n) return;
  let sec = n;
  if (unit === 'm') sec = n*60;
  if (unit === 'h') sec = n*3600;
  startTimer(sec);
}
function cancelTimer(){
  fetch('/timer?cancel=1').then(()=>updateStatus());
}
function secToHMS(s){
  if (s < 0) s = 0;
  const h = Math.floor(s/3600);
  const m = Math.floor((s%3600)/60);
  const sec = s%60;
  const parts = [];
  if (h) parts.push(h + 'h');
  if (m || h) parts.push(m + 'm');
  parts.push(sec + 's');
  return parts.join(' ');
}
function updateStatus(){
  fetch('/status')
    .then(r=>r.json())
    .then(j=>{
      document.getElementById('state').textContent = j.isOn ? 'ON (logic 0)' : 'OFF (logic 1)';
      document.getElementById('timer').textContent = j.timerActive ? secToHMS(j.remaining) : '—';
      document.getElementById('cancelBtn').classList.toggle('hidden', !j.timerActive);
    });
}
setInterval(updateStatus, 1000);
updateStatus();
</script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void forceOff() {
  isOn = false;
  digitalWrite(SIGNAL_PIN, HIGH); // OFF => logic 1
}

void forceOn() {
  isOn = true;
  digitalWrite(SIGNAL_PIN, LOW);  // ON => logic 0
}

void handleSet() {
  if (server.hasArg("state")) {
    String s = server.arg("state");
    timerActive = false; // any manual set cancels the timer
    if (s == "on") {
      forceOn();
    } else if (s == "off") {
      forceOff();
    }
  }
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleTimer() {
  if (server.hasArg("cancel")) {
    timerActive = false;
  } else if (server.hasArg("sec")) {
    unsigned long sec = server.arg("sec").toInt();
    if (sec > 0) {
      forceOn();
      timerActive = true;
      timerEndMs = millis() + (sec * 1000UL);
    }
  }
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleStatus() {
  unsigned long remaining = 0;
  if (timerActive) {
    unsigned long now = millis();
    if (timerEndMs > now) {
      remaining = (timerEndMs - now) / 1000UL;
    } else {
      remaining = 0;
    }
  }

  String json = "{";
  json += "\"isOn\":" + String(isOn ? "true" : "false") + ",";
  json += "\"timerActive\":" + String(timerActive ? "true" : "false") + ",";
  json += "\"remaining\":" + String(remaining);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  pinMode(SIGNAL_PIN, OUTPUT);
  forceOff();

  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.on("/timer", handleTimer);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  if (timerActive) {
    unsigned long now = millis();
    if ((long)(timerEndMs - now) <= 0) {
      timerActive = false;
      forceOff();
    }
  }
}




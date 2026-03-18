#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "__WIFI SSID / Hostpot name __";
const char* pass = "__Password__";


String apiKey =  "__Groq AIP KEY__";

ESP8266WebServer server(80);
WebSocketsServer ws(81);


// ===== PROFESSIONAL CHATGPT UI =====
String page(){
return R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, viewport-fit=cover">
<title>ESP AI OS</title>
<style>
/* Global Fixes */
* { box-sizing: border-box; margin: 0; padding: 0; }

body {
    font-family: -apple-system, system-ui, sans-serif;
    background: #0f172a;
    color: white;
    /* This fix ensures the UI fits 1600px height perfectly without cutting off */
    height: 100vh; 
    height: 100dvh; 
    display: flex;
    flex-direction: column;
    overflow: hidden;
}

/* TOP BAR (Optimized for Mobile) */
.header {
    background: rgba(15, 23, 42, 0.9);
    backdrop-filter: blur(10px);
    padding: 12px 16px;
    display: flex;
    align-items: center;
    justify-content: space-between;
    border-bottom: 1px solid rgba(255,255,255,0.1);
    z-index: 10;
}

.logo { font-size: 18px; font-weight: 800; color: #3b82f6; }
.stats { display: flex; gap: 8px; }
.badge { 
    background: rgba(255,255,255,0.1); 
    padding: 4px 8px; 
    border-radius: 6px; 
    font-size: 11px; 
    font-family: monospace;
}

/* CHAT AREA */
.chat-container {
    flex: 1;
    overflow-y: auto;
    padding: 15px;
    display: flex;
    flex-direction: column;
    gap: 15px;
    /* Extra padding at bottom so input doesn't cover last message */
    padding-bottom: 90px; 
}

.msg {
    padding: 12px 16px;
    border-radius: 18px;
    max-width: 85%;
    font-size: 15px;
    line-height: 1.5;
    white-space: pre-wrap;
    word-wrap: break-word;
    animation: fadeIn 0.3s ease;
}

@keyframes fadeIn { from { opacity: 0; transform: translateY(5px); } to { opacity: 1; transform: translateY(0); } }

.user { background: #2563eb; align-self: flex-end; border-bottom-right-radius: 4px; }
.ai { background: #1e293b; align-self: flex-start; border-bottom-left-radius: 4px; border: 1px solid rgba(255,255,255,0.1); }
b { color: #60a5fa; font-weight: 700; }

/* FLOATING INPUT BAR (Ensures visibility on 720x1600) */
.input-area {
    position: fixed;
    bottom: 0;
    left: 0;
    width: 100%;
    padding: 15px;
    background: linear-gradient(to top, #0f172a 80%, transparent);
    display: flex;
    justify-content: center;
    align-items: center;
}

.input-container {
    width: 100%;
    max-width: 720px;
    display: flex;
    gap: 10px;
    background: #1e293b;
    padding: 8px 12px;
    border-radius: 30px;
    border: 1px solid rgba(255,255,255,0.2);
    box-shadow: 0 10px 25px rgba(0,0,0,0.5);
}

input {
    flex: 1;
    background: transparent;
    border: none;
    color: white;
    font-size: 16px; /* Prevents auto-zoom on mobile */
    outline: none;
    padding-left: 5px;
}

.send-btn {
    background: #2563eb;
    border: none;
    width: 38px;
    height: 38px;
    border-radius: 50%;
    color: white;
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
}

/* DESKTOP SIDEBAR */
@media (min-width: 1024px) {
    body { flex-direction: row; }
    .header { 
        width: 260px; height: 100vh; 
        flex-direction: column; justify-content: flex-start; 
        gap: 20px; border-right: 1px solid rgba(255,255,255,0.1); 
    }
    .input-area { left: 260px; width: calc(100% - 260px); }
}
</style>
</head>
<body>

<div class="header">
    <div class="logo">ESP AI OS</div>
    <div class="stats">
        <div class="badge" id="wifi">WiFi: --</div>
        <div class="badge" id="tok">T: 0</div>
    </div>
    <button onclick="clr()" style="background:none; border:none; color:#94a3b8; font-size:11px; text-decoration:underline;">Clear Chat</button>
</div>

<div class="chat-container" id="chat">
    </div>

<div class="input-area">
    <div class="input-container">
        <input id="in" type="text" placeholder="Type a message..." autocomplete="off">
        <button class="send-btn" onclick="send()">
            <svg viewBox="0 0 24 24" width="20" height="20" fill="currentColor"><path d="M2.01 21L23 12 2.01 3 2 10l15 2-15 2z"></path></svg>
        </button>
    </div>
</div>

<script>
let ws = new WebSocket("ws://"+location.hostname+":81/");
let chat = document.getElementById("chat");
let typingDiv = null;

// Handle enter key
document.getElementById("in").addEventListener("keypress", (e) => {
    if (e.key === "Enter") send();
});

function formatText(t) {
    if(!t) return "";
    // Bold **text**
    t = t.replace(/\*\*(.*?)\*\*/g, "<b>$1</b>");
    // New lines
    t = t.replace(/\\n/g, "\n");
    return t;
}

ws.onmessage = e => {
    if(e.data.startsWith("RSSI")) document.getElementById("wifi").innerText="WiFi: "+e.data.split(":")[1];
    else if(e.data.startsWith("TOK")) document.getElementById("tok").innerText="T: "+e.data.split(":")[1];
    else if(e.data == "AI_START") {
        typingDiv = add("ai", "...");
    }
    else if(e.data.startsWith("AI:")){
        let raw = e.data.substring(3);
        if(typingDiv) typingDiv.innerHTML = formatText(raw);
        chat.scrollTop = chat.scrollHeight;
    }
};

function add(cls, txt){
    let d = document.createElement("div");
    d.className = "msg " + cls;
    if(cls === "ai") d.innerHTML = formatText(txt);
    else d.innerText = txt;
    chat.appendChild(d);
    chat.scrollTop = chat.scrollHeight;
    return d;
}

function send(){
    let i = document.getElementById("in");
    if(!i.value.trim()) return;
    add("user", i.value);
    ws.send(i.value);
    i.value = "";
}

function clr(){ chat.innerHTML = ""; }
</script>

</body>
</html>
)=====";
}
// ====== AI REQUEST (ONE CALL ONLY) ======
String askAI(String prompt) {
  WiFiClientSecure client;
  client.setInsecure(); // Groq requires HTTPS
  HTTPClient https;

  // 1. Correct Endpoint
  if (!https.begin(client, "https://api.groq.com/openai/v1/chat/completions")) {
    return "Connection Failed";
  }

  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer " + apiKey);

  // 2. Correct JSON Body Format
  String body = "{";
  body += "\"model\":\"llama-3.3-70b-versatile\","; // Use a valid Groq model
  body += "\"messages\": [";
  body += "{\"role\":\"system\",\"content\":\"You are a short, helpful AI.\"},";
  body += "{\"role\":\"user\",\"content\":\"" + prompt + "\"}";
  body += "],";
  body += "\"temperature\": 0.7";
  body += "}";

  int code = https.POST(body);
  
  if (code != 200) {
    String err = "Error: " + String(code);
    https.end();
    return err;
  }

  String res = https.getString();
  https.end();

  // 3. Updated Parsing for "choices" array (OpenAI Standard)
  int s = res.indexOf("\"content\":\"") + 11;
  int e = res.indexOf("\"", s);
  
  if (s < 11) return "Parse Error";
  
  String out = res.substring(s, e);
  return out;
}

// ===== WebSocket Handler =====

void handleWS(uint8_t num, WStype_t type, uint8_t * payload, size_t length){

if(type == WStype_TEXT){

String msg = String((char*)payload);

// typing indicator
String startMsg = "AI_START";
ws.sendTXT(num, startMsg);

// ask AI
String reply = askAI(msg);

// send reply
String sendReply = "AI:" + reply;
ws.sendTXT(num, sendReply);

// token counter
int tokens = msg.length()/4 + reply.length()/4;
String tokMsg = "TOK:" + String(tokens);
ws.sendTXT(num, tokMsg);

// wifi meter
int r = WiFi.RSSI();
String wifiMsg = "RSSI:" + String(r);
ws.sendTXT(num, wifiMsg);

}
}

void setup(){

Serial.begin(115200);

WiFi.begin(ssid,pass);
WiFi.setSleepMode(WIFI_NONE_SLEEP);

while(WiFi.status()!=WL_CONNECTED){
delay(500);
Serial.print(".");
}

Serial.println(WiFi.localIP());

server.on("/",[](){
server.send(200,"text/html",page());
});
server.begin();

ws.begin();
ws.onEvent(handleWS);

}

void loop(){
server.handleClient();
ws.loop();
}


// const char* ssid = "moto g45";
// const char* pass = "74393989800";
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

// ==== WiFi Credentials ====
const char* ssid = "ESP_Draw";
const char* password = "12345678";

// ==== ILI9341 Pins (NodeMCU) ====
#define TFT_CS   5   // D1
#define TFT_DC   4   // D2
#define TFT_RST  2   // D4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
ESP8266WebServer server(80);

// ==== HTML Page ====
const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP8266 Drawing</title>
  <style>
    body { font-family: Arial; text-align: center; background: #f0f0f0; }
    .toolbar { margin-bottom: 10px; display: flex; flex-wrap: wrap; justify-content: center; align-items: center; gap: 6px; }
    .color-btn, .tool-btn { width: 24px; height: 24px; border: 2px solid #444; cursor: pointer; border-radius: 4px; }
    .tool-btn { background: #ddd; text-align: center; line-height: 20px; font-size: 14px; }
    canvas { border: 2px solid #000; touch-action: none; background: #fff; }
    .label { font-weight: bold; margin: 0 6px; }
  </style>
</head>
<body>
  <h2>ESP8266 Drawing Pad</h2>
  <div class="toolbar">
    <span class="label">Color:</span>
    <div class="color-btn" style="background:#000" onclick="setColor('000')"></div>
    <div class="color-btn" style="background:#F00" onclick="setColor('F00')"></div>
    <div class="color-btn" style="background:#0F0" onclick="setColor('0F0')"></div>
    <div class="color-btn" style="background:#00F" onclick="setColor('00F')"></div>
    <div class="color-btn" style="background:#FF0" onclick="setColor('FF0')"></div>
    <div class="color-btn" style="background:#FA0" onclick="setColor('FA0')"></div>
    <div class="color-btn" style="background:#90F" onclick="setColor('90F')"></div>
    <div class="color-btn" style="background:#F0F" onclick="setColor('F0F')"></div>
    <div class="color-btn" style="background:#0FF" onclick="setColor('0FF')"></div>
    <div class="color-btn" style="background:#888" onclick="setColor('888')"></div>
    <div class="color-btn" style="background:#964B00" onclick="setColor('964B00')"></div>
    <div class="color-btn" style="background:#87CEEB" onclick="setColor('87CEEB')"></div>
    <div class="color-btn" style="background:#00FF7F" onclick="setColor('00FF7F')"></div>
    <div class="color-btn" style="background:#E6E6FA" onclick="setColor('E6E6FA')"></div>
    <div class="color-btn" style="background:#D2691E" onclick="setColor('D2691E')"></div>
    <div class="tool-btn" onclick="setColor('FFF')">ER</div>
    <button onclick="clearCanvas()">Clear</button>
    <span class="label">Size:</span>
    <input type="range" min="1" max="10" value="2" id="sizeSlider">
  </div>
  <canvas id="canvas" width="240" height="320"></canvas>

<script>
let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");
let drawing = false;
let color = "000";
let size = 2;

function setColor(c) { color = c; }
function clearCanvas() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  fetch("/clear");
}

document.getElementById("sizeSlider").addEventListener("input", e => {
  size = parseInt(e.target.value);
});

function drawDot(x, y) {
  ctx.fillStyle = "#" + color;
  ctx.beginPath();
  ctx.arc(x, y, size, 0, 2 * Math.PI);
  ctx.fill();
  fetch(`/draw?x=${x}&y=${y}&color=${color}&size=${size}`);
}

function getXY(e) {
  let rect = canvas.getBoundingClientRect();
  return {
    x: Math.floor((e.clientX || e.touches[0].clientX) - rect.left),
    y: Math.floor((e.clientY || e.touches[0].clientY) - rect.top)
  };
}

canvas.addEventListener("mousedown", e => { drawing = true; drawDot(...Object.values(getXY(e))); });
canvas.addEventListener("mouseup", () => drawing = false);
canvas.addEventListener("mousemove", e => { if (drawing) drawDot(...Object.values(getXY(e))); });
canvas.addEventListener("touchstart", e => { drawing = true; drawDot(...Object.values(getXY(e))); });
canvas.addEventListener("touchend", () => drawing = false);
canvas.addEventListener("touchmove", e => { e.preventDefault(); if (drawing) drawDot(...Object.values(getXY(e))); });
</script>
</body>
</html>
)rawliteral";

// ==== Setup ====
void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.fillScreen(ILI9341_WHITE);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(1000);

  Serial.println("AP started: " + WiFi.softAPIP().toString());

  server.on("/", []() {
    server.send(200, "text/html", html);
  });

  server.on("/clear", []() {
    tft.fillScreen(ILI9341_WHITE);
    server.send(200, "text/plain", "CLEARED");
  });

  server.on("/draw", []() {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("color")) {
      int x = server.arg("x").toInt();
      int y = server.arg("y").toInt();
      int size = server.hasArg("size") ? server.arg("size").toInt() : 2;
      String col = server.arg("color");
      uint16_t color = ILI9341_BLACK;

      if (col == "000") color = ILI9341_BLACK;
      else if (col == "F00") color = tft.color565(255, 0, 0);
      else if (col == "0F0") color = tft.color565(0, 255, 0);
      else if (col == "00F") color = tft.color565(0, 0, 255);
      else if (col == "FF0") color = tft.color565(255, 255, 0);
      else if (col == "FA0") color = tft.color565(250, 170, 0);
      else if (col == "90F") color = tft.color565(144, 0, 255);
      else if (col == "F0F") color = tft.color565(255, 0, 255);
      else if (col == "0FF") color = tft.color565(0, 255, 255);
      else if (col == "888") color = tft.color565(136, 136, 136);
      else if (col == "964B00") color = tft.color565(150, 75, 0);
      else if (col == "87CEEB") color = tft.color565(135, 206, 235);
      else if (col == "00FF7F") color = tft.color565(0, 255, 127);
      else if (col == "E6E6FA") color = tft.color565(230, 230, 250);
      else if (col == "D2691E") color = tft.color565(210, 105, 30);
      else if (col == "FFF") color = ILI9341_WHITE;

      for (int dx = -size; dx <= size; dx++) {
        for (int dy = -size; dy <= size; dy++) {
          int distSq = dx * dx + dy * dy;
          if (distSq <= size * size) {
            int px = x + dx;
            int py = y + dy;
            if (px >= 0 && px < 240 && py >= 0 && py < 320)
              tft.drawPixel(px, py, color);
          }
        }
      }
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
  Serial.println("Web server running.");
}

// ==== Loop ====
void loop() {
  server.handleClient();
}

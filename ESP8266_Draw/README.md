# 🖊️ ESP8266_Draw

A **Wi-Fi-based drawing application** powered by an **ESP8266 microcontroller** and **TFT (ILI9341) display**. This project creates a local access point with a web-based drawing pad interface. Drawings made via the web page are instantly rendered on the TFT display.

---

## 🚀 Features

- 📶 Creates its own Wi-Fi Access Point (`ESP_Draw`)
- 🎨 Interactive web-based canvas (HTML5 + JavaScript)
- 🖌️ Real-time drawing on ILI9341 TFT display
- 🎚️ Adjustable brush size and color palette
- 🧼 Eraser and clear screen functionality

---

## 🧠 Use Case

This project can be used as:

- A **portable collaborative art tool** — users can connect to the ESP’s Wi-Fi and draw from any mobile device or PC.
- A **digital whiteboard** for teaching, explaining, or quick sketching.
- A **learning platform** for embedded electronics and web UI interaction.
- A **demonstration tool** for Wi-Fi controlled IoT interfaces.

---

## 🛠️ Hardware Required

| Component            | Description                          |
|---------------------|--------------------------------------|
| ESP8266 (NodeMCU)    | Wi-Fi enabled microcontroller board   |
| ILI9341 TFT Display | 240x320 SPI Display                  |
| Jumper Wires        | For wiring TFT to NodeMCU            |
| Power Supply        | USB cable or 5V external supply       |

## Wiring Table (ILI9341 TFT with ESP8266 NodeMCU)

| TFT Pin      | NodeMCU Pin   | Function               |
|--------------|----------------|-------------------------|
| VCC          | 3.3V           | Power Supply            |
| GND          | GND            | Ground                  |
| CS           | D1 (GPIO5)     | Chip Select             |
| RESET        | D4 (GPIO2)     | Reset                   |
| DC/RS        | D2 (GPIO4)     | Data/Command            |
| MOSI (SDA)   | D7 (GPIO13)    | SPI MOSI                |
| SCK          | D5 (GPIO14)    | SPI Clock               |
| LED          | 3.3V or D6     | Backlight (PWM optional) |


---

## 🧩 Libraries Used

- [`ESP8266WiFi.h`](https://github.com/esp8266/Arduino)
- [`ESP8266WebServer.h`](https://github.com/esp8266/Arduino)
- [`Adafruit_GFX.h`](https://github.com/adafruit/Adafruit-GFX-Library)
- [`Adafruit_ILI9341.h`](https://github.com/adafruit/Adafruit_ILI9341)

Install these through the Arduino Library Manager.

---

## 🔧 Setup Instructions

1. **Clone or download** this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install the required libraries.
4. Select your board as `NodeMCU 1.0 (ESP-12E Module)`.
5. Upload the code to your ESP8266.
6. After uploading, connect your device to the Wi-Fi network:
   - SSID: `ESP_Draw`
   - Password: `12345678`
7. Open a browser and go to [http://192.168.4.1](http://192.168.4.1) to access the drawing interface.

---

## 📸 Screenshots

<table>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/977b13f9-8bc2-4f49-be8d-8ab2ff15629e" width="300" /></td>
    <td><img src="https://github.com/user-attachments/assets/29fe0f6b-5f79-496a-a40b-157ce454c844" width="300" /></td>
  </tr>
  <tr>
    <td colspan="2" align="center"><em>Sample drawing interface on browser</em></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/e3c24e36-a8cc-4be6-8cc1-246dc12ba6b9" width="300" /></td>
    <td><img src="https://github.com/user-attachments/assets/63ab7614-b772-40bd-8d50-fcb615a67d8e" width="300" /></td>
  </tr>
</table>

---

## 📚 License

This project is licensed under the MIT License. Feel free to use and modify it.

---

## 🙌 Acknowledgements

Thanks to [Adafruit](https://adafruit.com) for the display libraries and [ESP8266 Community](https://github.com/esp8266/Arduino) for the Wi-Fi and server support.

---

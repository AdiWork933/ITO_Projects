# ESP8266 Web Switch

<img width="1749" height="504" alt="image" src="https://github.com/user-attachments/assets/7cc1b4f8-96e8-48f4-9959-fd5df9c43ac3" />

Simple web-controlled switch for ESP8266 with manual and timed ON/OFF.  
**Logic:** ON = LOW, OFF = HIGH.

## Setup

1. Clone / copy the `.ino` / `.cpp` file into Arduino IDE.
2. Install ESP8266 board support in Arduino IDE (add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` in Preferences → Boards Manager).
3. Select your ESP8266 board (e.g., NodeMCU 1.0) and the correct port.
4. Edit credentials at top of the code:
   ```cpp
   const char* SSID     = "YourHotspotSSID";
   const char* PASSWORD = "YourHotspotPassword";
  ```

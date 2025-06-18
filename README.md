# ITO_Projects

---

### ESP32 WiFi Repeater

The **ESP32 WiFi Repeater** allows you to extend the range of an existing WiFi network. It connects to a primary WiFi source as a client and simultaneously acts as an access point, creating a new WiFi network for your devices to join. This effectively rebroadcasts the original WiFi signal, boosting coverage in areas with weak connectivity.

**Key features:**
- Acts as both a client (station mode) and an access point (soft AP mode).
- Ideal for improving WiFi signal coverage in larger areas.
- Supports dynamic IP assignment and can handle multiple devices connecting to the repeater network.
- 👉 [All setup guide here](https://github.com/AdiWork933/ITO_Projects/tree/main/ES32_WIFI_Repeter)

This setup is useful in scenarios where your main WiFi router’s coverage does not reach all areas you need.

---

### ESP32 Marauder

The **ESP32 Marauder** is a powerful WiFi and Bluetooth hacking toolkit based on the ESP32 microcontroller. It provides a comprehensive suite of features for security testing and wireless exploration.

**Key features:**
- Acts as a versatile WiFi scanner, packet sniffer, and deauthentication tool.
- Allows you to identify nearby WiFi networks and perform tests on them.
- Supports various attack modes, including deauth attacks and beacon spamming.
- Displays network data and test results on a touchscreen display for real-time feedback.
- Compatible with external SD cards for saving logs and session data.
- 👉 [All setup guide here](https://github.com/AdiWork933/ITO_Projects/tree/main/ESP32%20Marauder)

This setup is ideal for testing network security, understanding how WiFi works, and learning about potential vulnerabilities in a controlled environment.

---

### ESP8266 Draw

The **ESP8266 Draw** is a compact, web-based wireless drawing pad built using the ESP8266 microcontroller and an ILI9341 TFT display. It offers an interactive touchscreen interface accessible over WiFi, allowing users to sketch and draw in real-time from any browser.

**Key features:**
- Turns the ESP8266 into a local WiFi access point serving a web-based drawing canvas.
- Allows drawing directly on a touchscreen (ILI9341) using finger or stylus.
- Supports multiple colors, brush sizes, eraser, and clear canvas options.
- Touch-friendly web interface works across phones, tablets, and computers.
- No internet required – works entirely offline via `ESP_Draw` WiFi.
- Easy to deploy using Arduino IDE and open-source libraries.
- Ideal for IoT learning, interactive art projects, and embedded GUI experimentation.

👉 [All setup guide here](https://github.com/AdiWork933/ITO_Projects/tree/main/ESP8266_Draw)

This project is perfect for exploring web-based interfaces on microcontrollers, learning about embedded touch UIs, and creating interactive, offline art stations.

# ESP32 Marauder

## Software Setup

### Setup
1. Connect your ESP32 to your device or laptop.
2. Go to the [ESP32 Flash Download Tool](https://esp.huhn.me/).
3. Click the **CONNECT** button.  
   <img src="https://github.com/user-attachments/assets/e01ba71f-daed-40a4-892c-f344f3110732" width="400"/>
4. Select your **COM port**.  
   <img src="https://github.com/user-attachments/assets/f8e4ab30-d33b-4bce-9e2b-4ce03b64c6f7" width="400"/>
5. After the connection is established, assign the firmware file in the specified format.  
   <img src="https://github.com/user-attachments/assets/d7349c00-2feb-49f1-9504-f4f1b2ccc3df" width="400"/>
6. Finally, click the **PROGRAM** button to flash the firmware.

---

## Hardware Setup

### Requirements
- ESP32 (30-pin) with Wi-Fi and Bluetooth
- 2.8-inch SPI Touch Screen Module TFT Interface (240x320)
- SD card module

---

### Wiring for Display & SD Card Module  
![image](https://github.com/user-attachments/assets/2f10bb62-ad10-408a-ab7d-b935e6c34134)

| Pin | ILI9341      | ESP32   |
|-----|--------------|---------|
| 1   | VCC          | 3.3V    |
| 2   | GND          | GND     |
| 3   | CS           | D17     |
| 4   | RESET        | D5      |
| 5   | DC           | D16     |
| 6   | SDI (MOSI)   | D23     |
| 7   | SCK          | D18     |
| 8   | LED          | D32     |
| 9   | SDO (MISO)   | D19     |
| 10  | T_CLK        | D18     |
| 11  | T_CS         | D21     |
| 12  | T_DIN        | D23     |
| 13  | T_DO         | D19     |
| 14  | T_IRQ        | Leave unconnected |

---

### Wiring for SD Card Module

| MicroSD Card Reader | ESP32  |
|---------------------|---------|
| VCC                 | 5V      |
| GND                 | GND     |
| CS (Chip Select)    | GPIO 12 |
| SCK (Clock)         | GPIO 18 |
| MOSI (Master Out)   | GPIO 23 |
| MISO (Master In)    | GPIO 19 |

---
# Project Runtime Images

<div align="center">
  <img src="https://github.com/user-attachments/assets/15917eb4-c9a7-4101-9b5f-dc9d07ebc647" width="250" alt="Project runtime 1">
  <img src="https://github.com/user-attachments/assets/14320fc6-141c-44ab-8ad1-877edf52ea8a" width="250" alt="Project runtime 2">
  <img src="https://github.com/user-attachments/assets/00971e7e-5329-476a-bd9f-4043bd4e6313" width="250" alt="Project runtime 3">
</div>

<div align="center">
  <img src="https://github.com/user-attachments/assets/6141c198-f23e-49f4-9733-5cd355055b1b" width="250" alt="Project runtime 4">
  <img src="https://github.com/user-attachments/assets/63bf0203-050f-47dd-ba2e-3e665e6b2e1e" width="250" alt="Project runtime 5">
  <img src="https://github.com/user-attachments/assets/1257e4dc-8081-4f68-944b-2dda6ea16464" width="250" alt="Project runtime 6">
</div>

---

## Additional Resources

- Download the [latest firmware release](https://github.com/justcallmekoko/ESP32Marauder/releases/latest).
- Visit the project [Wiki](https://github.com/justcallmekoko/ESP32Marauder/wiki) for a full overview and additional documentation.
- ESP32 Driver [Here](https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool)

---

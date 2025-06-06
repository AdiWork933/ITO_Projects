# ESP32 Marauder
## SoftWare Setup
 - ### Setup
    - Connest your ESP32 to your divice or laptop
    - Goto link [Click here](https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool).
    - Click to **CONNECT** Button.
    - ![image](https://github.com/user-attachments/assets/e01ba71f-daed-40a4-892c-f344f3110732)
    - Now select You **COM port**.
    - ![image](https://github.com/user-attachments/assets/f8e4ab30-d33b-4bce-9e2b-4ce03b64c6f7)
    - After Connectinon assign file in following format.
    - ![Screenshot 2025-06-06 203151](https://github.com/user-attachments/assets/d7349c00-2feb-49f1-9504-f4f1b2ccc3df)
    - Click on **PROGRAM** Button

## Hardware Setup
 - ### Requirement
    - ESp32(30 pin) Wifi and Bluetooth
    - 2.8 inch SPI Touch Screen Module TFT Interface 240*320
    - SD card module
 - ### Wiring For Display

| Pin  | ILI9341     | ESP32  |
|------|-------------|--------|
| 1    | VCC         | 3.3V   |
| 2    | GND         | GND    |
| 3    | CS          | D17    |
| 4    | RESET       | D5     |
| 5    | DC          | D16    |
| 6    | SDI (MOSI)  | D23    |
| 7    | SCK         | D18    |
| 8    | LED         | D32    |
| 9    | SDO (MISO)  | D19    |
| 10   | T_CLK       | D18    |
| 11   | T_CS        | D21    |
| 12   | T_DIN       | D23    |
| 13   | T_DO        | D19    |
| 14   | T_IRQ       | Leave  |

 - ### Wiring For SD Card Module
   
| MicroSD Card Reader | ESP32 |
|----------------------|------------------|
| VCC                  | 5V               |
| GND                  | GND              |
| CS (Chip Select)     | GPIO 12          |
| SCK (Clock)          | GPIO 18          |
| MOSI (Master Out)    | GPIO 23          |
| MISO (Master In)     | GPIO 19          |

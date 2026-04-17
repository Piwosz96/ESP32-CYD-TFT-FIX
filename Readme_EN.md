\# ESP32-2432S028R (CYD) – Working TFT + WiFi + Time



\## ⚠️ Problem



In many ESP32-2432S028R modules, the display is NOT an ILI9341 (despite being advertised as such).

Most commonly, it is an ST7789 or a compatible controller (e.g. TPM408-2.8).



Symptoms of incorrect configuration:



\* display glitches ("garbage" pixels)

\* mirrored or distorted text

\* incorrect colors

\* shifted or partially working image



\---



\## ✅ Solution



Working configuration:



\* Library: LovyanGFX

\* Driver: ST7789

\* SPI: VSPI\_HOST

\* Rotation: setRotation(1) → 320x240 (landscape)



\---



\## 🔌 Pinout



SCLK = 14

MOSI = 13

MISO = 12

CS   = 15

DC   = 2

BL   = 21



\---



\## ⚙️ Key Settings



\* invert = false

\* DO NOT use fillScreen() inside loop (causes flickering)

\* update only parts of the screen (use fillRect + redraw)



\---



\## 📦 What this project includes



\* working TFT display

\* no flickering

\* correct colors

\* WiFi status

\* real-time clock (NTP)

\* ready-to-use dashboard (TEMP / TDS / WIFI / TIME / DATE)



\---



\## 🚀 Result



Stable and clean user interface without display artifacts.



\---



\## 📸 Tip



If only part of the screen works or you see glitches → you are likely using the wrong driver (ILI9341 instead of ST7789)



\---



\## 👌 Credits



If this helped you — consider leaving a ⭐ on the repository 🙂




![ESP32](https://img.shields.io/badge/ESP32-CYD-blue)
![Display](https://img.shields.io/badge/TFT-ST7789-green)
![Display](https://img.shields.io/badge/TFT-ILI9341-yellow)
![Library](https://img.shields.io/badge/LovyanGFX-working-orange)

🇵🇱 Polish | 🇬🇧 English: [Readme_EN.md](README_EN.md)


# ESP32-CYD-TFT-FIX
Reliable fix for ESP32-2432S028R (CYD) TFT display. Uses ST7789 + LovyanGFX to eliminate glitches, wrong colors and flickering. Includes working UI, WiFi status and real-time clock.
# ESP32-2432S028R (CYD) – działający TFT + WiFi + czas

## ⚠️ Problem

W wielu modułach ESP32-2432S028R wyświetlacz NIE jest ILI9341 (mimo opisu), tylko ST7789 lub kompatybilny (np. TPM408-2.8).

Objawy złej konfiguracji:

* krzaki na ekranie
* odbicia tekstu
* złe kolory
* przesunięty obraz

---

## ✅ Rozwiązanie

Działająca konfiguracja:

* Biblioteka: LovyanGFX
* Driver: ST7789
* SPI: VSPI_HOST
* Rotacja: setRotation(1) → 320x240

---

## 🔌 Piny

SCLK = 14
MOSI = 13
MISO = 12
CS   = 15
DC   = 2
BL   = 21

---

## ⚙️ Kluczowe ustawienia

* invert = false
* NIE używać fillScreen() w loop (powoduje miganie)
* aktualizować tylko fragmenty ekranu

---

## 📦 Co zawiera projekt

* działający ekran TFT
* brak migania
* poprawne kolory
* WiFi status
* aktualny czas (NTP)
* gotowy dashboard (TEMP / TDS / WIFI / TIME / DATA)

---

## 🚀 Efekt

Stabilny, czytelny interfejs bez artefaktów.

---

## 📸 Tip

Jeśli działa tylko połowa ekranu albo są krzaki → masz zły driver (ILI9341 zamiast ST7789)

---

## 👌 Autor rozwiązania

Jeśli pomogło — zostaw ⭐ na repo 🙂

#include <LovyanGFX.hpp>
#include <WiFi.h>
#include <time.h>

// WIFI
const char* ssid = "Enter Your WiFi SSID";
const char* password = "Enter Your WiFi Password";

// CZAS
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel;
  lgfx::Bus_SPI _bus;

public:
  LGFX(void) {
    {
      auto cfg = _bus.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 20000000;
      cfg.freq_read  = 16000000;

      cfg.pin_sclk = 14;
      cfg.pin_mosi = 13;
      cfg.pin_miso = 12;
      cfg.pin_dc   = 2;

      _bus.config(cfg);
      _panel.setBus(&_bus);
    }

    {
      auto cfg = _panel.config();
      cfg.pin_cs   = 15;
      cfg.pin_rst  = -1;

      cfg.panel_width  = 240;
      cfg.panel_height = 320;

      cfg.memory_width  = 240;
      cfg.memory_height = 320;

      cfg.offset_x = 0;
      cfg.offset_y = 0;

      cfg.invert = false;
      cfg.rgb_order = false;

      _panel.config(cfg);
    }

    setPanel(&_panel);
  }
};

LGFX tft;

float temperatura = 25.4;
int tds = 320;

// centrowanie dla 320px
void drawCentered(const char* text, int y, int size, uint16_t color) {
  tft.setTextSize(size);
  tft.setTextColor(color);
  int w = tft.textWidth(text);
  int x = (320 - w) / 2;
  tft.setCursor(x, y);
  tft.print(text);
}

// statyczny UI (rysowany raz)
void drawStaticUI() {
  tft.fillScreen(TFT_BLACK);

  drawCentered("AKWARIUM", 8, 2, TFT_CYAN);
  tft.drawLine(0, 30, 319, 30, TFT_DARKGREY);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  tft.setCursor(10, 45);  tft.print("TEMP");
  tft.setCursor(10, 90);  tft.print("TDS");
  tft.setCursor(10, 135); tft.print("WIFI");

  // 🔥 zamienione miejscami
  tft.setCursor(10, 170); tft.print("TIME");
  tft.setCursor(10, 200); tft.print("DATA");
}

// aktualizacja bez migania
void updateValues(struct tm timeinfo, bool wifiOK) {

  // TEMP
  tft.fillRect(120, 40, 180, 30, TFT_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(120, 40);
  tft.printf("%.1f C", temperatura);

  // TDS
  tft.fillRect(120, 85, 180, 30, TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(120, 85);
  tft.printf("%d ppm", tds);

  // WIFI
  tft.fillRect(120, 130, 180, 25, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(wifiOK ? TFT_GREEN : TFT_RED);
  tft.setCursor(120, 135);
  tft.print(wifiOK ? "Stargate 2.4Ghz" : "BRAK");

  // 🔥 TIME (wyżej)
  char timeBuf[20];
  strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &timeinfo);

  tft.fillRect(120, 170, 180, 25, TFT_BLACK);
  tft.setTextColor(TFT_BLUE);
  tft.setCursor(120, 170);
  tft.print(timeBuf);

  // 🔥 DATA (niżej)
  char dateBuf[20];
  strftime(dateBuf, sizeof(dateBuf), "%d-%m-%Y", &timeinfo);

  tft.fillRect(120, 200, 180, 25, TFT_BLACK);
  tft.setCursor(120, 200);
  tft.print(dateBuf);
}

void setup() {
  Serial.begin(115200);

  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  tft.init();
  tft.setRotation(1);

  drawStaticUI();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;

  bool wifiOK = (WiFi.status() == WL_CONNECTED);

  if (!getLocalTime(&timeinfo)) return;

  updateValues(timeinfo, wifiOK);

  delay(1000);
}
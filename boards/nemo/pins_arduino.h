#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

// UART
static const uint8_t TX = 1;
static const uint8_t RX = 3;

// SPI (не используется для дисплея — он на HSPI)
static const uint8_t SDA = 21;
static const uint8_t SCL = 22;
static const uint8_t SS = 5;
static const uint8_t MOSI = 23;
static const uint8_t MISO = 19;
static const uint8_t SCK = 18;

// Кнопки
#define BTN_UP_PIN 25
#define BTN_DOWN_PIN 26
#define BTN_OK_PIN 27
#define BTN_BACK_PIN 14
#define BTN_ACT LOW // кнопки на GND, INPUT_PULLUP

// ИК
#define TXLED 33
#define RXLED 35
#define LED_ON HIGH
#define LED_OFF LOW

// IR/RF списки пинов (отображаются в меню настроек Bruce)
#define IR_TX_PINS                                                                                           \
    {                                                                                                        \
        {"GPIO 33", 33}                                                                                      \
}
#define IR_RX_PINS                                                                                           \
    {                                                                                                        \
        {"GPIO 35", 35}                                                                                      \
    }
#define RF_TX_PINS                                                                                           \
    {                                                                                                        \
        {"GPIO 33", 33}                                                                                      \
    }
#define RF_RX_PINS                                                                                           \
    {                                                                                                        \
        {"GPIO 35", 35}                                                                                      \
    }

// I2C (Grove — нужен Bruce, ставим свободные пины)
#define GROVE_SDA 13
#define GROVE_SCL 15

// SD карты нет
#define SDCARD_CS -1
#define SDCARD_SCK -1
#define SDCARD_MISO -1
#define SDCARD_MOSI -1

// SPI шина (для CC1101/NRF если понадобится)
#define SPI_SCK_PIN -1
#define SPI_MOSI_PIN -1
#define SPI_MISO_PIN -1
#define SPI_SS_PIN -1

// Дисплей ST7789 240x240
#define HAS_SCREEN 1
#define ROTATION 1
#define USER_SETUP_LOADED 1
#define ST7789_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 21
#define TFT_RST 4
#define TFT_BL -1 // BL подключён к 3V3 напрямую
#define TFT_BACKLIGHT_ON 1
#define TOUCH_CS -1
#define SMOOTH_FONT 1
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000

// Шрифты
#define FP 1
#define FM 2
#define FG 3

// Кнопка "select" (одна — для совместимости с BTN_PIN логикой)
#define HAS_BTN 1
#define HAS_3_BUTTONS 1
#define BTN_ALIAS "\"Ok\""
#define BTN_PIN BTN_OK_PIN
#define BTN_ACT LOW

// Батарея/питание
#define BAD_TX -1
#define BAD_RX -1

#define DEVICE_NAME "\"Nemo\""

#endif

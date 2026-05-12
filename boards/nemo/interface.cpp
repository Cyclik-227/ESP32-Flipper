#include "core/powerSave.h"
#include <interface.h>

#define BTN_UP_PIN 25
#define BTN_DOWN_PIN 26
#define BTN_OK_PIN 27
#define BTN_BACK_PIN 14

void _setup_gpio() {
    pinMode(BTN_UP_PIN, INPUT_PULLUP);
    pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
    pinMode(BTN_OK_PIN, INPUT_PULLUP);
    pinMode(BTN_BACK_PIN, INPUT_PULLUP);
}
void _post_setup_gpio() {}
int getBattery() { return 0; }
void _setBrightness(uint8_t brightval) {}

void InputHandler(void) {
    checkPowerSaveTime();
    PrevPress = false;
    NextPress = false;
    UpPress = false;
    DownPress = false;
    SelPress = false;
    AnyKeyPress = false;
    EscPress = false;

    bool up = digitalRead(BTN_UP_PIN) == LOW;
    bool down = digitalRead(BTN_DOWN_PIN) == LOW;
    bool ok = digitalRead(BTN_OK_PIN) == LOW;
    bool back = digitalRead(BTN_BACK_PIN) == LOW;

    if (up || down || ok || back) {
        if (!wakeUpScreen()) AnyKeyPress = true;
        else goto END;
    }
    if (up) {
        PrevPress = true;
        UpPress = true;
    }
    if (down) {
        NextPress = true;
        DownPress = true;
    }
    if (back) { EscPress = true; }
    if (ok) { SelPress = true; }
END:
    if (AnyKeyPress) {
        long tmp = millis();
        while ((millis() - tmp) < 200 &&
               (digitalRead(BTN_UP_PIN) == LOW || digitalRead(BTN_DOWN_PIN) == LOW ||
                digitalRead(BTN_OK_PIN) == LOW || digitalRead(BTN_BACK_PIN) == LOW));
    }
}

void powerOff() { esp_deep_sleep_start(); }
void checkReboot() {}

# ESP32-Flipper

> DIY Flipper Zero alternative based on ESP32 with Bruce firmware.  
> 433MHz radio, NFC, IR transmitter/receiver, 240×240 display.

![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![Firmware](https://img.shields.io/badge/firmware-Bruce-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-red)

---

## 📷 Result

![ESP32-Flipper](photos/img1.png)
![ESP32-Flipper](photos/img2.png)

---

## 🛒 What to buy

| Component | What it does | Where to buy |
|-----------|-------------|--------------|
| ESP32-WROOM-32 (38-pin) | Main brain of the device | AliExpress |
| ST7789 240×240 display | Screen | AliExpress |
| CC1101 433MHz module | Capture and replay radio signals (gates, remotes) | AliExpress |
| PN532 NFC module | Read and emulate NFC cards | AliExpress |
| TSAL6200 × 2 | IR transmitter LEDs | AliExpress |
| TSOP4838 | IR receiver | AliExpress |
| BC547 | NPN transistor for IR circuit | Any electronics store |
| TP4056 | LiPo battery charger | AliExpress |
| ME6211 | 3.3V voltage regulator | AliExpress |
| Resistor 1kΩ | For IR transistor base | Any electronics store |
| Resistor 47Ω × 2 | IR LED current limiting | Any electronics store |
| Capacitor 1µF × 2 | Power filtering | Any electronics store |
| Rocker switch | Power on/off | Any electronics store |
| LiPo battery | Power source | AliExpress |

> **PN532 tip:** make sure it has DIP switches on the board — needed to set I2C mode.  
> **CC1101 tip:** get one with an antenna included.

---

## 🔧 Assembly guide

### Before you start

- You will need a soldering iron, solder, and flux
- All buttons connect with **one wire to the GPIO pin** and **one wire to GND**
- Everything runs on **3.3V** — never connect anything directly to 5V or battery voltage
- Double-check every connection before powering on
- Use a multimeter to verify GND connections (continuity test)

---

### Step 1 — Display (ST7789 240×240)

Solder the display first — it's the most important part.

| ST7789 pin | Connect to |
|------------|------------|
| GND | GND |
| VCC | 3V3 |
| SCL | GPIO 18 |
| SDA | GPIO 23 |
| RST | GPIO 4 |
| DC | GPIO 21 |
| CS | GPIO 5 |
| BL | 3V3 |

> **Note:** BL (backlight) goes directly to 3V3 — no resistor needed.

---

### Step 2 — Buttons

4 buttons total. Each button has 2 pins — one goes to GPIO, the other to GND.

| Button | GPIO |
|--------|------|
| Up / Left | GPIO 25 |
| Down / Right | GPIO 26 |
| Select / OK | GPIO 27 |
| Back | GPIO 14 |

> **Tip:** Buttons connect GPIO to GND when pressed — do not connect to 3V3.

---

### Step 3 — IR transmitter (TSAL6200 × 2 + BC547)

Both IR LEDs are connected in parallel, each with its own 47Ω resistor. BC547 transistor controls them.

```
GPIO 33 ──── 1kΩ ──── BC547 Base
                       BC547 Emitter ──── GND
                       BC547 Collector ──┬── 47Ω ──── TSAL6200 #1 Anode
                                         └── 47Ω ──── TSAL6200 #2 Anode
                       TSAL6200 Cathodes ──── GND
```

> ⚠️ **Watch polarity** — IR LEDs have a longer leg (anode +) and shorter leg (cathode −).

---

### Step 4 — IR receiver (TSOP4838)

3 pins. Looking at the flat side of the sensor from left to right:

| Pin | Connect to |
|-----|-----------|
| OUT (left) | GPIO 35 |
| GND (middle) | GND |
| VS (right) | 3V3 |

---

### Step 5 — 433MHz radio (CC1101)

Uses the second SPI bus on ESP32 — no conflict with the display.

| CC1101 pin | Connect to |
|------------|------------|
| VCC | 3V3 |
| GND | GND |
| SCK | GPIO 22 |
| MOSI | GPIO 17 |
| MISO | GPIO 19 |
| CSN | GPIO 16 |
| GDO0 | GPIO 32 |
| GDO2 | **Not connected** |

> ⚠️ **Do not connect GDO2** — leave it unsoldered.

---

### Step 6 — NFC (PN532)

**First:** set DIP switches on the PN532 board to I2C mode:
- SW1 = ON
- SW2 = OFF

Then solder only these 4 pins:

| PN532 pin | Connect to |
|-----------|------------|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 13 |
| SCL | GPIO 15 |

> All other pins on the PN532 board — leave unconnected.

---

### Step 7 — Power system

Battery → TP4056 (charger) → rocker switch → ME6211 (3.3V regulator) → ESP32.

```
Battery (+) ──── TP4056 B+
Battery (−) ──── TP4056 B−
TP4056 OUT+ ──── Rocker switch (middle pin)
Rocker switch (far pin) ──┬── ME6211 IN
                          └── Capacitor 1µF ──── GND
ME6211 OUT ──┬── ESP32 3V3
             └── Capacitor 1µF ──── GND
ME6211 GND ──── GND
TP4056 OUT− ──── GND
```

> ⚠️ **Capacitors are required** — they prevent ESP32 random resets.  
> ⚠️ **Never connect battery directly to ESP32** without the regulator.

---

### Step 8 — Final check before power on

1. Check GND everywhere with multimeter (continuity mode)
2. Make sure 3V3 is **not shorted to GND**
3. Check IR LED polarity
4. Check PN532 DIP switches
5. Power on — display should light up

---

## 💾 Flashing firmware

### Option A — Pre-built binary (easiest)

Download `firmware/firmware.bin` from this repo.

Install esptool and flash:

```bash
pip install esptool
esptool.py --port /dev/ttyUSB0 --baud 115200 write_flash 0x0 firmware.bin
```

On Windows replace `/dev/ttyUSB0` with `COM3` (check Device Manager for your port).

**How to enter flash mode:**
1. Hold **BOOT** button on ESP32
2. Press and release **RST**
3. Release **BOOT**
4. Run the flash command

---

### Option B — Build from source

Requirements:
- [PlatformIO](https://platformio.org/) VSCode extension
- Python 3.10–3.13 (**Python 3.14 is NOT supported yet**)

```bash
git clone https://github.com/pr3y/Bruce.git
cd Bruce
```

Copy `boards/nemo/` folder from this repo into `Bruce/boards/`.

Set `default_envs = nemo` in `platformio.ini`, then:

```bash
pio run -t upload
pio run -t uploadfs
```

**Linux — if permission denied:**
```bash
sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB0
```

**If upload fails with connection error**, add to `platformio.ini`:
```ini
upload_speed = 115200
board_upload.speed = 115200
```

Then enter flash mode manually (see Option A) and run upload again.

---

## 📡 Using the device

### WebUI

1. On device: **WiFi → Start WiFi AP**
2. Connect to Bruce WiFi (password: `brucenet`)
3. Open `http://172.0.0.1` in browser

### IR — TV and AC remotes

Go to **IR** in the menu. Point any remote at TSOP4838 sensor and capture.

> Some AC remotes (TOSOT/Gree) send very long signals. If capture fails — try RAW mode.

### 433MHz — gates and remotes

Go to **RF** in the menu.

### NFC — cards

Go to **RFID** in the menu. PN532 DIP switches must be set to I2C mode.

---

## 📋 TODO

- [x] Display working
- [x] Buttons working
- [x] IR transmitter/receiver working
- [x] Power system working
- [x] Bruce firmware running
- [x] Keyboard input working
- [x] WebUI accessible via WiFi
- [ ] CC1101 433MHz — module on the way
- [ ] PN532 NFC — module on the way
- [ ] GitHub release with pre-built firmware

---
---

# ESP32-Flipper (на русском)

> DIY аналог Flipper Zero на базе ESP32 с прошивкой Bruce.  
> Радио 433МГц, NFC, ИК передатчик/приёмник, дисплей 240×240.

---

## 📷 Результат

![ESP32-Flipper](photos/img1.png)
![ESP32-Flipper](photos/img2.png)

---

## 🛒 Что купить

| Компонент | Для чего | Где купить |
|-----------|----------|-----------|
| ESP32-WROOM-32 (38 пин) | Основной микроконтроллер | AliExpress |
| Дисплей ST7789 240×240 | Экран | AliExpress |
| Модуль CC1101 433МГц | Перехват и воспроизведение радиосигналов | AliExpress |
| Модуль PN532 NFC | Чтение и эмуляция NFC карт | AliExpress |
| TSAL6200 × 2 | ИК-диоды передатчика | AliExpress |
| TSOP4838 | ИК-приёмник | AliExpress |
| BC547 | NPN транзистор для ИК цепи | Любой радиомагазин |
| TP4056 | Зарядник LiPo аккумулятора | AliExpress |
| ME6211 | Стабилизатор 3.3В | AliExpress |
| Резистор 1кОм | Для базы транзистора | Любой радиомагазин |
| Резистор 47 Ом × 2 | Ограничение тока ИК-диодов | Любой радиомагазин |
| Конденсатор 1мкФ × 2 | Фильтрация питания | Любой радиомагазин |
| Кулисный переключатель | Включение/выключение | Любой радиомагазин |
| LiPo аккумулятор | Источник питания | AliExpress |

> **Совет по PN532:** убедись что на плате есть DIP переключатели — они нужны для I2C режима.  
> **Совет по CC1101:** бери с антенной в комплекте.

---

## 🔧 Гайд по сборке

### Перед началом

- Понадобится паяльник, припой и флюс
- Все кнопки: **один провод на GPIO**, **второй на GND**
- Всё питается от **3.3В** — никогда не подключай к 5В или напрямую к батарее
- Проверяй каждое соединение перед включением
- Используй мультиметр для прозвонки GND

---

### Шаг 1 — Дисплей (ST7789 240×240)

Начни с дисплея — это самая важная часть.

| Пин ST7789 | Куда |
|------------|------|
| GND | GND |
| VCC | 3V3 |
| SCL | GPIO 18 |
| SDA | GPIO 23 |
| RST | GPIO 4 |
| DC | GPIO 21 |
| CS | GPIO 5 |
| BL | 3V3 |

> **Важно:** BL идёт напрямую на 3V3, резистор не нужен.

---

### Шаг 2 — Кнопки

4 кнопки. Каждая: один провод на GPIO, второй на GND.

| Кнопка | GPIO |
|--------|------|
| Вверх / Влево | GPIO 25 |
| Вниз / Вправо | GPIO 26 |
| Выбор / ОК | GPIO 27 |
| Назад | GPIO 14 |

> Кнопка при нажатии замыкает GPIO на GND — не на 3V3.

---

### Шаг 3 — ИК-передатчик (TSAL6200 × 2 + BC547)

Оба диода параллельно, у каждого свой резистор 47 Ом. Транзистор BC547 управляет ими.

```
GPIO 33 ──── 1кОм ──── База BC547
                        Эмиттер BC547 ──── GND
                        Коллектор BC547 ──┬── 47 Ом ──── Анод TSAL6200 #1
                                          └── 47 Ом ──── Анод TSAL6200 #2
                        Катоды TSAL6200 ──── GND
```

> ⚠️ **Полярность диодов:** длинная ножка — анод (+), короткая — катод (−).

---

### Шаг 4 — ИК-приёмник (TSOP4838)

3 ножки. Смотришь на плоскую сторону слева направо:

| Пин | Куда |
|-----|------|
| OUT (левый) | GPIO 35 |
| GND (средний) | GND |
| VS (правый) | 3V3 |

---

### Шаг 5 — Радио 433МГц (CC1101)

Использует второй SPI шины ESP32 — конфликта с дисплеем нет.

| Пин CC1101 | Куда |
|------------|------|
| VCC | 3V3 |
| GND | GND |
| SCK | GPIO 22 |
| MOSI | GPIO 17 |
| MISO | GPIO 19 |
| CSN | GPIO 16 |
| GDO0 | GPIO 32 |
| GDO2 | **Не подключать** |

> ⚠️ **GDO2 не подключай** — оставь незапаянным.

---

### Шаг 6 — NFC (PN532)

**Сначала** выстави DIP переключатели на плате PN532 в режим I2C:
- SW1 = ON
- SW2 = OFF

Затем паяй только 4 пина:

| Пин PN532 | Куда |
|-----------|------|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 13 |
| SCL | GPIO 15 |

> Остальные пины на плате PN532 — не подключай.

---

### Шаг 7 — Питание

Батарея → TP4056 → кулисник → ME6211 → ESP32.

```
Батарея (+) ──── TP4056 B+
Батарея (−) ──── TP4056 B−
TP4056 OUT+ ──── Средний пин кулисника
Крайний пин кулисника ──┬── ME6211 IN
                        └── Конденсатор 1мкФ ──── GND
ME6211 OUT ──┬── ESP32 3V3
             └── Конденсатор 1мкФ ──── GND
ME6211 GND ──── GND
TP4056 OUT− ──── GND
```

> ⚠️ **Конденсаторы обязательны** — без них ESP32 будет перезагружаться.  
> ⚠️ **Батарею напрямую к ESP32 не подключай** — только через ME6211.

---

### Шаг 8 — Финальная проверка

1. Прозвони GND мультиметром везде
2. Убедись что 3V3 **не замкнут на GND**
3. Проверь полярность ИК диодов
4. Проверь положение DIP переключателей PN532
5. Включай — дисплей должен засветиться

---

## 💾 Прошивка

### Вариант А — Готовый бинарник (проще всего)

Скачай `firmware/firmware.bin` из этого репо.

Установи esptool и прошей:

```bash
pip install esptool
esptool.py --port /dev/ttyUSB0 --baud 115200 write_flash 0x0 firmware.bin
```

На Windows замени `/dev/ttyUSB0` на `COM3` (смотри в Диспетчере устройств).

**Как войти в режим прошивки:**
1. Зажми кнопку **BOOT** на ESP32
2. Нажми и отпусти **RST**
3. Отпусти **BOOT**
4. Запускай команду прошивки

---

### Вариант Б — Сборка из исходников

Требования:
- Расширение [PlatformIO](https://platformio.org/) для VSCode
- Python 3.10–3.13 (**Python 3.14 пока НЕ поддерживается**)

```bash
git clone https://github.com/pr3y/Bruce.git
cd Bruce
```

Скопируй папку `boards/nemo/` из этого репо в `Bruce/boards/`.

Установи `default_envs = nemo` в `platformio.ini`, затем:

```bash
pio run -t upload
pio run -t uploadfs
```

**Linux — если ошибка доступа к порту:**
```bash
sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB0
```

**Если прошивка падает с ошибкой подключения**, добавь в `platformio.ini`:
```ini
upload_speed = 115200
board_upload.speed = 115200
```

Затем войди в режим прошивки вручную (см. Вариант А) и запускай заново.

---

## 📡 Использование

### WebUI

1. На устройстве: **WiFi → Start WiFi AP**
2. Подключись к точке доступа Bruce (пароль: `brucenet`)
3. Открой `http://172.0.0.1` в браузере

### ИК — пульты от телевизоров и кондиционеров

Зайди в **IR** в меню. Направь пульт на датчик TSOP4838 и нажми capture.

> Некоторые пульты кондиционеров (TOSOT/Gree) отправляют очень длинные сигналы. Если не записывается — попробуй режим RAW.

### 433МГц — ворота и пульты

Зайди в **RF** в меню.

### NFC — карты

Зайди в **RFID** в меню. DIP переключатели PN532 должны стоять в режиме I2C.

---

## 📋 Что сделано / что в планах

- [x] Дисплей работает
- [x] Кнопки работают
- [x] ИК-передатчик и приёмник работают
- [x] Питание работает
- [x] Прошивка Bruce запущена
- [x] Клавиатура работает
- [x] WebUI доступен по WiFi
- [ ] CC1101 433МГц — жду модуль
- [ ] PN532 NFC — жду модуль
- [ ] Релиз с готовой прошивкой

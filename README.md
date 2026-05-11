# ESP32-Flipper

> A DIY Flipper Zero alternative built on ESP32 with Bruce firmware, 433MHz radio, NFC and IR support.

![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![Firmware](https://img.shields.io/badge/firmware-Bruce-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-red)

---

## 📷 Photos

> *(Coming soon)*

---

## 🧰 Hardware

### Components List

| Component | Description | ~Price (AliExpress) |
|-----------|-------------|----------------------|
| ESP32-WROOM-32 (38-pin) | Main microcontroller | ~$3 |
| ST7789 240×240 Display | Main screen | ~$2 |
| CC1101 433MHz module | Sub-GHz radio (pending) | ~$2 |
| PN532 NFC module | NFC read/emulate (pending) | ~$2 |
| TSAL6200 × 2 | IR transmitter LEDs | ~$0.5 |
| TSOP4838 | IR receiver | ~$0.5 |
| BC547 | NPN transistor (IR) | ~$0.1 |
| TP4056 | LiPo charger module | ~$0.5 |
| ME6211 | 3.3V LDO regulator | ~$0.5 |
| Resistor 1kΩ | IR transistor base | — |
| Resistor 47Ω × 2 | IR LED current limit | — |
| Capacitor 1µF × 2 | Power filtering | — |
| Rocker switch | Power on/off | — |
| LiPo battery | Power source | ~$3 |

---

## 🔌 Wiring

### Display — ST7789 (240×240)

| ST7789 Pin | ESP32 GPIO |
|------------|------------|
| GND | GND |
| VCC | 3V3 |
| SCL | GPIO 18 |
| SDA | GPIO 23 |
| RST | GPIO 4 |
| DC | GPIO 21 |
| CS | GPIO 5 |
| BL | 3V3 |

---

### Buttons

| Button | GPIO | Other pin |
|--------|------|-----------|
| Up / Left | GPIO 25 | GND |
| Down / Right | GPIO 26 | GND |
| Select / OK | GPIO 27 | GND |
| Back | GPIO 14 | GND |

---

### IR Transmitter — TSAL6200 × 2 + BC547

Both LEDs connected in parallel, each with its own 47Ω resistor.

| Connection | Detail |
|------------|--------|
| BC547 Emitter | GND |
| BC547 Base | GPIO 33 (via 1kΩ resistor) |
| BC547 Collector | TSAL6200 Cathodes |
| TSAL6200 Anodes | Rocker switch (+) via 47Ω resistors |

---

### IR Receiver — TSOP4838

| TSOP4838 Pin | Connection |
|--------------|------------|
| OUT (left) | GPIO 35 |
| GND (middle) | GND |
| VS (right) | 3V3 |

---

### 433MHz Radio — CC1101

> Uses ESP32 second SPI bus. **Pending arrival.**

| CC1101 Pin | ESP32 GPIO |
|------------|------------|
| VCC | 3V3 |
| GND | GND |
| SCK | GPIO 22 |
| MOSI | GPIO 17 |
| MISO | GPIO 19 |
| CSN | GPIO 16 |
| GDO0 | GPIO 32 |
| GDO2 | Not connected |

---

### NFC — PN532

> I2C mode. Set DIP switches: SW1=ON, SW2=OFF. **Pending arrival.**

| PN532 Pin | ESP32 GPIO |
|-----------|------------|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 13 |
| SCL | GPIO 15 |

---

### Power

| Connection | Detail |
|------------|--------|
| ME6211 OUT | 3V3 → ESP32 |
| ME6211 GND | GND → ESP32 |
| ME6211 IN | Rocker switch (far pin) |
| Rocker switch (middle pin) | TP4056 OUT+ |
| TP4056 OUT− | GND |
| Capacitor 1 (1µF) | Between ME6211 IN and GND |
| Capacitor 2 (1µF) | Between ME6211 OUT and GND |

---

## 💾 Firmware

This project uses **[Bruce firmware](https://github.com/pr3y/Bruce)** with a custom board configuration.

### Build Requirements

- [PlatformIO](https://platformio.org/) (VSCode extension)
- Python 3.10–3.13 (**important: 3.14 is not supported yet**)

### Setup

```bash
git clone https://github.com/pr3y/Bruce.git
cd Bruce
```

Create `boards/nemo/` folder with three files:

- `nemo.ini` — board config
- `pins_arduino.h` — pin definitions with `HAS_3_BUTTONS` and `HAS_SCREEN`
- `interface.cpp` — InputHandler for 4 physical buttons

Set `default_envs = nemo` in `platformio.ini` and flash:

```bash
pio run -t upload
pio run -t uploadfs
```

### USB Access on Linux (Fedora)

```bash
sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB0
```

### Flash speed issue

If upload fails, add to `platformio.ini`:
```ini
upload_speed = 115200
board_upload.speed = 115200
```

Enter bootloader manually: hold **BOOT**, press **RST**, release **BOOT**, then flash.

### WebUI

Connect to Bruce WiFi AP → open `http://172.0.0.1` in browser.

---

## 🖨️ Case

- Printer: Ender 3 V3 KE
- Material: PLA

> STL files coming soon (lid in progress)

---

## 📋 TODO

- [x] Display working (ST7789 240×240)
- [x] Buttons working (4 buttons)
- [x] IR transmitter/receiver working
- [x] Power system working
- [x] Bruce firmware running
- [x] Keyboard input working (HAS_3_BUTTONS fix)
- [x] WebUI accessible via WiFi
- [ ] CC1101 433MHz — awaiting module
- [ ] PN532 NFC — awaiting module
- [ ] Case lid — in progress
- [ ] IR database for AC/TV
- [ ] GitHub release with pre-built firmware

---
---

# ESP32-Flipper (на русском)

> DIY аналог Flipper Zero на базе ESP32 с прошивкой Bruce, радиомодулем 433МГц, NFC и ИК.

---

## 🧰 Железо

### Список компонентов

| Компонент | Описание | ~Цена (AliExpress) |
|-----------|----------|---------------------|
| ESP32-WROOM-32 (38 пин) | Основной микроконтроллер | ~270₽ |
| Дисплей ST7789 240×240 | Экран | ~180₽ |
| Модуль CC1101 433МГц | Радио Sub-GHz (ожидается) | ~200₽ |
| Модуль PN532 NFC | Чтение и эмуляция NFC (ожидается) | ~200₽ |
| TSAL6200 × 2 | ИК-диоды передатчика | ~50₽ |
| TSOP4838 | ИК-приёмник | ~50₽ |
| BC547 | NPN транзистор (для ИК) | ~10₽ |
| TP4056 | Зарядник LiPo | ~50₽ |
| ME6211 | Стабилизатор 3.3В | ~50₽ |
| Резистор 1кОм | База транзистора | — |
| Резистор 47 Ом × 2 | Ограничение тока ИК-диодов | — |
| Конденсатор 1мкФ × 2 | Фильтрация питания | — |
| Кулисный переключатель | Включение питания | — |
| LiPo аккумулятор | Источник питания | ~270₽ |

---

## 🔌 Схема подключения

### Дисплей — ST7789 (240×240)

| Пин ST7789 | GPIO ESP32 |
|------------|------------|
| GND | GND |
| VCC | 3V3 |
| SCL | GPIO 18 |
| SDA | GPIO 23 |
| RST | GPIO 4 |
| DC | GPIO 21 |
| CS | GPIO 5 |
| BL | 3V3 |

---

### Кнопки

| Кнопка | GPIO | Второй провод |
|--------|------|---------------|
| Вверх / Влево | GPIO 25 | GND |
| Вниз / Вправо | GPIO 26 | GND |
| Выбор / ОК | GPIO 27 | GND |
| Назад | GPIO 14 | GND |

---

### ИК-передатчик — TSAL6200 × 2 + BC547

Оба диода подключены параллельно, у каждого свой резистор 47 Ом.

| Соединение | Описание |
|------------|----------|
| Эмиттер BC547 | GND |
| База BC547 | GPIO 33 (через 1кОм) |
| Коллектор BC547 | Катоды TSAL6200 |
| Аноды TSAL6200 | Крайний пин кулисника (+) через 47 Ом |

---

### ИК-приёмник — TSOP4838

| Пин TSOP4838 | Подключение |
|--------------|-------------|
| OUT (левый) | GPIO 35 |
| GND (средний) | GND |
| VS (правый) | 3V3 |

---

### Радио 433МГц — CC1101

> Второй SPI шины ESP32. **Ожидается.**

| Пин CC1101 | GPIO ESP32 |
|------------|------------|
| VCC | 3V3 |
| GND | GND |
| SCK | GPIO 22 |
| MOSI | GPIO 17 |
| MISO | GPIO 19 |
| CSN | GPIO 16 |
| GDO0 | GPIO 32 |
| GDO2 | Не подключать |

---

### NFC — PN532

> Режим I2C. DIP: SW1=ON, SW2=OFF. **Ожидается.**

| Пин PN532 | GPIO ESP32 |
|-----------|------------|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 13 |
| SCL | GPIO 15 |

---

### Питание

| Соединение | Описание |
|------------|----------|
| ME6211 OUT | 3V3 → ESP32 |
| ME6211 GND | GND → ESP32 |
| ME6211 IN | Крайний пин кулисника |
| Средний пин кулисника | TP4056 OUT+ |
| TP4056 OUT− | GND |
| Конденсатор 1 (1мкФ) | Между ME6211 IN и GND |
| Конденсатор 2 (1мкФ) | Между ME6211 OUT и GND |

---

## 💾 Прошивка

Используется **[прошивка Bruce](https://github.com/pr3y/Bruce)** с кастомной конфигурацией.

### Требования

- [PlatformIO](https://platformio.org/) (расширение VSCode)
- Python 3.10–3.13 (**важно: 3.14 пока не поддерживается**)

### Сборка

```bash
git clone https://github.com/pr3y/Bruce.git
cd Bruce
```

Создай папку `boards/nemo/` с тремя файлами:

- `nemo.ini` — конфиг платы
- `pins_arduino.h` — пины с `HAS_3_BUTTONS` и `HAS_SCREEN`
- `interface.cpp` — обработчик 4 кнопок

Установи `default_envs = nemo` в `platformio.ini` и прошивай:

```bash
pio run -t upload
pio run -t uploadfs
```

### Доступ к USB на Linux (Fedora)

```bash
sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB0
```

### Проблема со скоростью прошивки

```ini
upload_speed = 115200
board_upload.speed = 115200
```

Вход в режим прошивки: зажми **BOOT**, нажми **RST**, отпусти **BOOT**, прошивай.

### WebUI

Подключись к точке доступа Bruce → открой `http://172.0.0.1` в браузере.

---

## 🖨️ Корпус

- Принтер: Ender 3 V3 KE
- Материал: PLA

> STL файлы появятся позже (крышка в разработке)

---

## 📋 Что сделано / что в планах

- [x] Дисплей работает (ST7789 240×240)
- [x] Кнопки работают (4 кнопки)
- [x] ИК-передатчик и приёмник работают
- [x] Питание работает
- [x] Прошивка Bruce запущена
- [x] Клавиатура работает (фикс HAS_3_BUTTONS)
- [x] WebUI доступен по WiFi
- [ ] CC1101 433МГц — жду модуль
- [ ] PN532 NFC — жду модуль
- [ ] Крышка корпуса — в разработке
- [ ] База ИК сигналов для кондиционеров/телевизоров
- [ ] Релиз с готовой прошивкой

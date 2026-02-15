# Arduino Nano v3 Specifications

## Overview

The Arduino Nano is a compact, breadboard-friendly board based on the ATmega328P microcontroller.

## Microcontroller Specifications

| Parameter | Value |
|-|-|
| Microcontroller | ATmega328P |
| Architecture | 8-bit AVR |
| Operating Voltage | 5V |
| Input Voltage (Vin) | 7-12V (recommended) |
| Clock Speed | 16 MHz |

## Memory

| Type | Size |
|-|-|
| Flash Memory | 32 KB (2 KB used by bootloader) |
| SRAM | 2 KB |
| EEPROM | 1 KB |

## I/O

| Parameter | Value |
|-|-|
| Digital I/O Pins | 14 (D0-D13) |
| PWM Pins | 6 (D3, D5, D6, D9, D10, D11) |
| Analog Input Pins | 8 (A0-A7) |
| DC Current per I/O Pin | 40 mA |
| DC Current for 3.3V Pin | 50 mA |

## Communication

| Interface | Pins |
|-|-|
| UART | TX (D1), RX (D0) |
| I2C (TWI) | SDA (A4), SCL (A5) |
| SPI | MOSI (D11), MISO (D12), SCK (D13), SS (D10) |

## Physical

| Parameter | Value |
|-|-|
| Length | 45 mm |
| Width | 18 mm |
| Weight | 7 g |

## Pinout

```
                    +-----+
        +---[USB]---+     |
        |   [RESET] |     |
    D1  | TX    VIN |     |
    D0  | RX    GND |     |
   RST  | RST   RST |     |
   GND  | GND   5V  |     |
    D2  | D2    A7  |     |
    D3  | D3~   A6  |     |
    D4  | D4    A5  | SCL |
    D5  | D5~   A4  | SDA |
    D6  | D6~   A3  |     |
    D7  | D7    A2  |     |
    D8  | D8    A1  |     |
    D9  | D9~   A0  |     |
   D10  | D10~  REF |     |
   D11  | D11~  3V3 |     |
   D12  | D12   D13 | LED |
        +-----------+     |
                    +-----+

~ = PWM capable
```

## References

- [Arduino Nano Official Documentation](https://docs.arduino.cc/hardware/nano)
- [ATmega328P Datasheet (PDF)](https://docs.arduino.cc/resources/datasheets/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf)
- [Arduino Nano Datasheet (PDF)](https://www.handsontec.com/dataspecs/arduino-nano.pdf)
- [Arduino Store - Nano](https://store.arduino.cc/products/arduino-nano)

# Bowsprit Spinner

## Project Info

* **Name:** BowspritSpinner
* **Description:** Slow rotation motor controller for refinishing a bowsprit
* **Goal:** Rotate bowsprit at constant slow speed for even finish application

## Requirements

#### Motor Control

1. Rotate stepper motor at slow speed (0-10 RPM, default 0 RPM - stopped)
2. Continuous rotation when powered
3. Direction selectable in code
4. Faster button (D2) - increase speed by 1 RPM (first press: 0→1 RPM)
5. Slower button (D3) - decrease speed by 1 RPM (stops at 0 RPM)
6. Every 10 seconds write current RPM to serial port (9600 baud)

## Hardware

* **MCU:** Arduino Nano v3
* **Motor:** YEJMKJ NEMA 17 (42BL4002-24Ypro)
* **Driver:** Integrated IDC1-42
* **Belt Drive:** 3:1 ratio (motor to bowsprit)
* **Bootloader:** New (ATmega328P, 115200 baud) - FQBN: `arduino:avr:nano`
* **Power:** 12-30V DC for motor/driver

## Motor Specifications

| Parameter | Value |
|-|-|
| Step Angle | 1.8° |
| Steps/Rev (base) | 200 |
| Rated Current | 1.5A |
| Holding Torque | 0.41 N.m (58 oz-in) |
| Phases | 2 (bipolar) |

## Driver Specifications (IDC1-42)

| Parameter | Value |
|-|-|
| Input Voltage | 12-30V DC |
| Microstepping | 200-3600 steps/rev (DIP configurable) |
| Pulse Frequency | 0-90 KHz |
| Pulse Width | >2.5μs |
| Direction Setup | 50μs before pulse |

## DIP Switch Settings (Microstepping)

| pul/rev | SW2 | SW3 | SW4 |
|-|-|-|-|
| 200 | on | on | on |
| 400 | off | on | on |
| 800 | on | off | on |
| 1600 | off | off | on |
| 3200 | on | on | off |
| 1000 | off | on | off |
| 2000 | on | off | off |
| 3600 | off | off | off |

SW1: Current setting (OFF=1.0A, ON=1.5A)

## Pin Connections

### Arduino Nano v3

| Arduino Pin | Type | Function | Connected To |
|-|-|-|-|
| D2 | Input | Faster button | White wire to D2, Green wire to GND (INPUT_PULLUP) |
| D3 | Input | Slower button | Black wire to D3, Green wire to GND (INPUT_PULLUP) |
| D8 | Output | Direction signal | Driver DR- |
| A5 (D19) | Output | Pulse signal | Driver PU- |
| D13 | Output | Running indicator | Built-in LED (toggles every 100 pulses) |
| 5V | Power | Opto-isolator common | Driver XCOM |
| GND | Power | Common ground | Power supply GND |

### IDC1-42 Driver

| Driver Pin | Type | Function | Connected To |
|-|-|-|-|
| PU- | Input | Pulse input | Arduino A5 (D19) |
| DR- | Input | Direction input | Arduino D8 |
| MF- | Input | Enable input | (float - not connected) |
| XCOM | Power | Opto-isolator common | Arduino 5V |
| DC+ | Power | Motor power positive | External 12-24V DC |
| GND | Power | Motor power ground | External power GND |

## Configuration

| Parameter | Value | Description |
|-|-|-|
| Microstepping | 200 | Full step (SW2=on, SW3=on, SW4=on) |
| Belt Ratio | 3:1 | Motor:bowsprit (motor runs 3x faster) |
| Target RPM | 0 | Starts stopped, adjustable 0-10 RPM |
| Pulse delay | calculated | Based on steps/rev, belt ratio, and RPM |

## Calculations

For 2 RPM bowsprit with 3:1 belt drive and 200 steps/rev:
- Motor RPM = 2 * 3 = 6 RPM
- Steps per second = (200 * 6) / 60 = 20 steps/sec
- Pulse interval = 1000000 / 20 = 50000 μs (50ms) between pulses

## Code Structure

```
/BowspritSpinner
  project_outline.md              - This document
  /BowspritSpinner
    BowspritSpinner.ino           - Main sketch
  /docs
    ArduinoNanoV3_Specs.md        - Arduino Nano specifications
    StepperMotorwDriverL.pdf      - Motor/driver datasheet
```

## Driver Wiring

| Wire Color | Connection |
|-|-|
| Red | XCOM (Arduino 5V) |
| White | PU- (Arduino A5/D19) |
| Black | GND (Power supply ground) |

## Switch Wiring

| Wire Color | Connection |
|-|-|
| Green | Common (GND) |
| White | Faster button (D2) |
| Black | Slower button (D3) |

## Notes

* Bowsprit should rotate slowly (1-5 RPM) for even varnish/epoxy application
* Motor driver has built-in overvoltage/undervoltage protection
* Green LED on driver indicates power status (flashing = fault)

## References

* [Amazon - YEJMKJ NEMA 17 Stepper Motor with Integrated Driver](https://www.amazon.com/dp/B0FHHSQN99)
* [Amazon - Arduino Nano v3](https://www.amazon.com/dp/B0DN5MSSCC)

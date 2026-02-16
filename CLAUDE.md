# BowspritSpinner

Slow rotation stepper motor controller for refinishing a bowsprit.

## Project Structure
- `project_outline.md` — Hardware spec, pin mappings, requirements
- `BowspritSpinner/BowspritSpinner.ino` — Main Arduino sketch
- `docs/` — Datasheets and hardware specs

## Hardware
- Arduino Nano v3 (CH340 clone)
- YEJMKJ NEMA 17 stepper with integrated IDC1-42 driver
- Bootloader: New (ATmega328P, 115200 baud)
- FQBN: `arduino:avr:nano`

## Build & Upload
```bash
# Compile
arduino-cli compile --fqbn arduino:avr:nano BowspritSpinner

# Upload (Nano is on /dev/ttyUSB1 via CH340)
arduino-cli upload --fqbn arduino:avr:nano --port /dev/ttyUSB1 BowspritSpinner

# Serial monitor (9600 baud)
stty -F /dev/ttyUSB1 9600 raw -echo && cat /dev/ttyUSB1
```

## WSL2 USB Setup
Nano must be attached via usbipd from Windows PowerShell (admin):
```powershell
usbipd bind --busid 4-4
usbipd attach --wsl --busid 4-4
```

## Notes
- Always keep `project_outline.md` in sync with code changes
- CP210x on `/dev/ttyUSB0` is a different device, not the Nano

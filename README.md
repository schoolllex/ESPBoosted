# Custom ESP32-WROOM-32 All-in-One DevBoard

A custom, feature-rich ESP32-WROOM-32 development board featuring built-in environmental sensors, power management, and expansion interfaces. All project files, schematics, and manufacturing assets are included in the `.zip` archive within this repository.

## Features

* **Core & Programming:** ESP32-WROOM-32E module with onboard CH340K USB-to-UART bridge and automatic flash circuit.
* **Power Management:** AP2112K-3.3 LDO regulator, TP4056 LiPo battery charger, and power path management.
* **Sensors & Peripherals:**
* BME280 (Temperature, Humidity, Pressure)
* TSL25911FN (Digital Light Sensor)
* MPU-6050 (6-axis IMU / Accelerometer & Gyroscope)
* WS2812B RGB NeoPixel LED & Passive Piezo Buzzer
* MicroSD Card Slot (SPI mode)


* **Expansion:** MCP23017 16-bit I/O expander, ADS1115 16-bit ADC, and a Qwiic/STEMMA QT connector.

## Getting Started

1. Download and extract the project files from the `.zip` archive in this repository.
2. Open the project in **KiCad** to view schematics, layouts, and manufacturing files (Gerber/BOM/CPL).
3. Connect the board to your computer via a USB-C cable.
4. Flash your code using the Arduino IDE or your preferred development environment.
5. Enjoy your custom DevBoard!

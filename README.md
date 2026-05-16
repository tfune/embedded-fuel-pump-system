# Embedded Fuel Pump System

An embedded fuel pump simulation system built on an Arduino Mega using a finite state machine architecture, interrupt-driven flow sensing, MOSFET-controlled pump operation, and OLED-based user interaction.

This project was developed to demonstrate core embedded systems concepts including:

* finite state machines (FSM)
* interrupt service routines (ISR)
* hardware abstraction drivers
* real-time embedded control
* fault handling and recovery
* hardware/software integration

---

# Features

* Finite state machine architecture
* Interrupt-driven flow sensor handling
* ISR-safe atomic pulse access
* Dedicated `FlowSensor` and `PumpDriver` abstractions
* MOSFET-based diaphragm pump control
* OLED user interface with keypad input
* Real-time fuel and cost calculation
* Pump timeout safety protection
* Flow sensor fault detection
* ERROR state handling and recovery

---

# Hardware Used

| Component       | Description                    |
| --------------- | ------------------------------ |
| Microcontroller | Arduino Mega 2560              |
| Display         | SSD1306 OLED Display           |
| Input           | 4x4 Matrix Keypad              |
| Flow Sensor     | YF-S201C Water Flow Sensor     |
| Pump            | 12V Diaphragm Water Pump       |
| Pump Driver     | MOSFET-based switching circuit |
| Button Input    | Pump trigger button            |

---

# System Architecture

```text
FuelPumpSystem
├── InputHandler
├── Display
├── FlowSensor
└── PumpDriver
```

## Driver Responsibilities

### FlowSensor

* interrupt-driven pulse counting
* ISR-safe atomic data access
* fuel volume calculation
* sensor calibration and reset handling

### PumpDriver

* MOSFET GPIO control
* pump enable/disable logic
* operating state tracking

### InputHandler

* keypad scanning
* trigger button input
* one-cycle event generation

### Display

* OLED rendering
* state-specific UI screens
* fault message display

---

# State Machine

```text
READY
↓
FUEL_SELECTION
↓
PUMPING
↓
COMPLETE

ERROR state accessible from fault conditions
```

## State Summary

* **READY** → waits for user input
* **FUEL_SELECTION** → selects fuel pricing
* **PUMPING** → controls pump operation and monitors safety conditions
* **COMPLETE** → displays transaction summary
* **ERROR** → disables pump and displays fault information

---

# Safety Features

## Pump Timeout Protection

Automatically disables the pump if runtime exceeds a maximum limit.

```cpp
if(pump.isRunning() &&
   millis() - pumpStartTime >= MAX_PUMP_TIME)
```

---

## Flow Fault Detection

Detects conditions where:

* the pump is active
* but flow sensor pulses are not increasing

Possible fault conditions:

* disconnected flow sensor
* clogged tubing
* dry-running pump
* sensor failure

---

# Flow Sensor Calibration

The YF-S201C flow sensor was experimentally calibrated using measured fluid volume.

Measured values:

* 114 pulses
* 16 oz dispensed

Calibration factor:

```text
7.125 pulses/oz
```

---

# Embedded Concepts Demonstrated

* Finite state machines
* Interrupt service routines
* Atomic data access
* Hardware abstraction layers
* Modular embedded drivers
* Fault detection and recovery
* Embedded GPIO control
* Sensor calibration
* Hardware/software integration

---

# Project Structure

```text
Display.cpp / Display.h
FlowSensor.cpp / FlowSensor.h
FuelPumpSystem.cpp / FuelPumpSystem.h
InputHandler.cpp / InputHandler.h
PumpDriver.cpp / PumpDriver.h
main.cpp
```

---

# Demo

(Add photos, wiring diagrams, or demo video here.)

---

# Future Improvements

* Store calibration and fuel pricing settings in EEPROM
* Convert transaction cost calculations to integer cents
* Design a custom PCB for the pump driver and sensor interface
* Add PWM-based pump speed control
* Port firmware to an STM32 microcontroller

---

# Author

Trevor Fune
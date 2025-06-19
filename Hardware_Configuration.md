# Hardware Configuration & Pin Mapping for Advanced OOP-Based Robotic System

**Project:** Advanced OOP-Based Robotic System  
**Course:** CS-112  
**Authors:** 
Usman Azhar [GitHub](https://github.com/daffy-usman)  
Fatima Rehman [GitHub](https://github.com/Fatima-RM) 

---

## Overview

This document provides the necessary hardware pin mapping and configuration guidelines to assemble and connect all components for the provided robotic system code.

---

## 1. Microcontroller

- **Platform:** Arduino Mega 2560 (Recommended for sufficient I/O)

---

## 2. Pin Mapping

| **Component**          | **Function**           | **Pin(s) Used**      | **Notes**                       |
|------------------------|------------------------|----------------------|----------------------------------|
| **PIR Motion Sensor**  | Left PIR Data          | 35                   | Digital input                    |
|                        | Right PIR Data         | 34                   | Digital input                    |
| **LN298 Motor Driver** | IN1                    | 22                   | Digital output                   |
|                        | IN2                    | 23                   | Digital output                   |
|                        | IN3                    | 24                   | Digital output                   |
|                        | IN4                    | 25                   | Digital output                   |
| **IR Sensors**         | Left IR                | 26                   | Digital input (LOW = detected)   |
|                        | Right IR               | 27                   | Digital input (LOW = detected)   |
| **Ultrasonic Sensors** | Left: Trigger/Echo     | 30 / 31              | Use NewPing library, max 200cm   |
|                        | Front: Trigger/Echo    | 28 / 29              |                                  |
|                        | Right: Trigger/Echo    | 32 / 33              |                                  |
| **Serial Debug Output**| Serial TX/RX           | Built-in (USB)       | Baud: 9600                       |

---

## 3. Sensor & Actuator Details

### PIR Motion Sensors (x2)
- **Pins:** 35 (Left), 34 (Right)
- **Type:** Digital output (HIGH when motion detected)
- **Stabilization:** Initial stabilization required (10s)

### IR Obstacle Sensors (x2)
- **Pins:** 26 (Left), 27 (Right)
- **Type:** Digital output (LOW when obstacle detected)

### Ultrasonic Distance Sensors (x3)
- **Model:** HC-SR04 or compatible
- **Pins:**
  - Left: Trigger 30, Echo 31
  - Front: Trigger 28, Echo 29
  - Right: Trigger 32, Echo 33
- **Range:** Up to 200cm (as set in `NewPing` initialization)

### LN298 Motor Driver (Dual H-Bridge)
- **Pins:**
  - IN1: 22
  - IN2: 23
  - IN3: 24
  - IN4: 25
- **Motors:** 2 DC motors (left/right)

---

## 4. Power Specifications

| **Component**         | **Voltage** | **Current**         |
|-----------------------|-------------|---------------------|
| Arduino Mega 2560     | 5V (USB or VIN 7-12V) | < 500mA  |
| PIR Sensors           | 5V          | < 60mA each         |
| IR Sensors            | 5V          | < 20mA each         |
| Ultrasonic Sensors    | 5V          | < 15mA each         |
| LN298 + Motors        | 7-12V (motors) & 5V (logic) | ~1A+ (motors) |
| **Note:** Use a separate battery for motors if possible to avoid brownouts on logic. |

---

## 5. Required Libraries

- **NewPing** (for ultrasonic sensors)
  - Install via Library Manager: `Sketch > Include Library > Manage Libraries... > NewPing`

---

## 6. Assembly Notes

- **GND:** All sensor and actuator grounds must be connected to Arduino GND.
- **Stabilization:** Allow 10 seconds after startup for PIR sensors to stabilize.
- **Motor Driver:** Ensure the LN298's "Enable" pins are HIGH (if present) for motor operation.

---

## 7. Schematic Diagram

```
[Not included here: Please wire according to pin mapping table above. Use Fritzing or a similar tool to visualize.]
```

---

## 8. Quick Reference Table

| **Pin** | **Function**             |
|---------|--------------------------|
| 22      | Motor IN1                |
| 23      | Motor IN2                |
| 24      | Motor IN3                |
| 25      | Motor IN4                |
| 26      | IR Sensor LEFT           |
| 27      | IR Sensor RIGHT          |
| 28      | Ultrasonic FRONT Trigger |
| 29      | Ultrasonic FRONT Echo    |
| 30      | Ultrasonic LEFT Trigger  |
| 31      | Ultrasonic LEFT Echo     |
| 32      | Ultrasonic RIGHT Trigger |
| 33      | Ultrasonic RIGHT Echo    |
| 34      | PIR Sensor RIGHT         |
| 35      | PIR Sensor LEFT          |

---

## 9. Setup Checklist

- [ ] Double-check all pin connections and power supplies.
- [ ] Install required libraries before uploading the code.
- [ ] After upload, monitor Serial output (9600 baud) for status messages.
- [ ] Wait for PIR sensor stabilization before triggering motion.
- [ ] Test each sensor and motor individually for troubleshooting.

---

**For questions or further guidance, contact the project authors.**

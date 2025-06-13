# Autonomous Robot Navigation Using Sensors and OOP

**Authors:**  
Usman Azhar [GitHub](https://github.com/daffy-usman)  
Fatima Rehman [GitHub]()

---

## Abstract

This project demonstrates the design and development of an autonomous robot built on the Arduino platform. The robot is equipped with multiple Passive Infrared (PIR) sensors for human motion detection and uses ultrasonic and infrared (IR) sensors for real-time obstacle avoidance. The control logic is implemented in C++ utilizing Object-Oriented Programming (OOP) principles such as abstraction, inheritance, and polymorphism to ensure a modular, scalable, and maintainable software architecture.

Through the integration of diverse sensors, the robot achieves robust perception of its environment, enabling dynamic and responsive navigation. This project presents a cost-effective approach to autonomous robotics, suitable for security and assistance applications. It also addresses challenges such as sensor noise and synchronization, optimizing the robot's real-world performance.

---

## Table of Contents

- [Introduction](#introduction)
- [Problem Statement](#problem-statement)
- [Objectives](#objectives)
- [Hardware Design](#hardware-design)
    - [Sensor Configuration](#sensor-configuration)
    - [Actuation and Power](#actuation-and-power)
    - [Connectivity and Wiring](#connectivity-and-wiring)
- [Software Design](#software-design)
    - [Motor Control Classes](#motor-control-classes)
    - [Sensor Classes](#sensor-classes)
    - [Robot Behavior Integration](#robot-behavior-integration)
- [UML Class Diagram](#uml-class-diagram)
- [Use Case Diagram](#use-case-diagram)
- [C++ Implementation and OOP Concepts](#c-implementation-and-oop-concepts)
- [Testing and Debugging](#testing-and-debugging)
- [Challenges Faced](#challenges-faced)
- [Conclusion](#conclusion)
- [Future Work](#future-work)
- [References](#references)

---

## Introduction

Autonomous robots are transforming industries such as security, healthcare, and automation by operating with minimal human intervention and adapting to dynamic environments. To navigate effectively, these robots must sense and interpret their surroundings using multiple sensors. This project focuses on developing an autonomous robot that combines ultrasonic, IR, and PIR sensors for intelligent navigation toward detected human motion while avoiding obstacles, all orchestrated by a C++ OOP-based modular software framework.

---

## Problem Statement

The demand for cost-effective and efficient autonomous robots is growing, especially for applications requiring safe navigation without manual control. These robots must detect human presence and obstacles in real-time, processing input from multiple sensors within the computational and power constraints of embedded systems like Arduino. The primary challenge is achieving reliable sensor fusion and responsive motion control under hardware limitations to enable smooth, uninterrupted navigation.

---

## Objectives

- **Motion Detection Using PIR Sensors:** Employ multiple PIR sensors for omnidirectional human motion detection.
- **Autonomous Navigation:** Develop algorithms for real-time, autonomous movement toward detected motion.
- **Obstacle Avoidance:** Integrate ultrasonic and IR sensors for continuous obstacle detection and avoidance.
- **Modular, Scalable Software:** Implement the control system in C++ using OOP principles for modularity and future extensibility.

---

## Hardware Design

### Sensor Configuration

- **Ultrasonic Sensors (3x HC-SR04):** Positioned at the front, left, and right for real-time distance measurement and obstacle avoidance.
- **Infrared (IR) Sensors (2x):** Installed at the front for close-range object detection.
- **PIR Motion Sensors (4x):** Cover all sides (front, left, right, rear) for 360° human motion detection.

### Actuation and Power

- **Motors:** Two DC motors enable differential steering.
- **L298N Motor Driver:** Interfaces Arduino with DC motors for speed and direction control.
- **Power Supply:** Rechargeable battery pack with voltage regulation for stable operation.

### Connectivity and Wiring

| Component           | Arduino Connection                        |
|---------------------|-------------------------------------------|
| Ultrasonic Sensors  | Digital I/O pins (Trigger & Echo)         |
| IR Sensors          | Analog/Digital input pins                 |
| PIR Sensors         | Digital input pins                        |
| L298N Motor Driver  | PWM (speed), Digital (direction) pins     |
| DC Motors           | Connected via L298N outputs               |
| Power Supply        | VIN and motor driver power input          |

Connections are designed for modularity, noise minimization, and stability.

---

## Software Design

### Motor Control Classes

- **MotorBase Class:** Abstracts basic motor operations (speed, direction).
- **Derived Classes:** Implement specific maneuvers (forward, backward, left, right) with encapsulated motor driver details.

### Sensor Classes

- **Sensor Base Class:** Provides a unified interface (e.g., `readValue()`, `isTriggered()`) for all sensors.
- **Derived Classes:** Ultrasonic, IR, and PIR sensor classes override methods for sensor-specific logic, enabling polymorphic sensor management.

### Robot Behavior Integration

- **MotorController Class:** Central coordinator integrating motor and sensor classes.
    - Prioritizes human motion (PIR)
    - Processes obstacle data (ultrasonic, IR)
    - Applies abstraction and polymorphism for easy hardware upgrades and feature extensions.

---

## UML Class Diagram

This diagram illustrates the modular structure, relationships, and encapsulation of the major classes (MotorBase, movement classes, Sensor, UltrasonicSensor, IRSensor, PIRSensor, Robot).

[View UML Diagram](https://app.eraser.io/workspace/6d3iGFlBS0CWUzSBsD6v?origin=share)

---

## Use Case Diagram

- **Motion Detection:** PIR sensors monitor for human presence in all directions.
- **Autonomous Navigation:** Robot moves toward detected motion.
- **Obstacle Avoidance:** Ultrasonic and IR sensors ensure safe navigation.

---

## C++ Implementation and OOP Concepts

- **Abstraction:** MotorBase class hides low-level hardware details.
- **Inheritance:** Movement classes extend MotorBase for different maneuvers.
- **Polymorphism:** Overridden methods allow runtime selection of movement strategies.
- **Encapsulation:** Internal hardware states are protected and modular.

---

## Testing and Debugging

- **Sensor Verification:** PIR sensors tested for sensitivity and coverage.
- **Obstacle Avoidance:** Evaluated in diverse, cluttered environments.
- **Debugging:** Used Arduino Serial Monitor for real-time data, calibrated thresholds, and synchronized sensor polling.

---

## Challenges Faced

- **Noisy Sensor Data:** Addressed with threshold calibration and filtering.
- **Timing Synchronization:** Improved sensor polling and command synchronization.
- **Sensor Calibration:** Required iterative parameter tuning for reliable detection and tracking.

---

## Conclusion

This project successfully demonstrates robust, modular autonomous robot navigation using integrated PIR, ultrasonic, and IR sensors, coordinated by a C++ OOP framework. The system detects human motion, navigates toward it, and avoids obstacles in real time. The modular software design supports future enhancements and easy adaptation to new hardware.

---

## Future Work

- **Voice Recognition:** For hands-free, remote operation.
- **Camera/Computer Vision:** For facial recognition and advanced target identification.
- **GPS Navigation:** For outdoor path following and area mapping.
- **Scalable Architecture:** OOP design allows seamless integration of new features.

---

## References

- Arduino Official Documentation
- HC-SR04 Ultrasonic Sensor Datasheet
- PIR Sensor Manufacturer Datasheets
- IR Sensor Specifications

---

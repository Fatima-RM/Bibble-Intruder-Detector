# Autonomous Robot Navigation Using Sensors and OOP

**Authors:**  
Usman Azhar [GitHub](https://github.com/daffy-usman)  
Fatima Rehman [GitHub](https://github.com/Fatima-RM)

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
    - [Pin Mapping](#pin-mapping)
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

- **Ultrasonic Sensors (3x HC-SR04):** Positioned at the left, front, and right for real-time distance measurement and obstacle avoidance.
- **Infrared (IR) Sensors (2x):** Installed at the front for close-range object detection.
- **PIR Motion Sensors (2x):** Left and right for human motion detection (expandable to 4 for all-side coverage).

### Actuation and Power

- **Motors:** Two DC motors enable differential steering.
- **L298N Motor Driver:** Interfaces Arduino with DC motors for speed and direction control.
- **Power Supply:** Rechargeable battery pack with voltage regulation for stable operation.

### Connectivity and Wiring

| Component           | Arduino Connection                        |
|---------------------|-------------------------------------------|
| Ultrasonic Sensors  | Digital I/O pins (Trigger & Echo)         |
| IR Sensors          | Digital input pins                        |
| PIR Sensors         | Digital input pins                        |
| L298N Motor Driver  | Digital pins for direction                |
| DC Motors           | Connected via L298N outputs               |
| Power Supply        | VIN and motor driver power input          |

Designed for modularity, noise minimization, and stability.

---

### Pin Mapping

Below is the pin mapping **according to the provided source code**:

| Device / Signal                  | Arduino Pin | Description                                  |
|----------------------------------|-------------|----------------------------------------------|
| **Motor Driver IN1**             | 22          | Motor A direction                            |
| **Motor Driver IN2**             | 23          | Motor A direction                            |
| **Motor Driver IN3**             | 24          | Motor B direction                            |
| **Motor Driver IN4**             | 25          | Motor B direction                            |
| **IR Sensor Left**               | 26          | Digital input for left IR sensor             |
| **IR Sensor Right**              | 27          | Digital input for right IR sensor            |
| **Ultrasonic Front Trig**        | 28          | Trigger pin for front ultrasonic sensor      |
| **Ultrasonic Front Echo**        | 29          | Echo pin for front ultrasonic sensor         |
| **Ultrasonic Left Trig**         | 30          | Trigger pin for left ultrasonic sensor       |
| **Ultrasonic Left Echo**         | 31          | Echo pin for left ultrasonic sensor          |
| **Ultrasonic Right Trig**        | 32          | Trigger pin for right ultrasonic sensor      |
| **Ultrasonic Right Echo**        | 33          | Echo pin for right ultrasonic sensor         |
| **PIR Sensor Right**             | 34          | Digital input for right PIR sensor           |
| **PIR Sensor Left**              | 35          | Digital input for left PIR sensor            |
| **GND**                          | GND         | Common ground                                |
| **VCC**                          | 5V/3.3V     | Sensor and control logic power               |

> **Note:**  
> - PIR sensors in this code are only using two (Left: 35, Right: 34).  
> - All pins above correspond to Arduino MEGA or similar (with sufficient digital I/O).
> - Pins for motor speed (PWM) are not used in this code, only direction pins are wired.

---

## Software Design

### Motor Control Classes

- **MotorController**: Manages DC motor direction and state using bitwise control.
- **MotorBase (abstract concept)**: You can extend with other movement classes for more specialized maneuvers.

### Sensor Classes

- **SensorBase**: Abstract base for all sensors, unifies polling.
- **PIRSensor**: Handles PIR motion detection with state and debounce logic.
- **SensorArray**: Manages ultrasonic and IR sensors, provides filtered readings.

### Robot Behavior Integration

- **NavigationSystem**: Implements state machine for obstacle avoidance and movement, integrates with sensors and motors.

---

## UML Class Diagram

This diagram illustrates the modular structure, relationships, and encapsulation of the major classes (MotorController, SensorBase, PIRSensor, SensorArray, NavigationSystem).

[View UML Diagram](https://app.eraser.io/workspace/6d3iGFlBS0CWUzSBsD6v?origin=share)

---

## Use Case Diagram

- **Motion Detection:** PIR sensors monitor for human presence (left/right).
- **Autonomous Navigation:** Robot moves in response to detected motion.
- **Obstacle Avoidance:** Ultrasonic and IR sensors ensure safe navigation.

---

## C++ Implementation and OOP Concepts

- **Abstraction:** SensorBase and MotorController hide hardware details.
- **Inheritance:** PIRSensor inherits from SensorBase.
- **Polymorphism:** Overridden methods allow sensor extensibility.
- **Encapsulation:** Internal states and timing variables are protected.

---

## Testing and Debugging

- **Sensor Verification:** PIR and IR sensors tested for sensitivity and coverage.
- **Obstacle Avoidance:** Evaluated in cluttered environments.
- **Debugging:** Arduino Serial Monitor used for data and logic verification.

---

## Challenges Faced

- **Noisy Sensor Data:** Solved with calibration and moving averages.
- **Timing Synchronization:** Improved polling and control loop design.
- **Sensor Calibration:** Iterative threshold tuning for reliable detection.

---

## Conclusion

This project successfully demonstrates modular autonomous robot navigation using PIR, ultrasonic, and IR sensors, coordinated by a C++ OOP framework. The system detects motion, navigates, and avoids obstacles in real time. The modular software design supports future enhancements and easy adaptation to new hardware.

---

## Future Work

- **Voice Recognition:** Hands-free remote operation.
- **Computer Vision:** Facial recognition and advanced target identification.
- **GPS Navigation:** Outdoor path following and mapping.
- **Scalable Architecture:** Seamless integration of new features.

---

## References

- Arduino Official Documentation
- HC-SR04 Ultrasonic Sensor Datasheet
- PIR Sensor Manufacturer Datasheets
- IR Sensor Specifications

---

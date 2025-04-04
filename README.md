# AutoNXT - Next-Generation Vehicle Technology 🚗💻

[![FOTA Enabled](https://img.shields.io/badge/FOTA-Enabled-success)](https://en.wikipedia.org/wiki/Firmware_over-the-air)
[![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-informational)](https://www.freertos.org/)
[![AI Integration](https://img.shields.io/badge/AI-Lane%20Detection-ff69b4)](https://pytorch.org/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

Advanced embedded system implementing automotive-grade features with AI integration and wireless capabilities.

![System Overview](https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/Car.jpg)
![System Overview2](https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/Car2.jpg)

## Table of Contents 📖
- [Project Overview](#project-overview)
- [Key Features](#key-features-)
- [Hardware Architecture](#hardware-architecture-)
- [Software Architecture](#software-architecture-)
- [Installation & Setup](#installation--setup-)
- [FOTA Implementation](#fota-implementation-)
- [RTOS Integration](#rtos-integration-)
- [AI Model](#ai-model-)
- [System Applications](#system-applications-)
- [Testing & Validation](#testing--validation-)
- [Contributing](#contributing-)
- [License](#license-)
- [Acknowledgments](#acknowledgments-)

## Project Overview
**AutoNXT** revolutionizes automotive technology by integrating:
- Firmware Over-The-Air (FOTA) updates
- AI-powered Lane Keep Assistance
- Adaptive Cruise Control (ACC)
- Real-Time Operating System (RTOS)
- Emergency Safety Systems
- Smart Lighting Control

**Technologies Stack:**
- STM32F401CC (Cortex-M4)
- Raspberry Pi 3 B+
- FreeRTOS
- Python/OpenCV
- Firebase Realtime Database
- Fernet Cryptography

## Key Features ✨
### 🚀 Firmware Over-The-Air (FOTA)
- Dual-bank flash memory system
- AES-256 encrypted updates
- Firebase backend integration
- Critical update enforcement
### 🚗 Car
- Lane Keep Assistance with AI
- Adaptive Cruise Control
- Emergency Airbag System
- Bluetooth Remote Control
- Real-Time Operating System (RTOS)
- Adaptive Lighting System

### 🛣️ AI-Powered Lane Assistance
- Real-time video processing
- Custom CNN model (95% accuracy)
- SPI communication with ECU
- Dynamic steering adjustments

### ⚡ Adaptive Cruise Control
- Ultrasonic distance sensing
- PID speed control
- Collision prevention system
- Smooth acceleration/deceleration

### 🆘 Emergency Safety System
- FSR pressure detection
- Airbag deployment mechanism
- RTOS priority-based interrupt
- System-wide task suspension

## Hardware Architecture 🛠️
![Hardware Diagram](docs/assets/hardware_layout.png)

| Component               | Specification                         | Purpose                                 |
|-------------------------|---------------------------------------|-----------------------------------------|
| Microcontroller         | STM32F401CC (Cortex-M4)               | Main ECU                                |
| SBC                     | Raspberry Pi 3 B+                     | AI Processing & FOTA                    |
| Sensors                 | Ultrasonic, LDR, FSR, Camera Module   | Lane Detection, Distance Measurement    |
| Actuators               | DC Gear Motors, L298N Driver          | Motor Control                           |
| Communication           | HC-05 Bluetooth Module                |  Remote Control                         |

## Software Architecture 🖥️
```plaintext
Software Stack
├── RTOS Layer (FreeRTOS)
│   ├── Task Scheduler
│   ├── Priority Manager
│   └── Resource Allocator
├── Service Layer
│   ├── FOTA Manager
│   ├── AI Processor
│   └── Safety Monitor
└── Hardware Abstraction
    ├── STM32 Drivers
    └── RPi Peripherals
````

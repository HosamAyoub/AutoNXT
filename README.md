# AutoNXT - Next-Generation Vehicle Technology 🚗💻

[![FOTA Enabled](https://img.shields.io/badge/FOTA-Enabled-success)](https://en.wikipedia.org/wiki/Firmware_over-the-air)
[![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-informational)](https://www.freertos.org/)
[![AI Integration](https://img.shields.io/badge/AI-Lane%20Detection-ff69b4)](https://pytorch.org/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

Advanced embedded system implementing automotive-grade features with AI integration and wireless capabilities.

![System Overview](docs/assets/system_overview.png)

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

## Hardware Architecture 🧩
![Hardware Diagram](docs/assets/hardware_layout.png)

| Component               | Specification                          | Purpose                   |
|-------------------------|----------------------------------------|---------------------------|
| STM32F401CC             | 84MHz Cortex-M4, 256KB Flash           | Main ECU                  |
| Raspberry Pi 3 B+       | 1.4GHz Quad-core, 1GB RAM              | AI Processing & FOTA      |
| OV5647 Camera           | 8MP, 1080p30                           | Lane Detection            |
| HC-SR04 Ultrasonic      | 2cm-400cm range                        | Distance Measurement      |
| L298N Motor Driver      | 2A per channel                         | Motor Control             |
| HC-05 Bluetooth         | 4.0 BLE                                | Remote Control            |

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
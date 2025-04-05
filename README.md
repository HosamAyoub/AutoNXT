# AutoNXT - Next-Generation Vehicle Technology 🚗💻



Advanced embedded system implementing automotive-grade features with AI integration and wireless capabilities.

![System Overview](https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/Car.jpg)
*Figure 1: The car with all components in development phase*

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
- SPI communication with ECU
- Steering adjustments

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

| Component               | Specification                         | Purpose                               |
|-------------------------|---------------------------------------|---------------------------------------|
| Microcontroller         | STM32F401CC (Cortex-M4)               | Main ECU                              |
| SBC                     | Raspberry Pi 3 B+                     | AI Processing & FOTA                  |
| Sensors                 | Ultrasonic, LDR, FSR, Camera Module   | Lane Detection & Distance Measurement |
| Actuators               | DC Gear Motors, L298N Driver          | Motor Control                         |
| Communication           | HC-05 Bluetooth Module                | Remote Control                        |

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
├── Hardware Abstraction
│   ├── STM32 Drivers
│   └── RPi Peripherals
└── FOTA
.......... Add project architecture and doxygen documentation
```








# AutoNXT: Automotive Next-Generation Vehicle Technology 🚗💻
[![FOTA](https://img.shields.io/badge/FOTA-Update-success)](https://en.wikipedia.org/wiki/Firmware_over-the-air)
[![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-informational)](https://www.freertos.org/)
[![AI Integration](https://img.shields.io/badge/AI-Lane%20Detection-ff69b4)](https://pytorch.org/)
[![Doxygen Documentation](https://img.shields.io/badge/Doxygen-Documentation-cyan.svg)](https://github.com/HosamAyoub/AutoNXT/tree/main/Doxygen%20Documentation)

AutoNXT is an innovative graduation project that redefines automotive functionality by integrating advanced features such as Firmware Over-The-Air (FOTA) updates, real-time operating systems (RTOS), and intelligent safety systems. The project combines modern embedded hardware with cutting-edge software to deliver an enhanced driving experience.  



## Table of Contents 📖

- [Introduction](#introduction)
- [Project Overview](#project-overview)
- [Microcontrollers](#microcontrollers)
- [Firmware Over-The-Air (FOTA)](#firmware-over-the-air-fota)
- [Real-Time Operating System (RTOS)](#real-time-operating-system-rtos)
- [Hardware Components](#hardware-components)
- [Artificial Intelligence (AI) Model](#artificial-intelligence-ai-model)
- [System Applications](#system-applications)
- [Test Cases](#test-cases)
- [Conclusion](#conclusion)
- [License](#license)
- [Contact & Acknowledgements](#contact--acknowledgements)



## Introduction

In the realm of automotive technology, AutoNXT pushes the boundaries by integrating cutting-edge features that enhance both performance and safety. With a focus on user convenience and continuous improvement, the project employs FOTA updates, real-time processing, and intelligent control systems to transform the driving experience.  



## Project Overview

AutoNXT introduces a comprehensive platform that features ✨:

- **Wireless Firmware Updates (FOTA):** Seamlessly update vehicle firmware remotely.
- **Intelligent Safety Systems:** Adaptive Cruise Control, Lane Keep Assistance, and Automated Emergency Actions.
- **Advanced Embedded Systems:** Utilizing STM32F401CC microcontrollers and Raspberry Pi 3 B+.
- **Real-Time Operations:** Coordinated by an RTOS to ensure deterministic and reliable performance.


## Microcontrollers 

### STM32F401CC Microcontroller
- **Overview:**  
  Based on the ARM Cortex-M4, this microcontroller operates at up to 84 MHz and is well-suited for embedded applications.
- **Key Features:**  
  - Up to 256 Kbytes Flash memory  
  - Up to 64 Kbytes SRAM  
  - Multiple communication interfaces (UART, SPI, I2C)  
  - Extensive peripheral support including timers, ADC, and DMA  
- **Pinout Diagram:**  
  Provides a detailed layout for interfacing with various hardware components.

### Raspberry Pi 3 B+
- **Overview:**  
  A compact, affordable single-board computer used for higher-level processing.
- **Key Features:**  
  - 1.4 GHz quad-core ARM Cortex-A53 processor  
  - 1 GB RAM  
  - Multiple USB ports, HDMI output, and a 40-pin GPIO header  

*(Detailed information can be found in Chapter 2 of the document.)*  


## Firmware Over-The-Air (FOTA)

FOTA is central to the project, allowing for remote and seamless firmware updates:

- **Concept & Benefits:**  
  - Wireless updates eliminate the need for physical intervention.
  - Facilitates bug fixes, security patches, and feature enhancements.
- **Flashing Process:**  
  - Involves transferring a hex file to the microcontroller.
  - Uses techniques such as sector erasure and bootloader operations.
- **Bootloader Sequence:**  
  - Initiates at reset, checks for new firmware, validates data, and manages updates accordingly.
  
<figure>
<img src="https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/Bootloader%20Sequence.png" alt="FOTA Sequence" width="400px">
<figcaption>Fig.1: FOTA Sequence</figcaption>
</figure>
<figure>
<img src="https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/FOTA_Sequence.png" alt="Bootloader Sequence" width="400px">
<figcaption>Fig.2: Bootloader Sequence</figcaption>
</figure>

*(Refer to Chapter 3 for a detailed description.)*  


## Real-Time Operating System (RTOS)

An RTOS is employed to handle the critical timing and scheduling requirements of the project:

- **Purpose:**  
  - Provides deterministic scheduling and task management.
  - Ensures predictable response times for safety-critical applications.
- **Architecture:**  
  - Integrates into a layered software design.
  - Supports features such as multitasking and resource allocation.
- **Application in AutoNXT:**  
  - Enables concurrent operation of features like Adaptive Cruise Control, Lane Keep Assistance, and Automated Emergency Systems.

*(For more details, see Chapter 4.)*  


## Hardware Components

The project incorporates several key hardware elements:

- **Sensors & Modules:**  
  - **Lane Keep Assistance:** RPi Camera Module for capturing video.
  - **Adaptive Cruise Control:** Ultrasonic sensors for distance measurement.
  - **Adaptive Lighting System:** LDR sensor for ambient light detection.
  - **Airbag System:** Force-Sensitive Resistor (FSR) for impact detection.
- **Communication & Control:**  
  - Bluetooth modules (HC-05) for remote control.
  - DC motors with L298N driver for vehicle movement.
- **Schematics & PCB Layout:**  
  - Detailed wiring diagrams and PCB designs are provided.

| Component               | Specification                         | Purpose                                                         |
|-------------------------|---------------------------------------|-----------------------------------------------------------------|
| Microcontroller         | STM32F401CC (Cortex-M4)               | Main ECU                                                        |
| SBC                     | Raspberry Pi 3 B+                     | AI Processing & FOTA                                            |
| Sensors                 | Ultrasonic, LDR, FSR, Camera Module   | Lane Detection & Distance Measurement & ambient light detection |
| Actuators               | DC Gear Motors, L298N Driver          | Motor Control                                                   |
| Communication           | HC-05 Bluetooth Module                | Remote Control                                                  |

<figure>
<img src="https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/Car.jpg" alt="Hardware" width="400px">
<figcaption>Fig.3: Hardware</figcaption>
</figure>

*(Refer to Chapter 5 for complete hardware information.)*  


## Artificial Intelligence (AI) Model

AI is integrated into AutoNXT to enhance vehicle intelligence:

- **Functions:**  
  - Lane detection and assistance through image processing.
  - Object detection and real-time decision-making for improved safety.
- **Implementation:**  
  - Utilizes computer vision techniques with OpenCV and machine learning algorithms.
  - Calibrates using real-world driving data for continuous improvement.

<figure>
<img src="https://github.com/HosamAyoub/Photos/blob/main/AutoNXT/AI-Model.jpg" alt="AI Model" width="400px">
<figcaption>Fig.4: AI Model</figcaption>
</figure>

*(Detailed in Chapter 6.)*  


## System Applications

AutoNXT demonstrates practical applications across various systems:

- **Remote Control via Bluetooth:**  
  - Secure pairing and control using a user-friendly interface.
- **Adaptive Lighting Control:**  
  - Dynamically adjusts headlight intensity based on ambient conditions.
- **Adaptive Cruise Control:**  
  - Uses ultrasonic sensors to maintain safe following distances.
- **Automated Emergency System:**  
  - Activates safety measures like airbag deployment when needed.
- **Lane Keep Assistance:**  
  - Continuously monitors and corrects vehicle position.

*(Chapter 7 provides in-depth working theories and diagrams.)*  


## Test Cases

Extensive testing has been performed to validate system functionality:

- **Firmware Update Tests:**  
  - Validate FOTA process, hex file parsing, and bootloader sequence.
- **Sensor and Control Tests:**  
  - Ensure proper operation of FSR, ultrasonic sensors, and adaptive systems.
- **System Response:**  
  - Verify correct activation of emergency systems and adaptive controls.
- **Results:**  
  - Most test cases have passed, with iterative improvements ongoing for the AI-based lane detection.

*(For full test case details, see Chapter 8.)*  


## Conclusion

AutoNXT marks a significant advancement in automotive technology by merging modern hardware with sophisticated software solutions. The integration of FOTA, RTOS, and intelligent systems has created a platform that is both safe and innovative, setting a new standard in vehicle performance and user experience.  


## License

*This project is for academic purposes. Please refer to the project documentation or contact the project authors for detailed licensing information.*



## Contact & Acknowledgements

For further details or inquiries:

- **Submitted by:** Hossam Ayoub, Hesham Yasser, Dina Elsayed, Diaa Assem, Ziad Khaled, Seif El-Deen Ashraf  
- **Supervised by:** Eng. Joe Nofal, Eng. Nour Hassan  
- **Institution:** Information Technology Institute, Egypt Makes Electronics

Special thanks to all contributors and academic advisors who supported the project.  
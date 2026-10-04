# Smart Agricultural Soil-Moisture Multi-Node Gateway

## 1. Project Overview

The Smart Agricultural Soil-Moisture Multi-Node Gateway is a software-based agricultural monitoring system developed using C++ and Linux.

The system simulates multiple agricultural sensor nodes that collect soil moisture, temperature, humidity, and battery information. The sensor nodes transmit telemetry to a central gateway using TCP communication.

The gateway receives, validates, processes, monitors, and logs the telemetry data. It also generates alerts when abnormal agricultural conditions are detected.

The project additionally demonstrates Linux system programming and a Linux character device driver for sensor data interaction.

## 2. Problem Statement

Agricultural monitoring systems may contain multiple distributed sensor nodes that continuously collect environmental information.

A central gateway is required to:

- Receive telemetry from multiple sensor nodes
- Validate incoming sensor data
- Process soil-moisture conditions
- Detect abnormal conditions
- Monitor sensor-node health
- Maintain system logs
- Provide a Linux-based interface for sensor data

This project provides a software simulation of such a gateway without requiring physical sensor hardware.

## 3. Objectives

The main objectives are:

- Simulate multiple agricultural sensor nodes
- Implement TCP client-server communication
- Support multiple sensor nodes
- Validate sensor telemetry
- Process soil-moisture conditions
- Determine whether irrigation is required
- Generate alerts
- Monitor node health
- Maintain gateway logs
- Demonstrate Linux system programming
- Demonstrate inter-process communication
- Implement a Linux character device driver
- Provide user-space interaction with the driver
- Apply C++ object-oriented programming and STL
- Demonstrate multithreaded processing
- Provide automated integration testing

## 4. System Architecture

```text
Virtual Sensor Nodes
        |
        | TCP
        v
+-------------------------+
|     CENTRAL GATEWAY     |
+-------------------------+
        |
        +-- Communication Manager
        |
        +-- Telemetry Validator
        |
        +-- Telemetry Processor
        |
        +-- Alert Engine
        |
        +-- Node Health Monitor
        |
        +-- Logger
        |
        v
   Linux Interface
        |
        v
/dev/agri_sensor
        |
        v
Linux Character Device Driver   
## 5. Main Components

### Virtual Sensor Nodes

The system simulates multiple agricultural sensor nodes.

Each node generates:

- Soil moisture
- Temperature
- Humidity
- Battery level
- Node status
- Timestamp

### TCP Communication

Sensor nodes communicate with the central gateway using TCP sockets.

The gateway listens on port 5000 and accepts telemetry from multiple sensor nodes.

### Telemetry Validator

The validator checks incoming sensor data before processing.

It validates:

- Node ID
- Soil moisture range
- Temperature range
- Humidity range
- Battery level

### Telemetry Processor

The processor analyzes validated telemetry and determines:

- Moisture classification
- Irrigation requirement
- Sensor operating condition

### Alert Engine

The alert engine detects abnormal conditions.

Current alerts include:

- LOW_MOISTURE
- LOW_BATTERY
- HIGH_TEMPERATURE

### Node Health Monitor

Tracks activity from sensor nodes and reports their health status.

### Logger

Records gateway activity and telemetry events in:

logs/gateway.log

### Linux Character Device Driver

The project includes a Linux character device:

/dev/agri_sensor

The driver supports reading and writing sensor data from user space.

## 6. Multi-Node Operation

The project currently simulates three sensor nodes:

NODE_01
NODE_02
NODE_03

Each node generates telemetry and sends it to the central gateway.

The integration test verifies successful telemetry reception from all three nodes.

## 7. Example Telemetry

Example telemetry:

NODE_01|soil_moisture=46.17|temperature=30.08|humidity=47.01|battery=94.45|status=NORMAL

Example processed result:

Node=NODE_01
Moisture=46.17%
MoistureStatus=OPTIMAL
Temperature=30.08C
Humidity=47.01%
Battery=94.45%
Irrigation=NOT_REQUIRED

## 8. Alert Conditions

| Condition | Alert |
|---|---|
| Soil moisture < 30% | LOW_MOISTURE |
| Battery < 30% | LOW_BATTERY |
| Temperature > 40C | HIGH_TEMPERATURE |

## 9. Linux System Programming

The project demonstrates:

- Process creation using fork()
- Process execution using exec()
- Process synchronization using waitpid()
- Pipes
- Shared memory
- POSIX semaphores
- POSIX message queues
- Signals
- File descriptors
- Memory mapping using mmap()
- File locking
- Asynchronous I/O
- Process monitoring
- Linux character device interaction

Linux process-management commands demonstrated include:

ps
top
kill
nice
renice

## 10. Linux Character Device Driver

The project contains a custom Linux character device driver.

Device:

/dev/agri_sensor

The driver demonstrates:

- Kernel module loading
- Character-device registration
- Device creation
- open()
- read()
- write()
- Device cleanup
- User-space interaction

The driver was successfully tested using a C++ user-space test program.

## 11. C++ Concepts Used

The project uses:

- Classes and objects
- Encapsulation
- Constructors and destructors
- STL containers
- std::vector
- std::string
- std::unordered_map
- Threads
- Mutexes
- RAII
- File I/O
- Socket programming
- Modular source/header organization
- C++17

## 12. Multithreading

The TCP gateway uses separate threads for client connections.

This allows telemetry from multiple sensor nodes to be processed concurrently.

## 13. Testing

Testing covers:

- Sensor simulation
- Telemetry validation
- Telemetry processing
- Alert generation
- Node health monitoring
- TCP communication
- Multi-node integration
- Linux process management
- Pipe IPC
- Shared memory IPC
- Semaphore IPC
- Message queue IPC
- Signal handling
- File descriptors
- Memory mapping
- File locking
- Asynchronous I/O
- Character device driver

## 14. Multi-Node Integration Test

Run:

bash tests/integration_test.sh

Expected result:

INTEGRATION TEST PASSED

NODE_01 telemetry received: PASS
NODE_02 telemetry received: PASS
NODE_03 telemetry received: PASS
Multi-node telemetry reception: PASS

## 15. Build

Build the project using:

make

The gateway executable is:

bin/smart_gateway

Run:

./bin/smart_gateway

## 16. Project Structure

SmartAgriculture-Gateway/
├── config/
├── docs/
│   ├── PRD.md
│   ├── architecture.md
│   └── uml/
├── driver/
├── include/
├── src/
├── tests/
├── logs/
├── Makefile
├── README.md
└── .gitignore

## 17. Technology Stack

Programming:
- C++
- C
- Bash

Operating System:
- Ubuntu Linux

System Programming:
- POSIX APIs
- Linux system calls
- TCP sockets
- IPC
- Linux kernel modules
- Character devices

Development Tools:
- GCC / G++
- Make
- Git
- GDB
- Oracle VirtualBox

## 18. Software-Only Hardware Simulation

The project does not require physical agricultural hardware.

Sensor nodes are software simulations representing agricultural sensor devices.

The Linux character device driver provides a software representation of the hardware/software interface.

## 19. Project Scope

Included:

- Multi-node sensor simulation
- TCP networking
- Gateway processing
- Telemetry validation
- Alert generation
- Node monitoring
- Logging
- Multithreading
- Linux system programming
- IPC
- Character device driver
- Automated testing
- UML documentation
- Architecture documentation

Future enhancements:

- UDP communication
- MQTT integration
- Database storage
- Web dashboard
- Docker deployment
- Kubernetes deployment
- Real agricultural sensors
- Cloud monitoring
- Advanced analytics

## 20. Expected Outcome

The system demonstrates how a Linux-based gateway can receive and process telemetry from multiple distributed agricultural sensor nodes.

The project combines:

- Computer Architecture
- Computer Networking
- Linux
- C++
- Linux System Programming
- Device Drivers
- Software Architecture
- SDLC
- UML
- Testing
- Git

## 21. Project Status

The core gateway system is implemented and tested.

Major working features include:

- Multi-node telemetry
- TCP communication
- Multithreaded gateway
- Telemetry validation
- Telemetry processing
- Alert generation
- Node health monitoring
- Logging
- Linux IPC
- Character device driver
- Unit testing
- Multi-node integration testing
- UML documentation
- Architecture documentation

## 22. Author

Developed as part of the Wipro Embedded Track training and capstone project.

Project: Smart Agricultural Soil-Moisture Multi-Node Gateway 

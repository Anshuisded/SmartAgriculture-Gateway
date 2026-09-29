# Product Requirements Document (PRD)

## 1. Project Title

Smart Agricultural Soil-Moisture Multi-Node Gateway

---

## 2. Project Overview

The Smart Agricultural Soil-Moisture Multi-Node Gateway is a software-based agricultural monitoring system that simulates multiple field sensor nodes and communicates their telemetry to a central gateway.

The system is designed to demonstrate C++, Linux, computer networking, Linux system programming, software architecture, and embedded-system concepts without requiring physical sensor hardware.

Virtual sensor nodes generate agricultural telemetry such as soil moisture, temperature, humidity, and battery level. The central gateway receives the data, validates it, processes the readings, monitors node health, generates alerts, and stores system logs.

A Linux character-device driver component will be developed to demonstrate interaction between user-space software and the Linux kernel.

---

## 3. Problem Statement

Agricultural fields can contain multiple sensing locations where soil and environmental conditions need to be monitored.

A monitoring system must be able to:

- Receive data from multiple sensor nodes.
- Validate incoming telemetry.
- Detect abnormal soil-moisture conditions.
- Monitor the availability and health of sensor nodes.
- Generate alerts when configurable conditions are detected.
- Maintain logs for later analysis.
- Handle concurrent communication from multiple nodes.

This project provides a software simulation of such a system.

---

## 4. Objectives

The primary objectives are:

1. Develop a multi-node agricultural sensor simulation.
2. Implement network communication between sensor nodes and a central gateway.
3. Build the gateway using C++ and Linux.
4. Process and validate incoming telemetry.
5. Implement soil-moisture based alert detection.
6. Monitor sensor-node health and connectivity.
7. Implement persistent logging.
8. Demonstrate Linux system-programming concepts.
9. Develop a Linux character-device driver component.
10. Apply object-oriented programming, STL, multithreading, synchronization, RAII, and exception handling.
11. Use Git for version control and project tracking.
12. Document the system using software architecture and UML diagrams.

---

## 5. Scope

### 5.1 In Scope

- Software-based virtual sensor nodes.
- Multiple concurrent sensor connections.
- TCP-based communication.
- Telemetry validation.
- Soil-moisture processing.
- Configurable alert thresholds.
- Node health monitoring.
- Event and telemetry logging.
- Graceful gateway shutdown.
- Multithreaded gateway processing.
- Linux system calls and POSIX APIs where appropriate.
- Linux character-device driver demonstration.
- C++ object-oriented architecture.
- Unit and integration testing.
- UML and architecture documentation.
- Git-based version control.

### 5.2 Out of Scope

- Physical soil sensors.
- Arduino or ESP32 hardware.
- Real agricultural field deployment.
- Direct control of irrigation equipment.
- Real-world crop prediction.
- Production-grade cloud deployment.
- Hardware-specific GPIO, I2C, or SPI integration.

---

## 6. System Actors

### Virtual Sensor Node

A software process that simulates an agricultural sensor node.

Responsibilities:

- Generate telemetry.
- Identify itself using a node ID.
- Establish communication with the gateway.
- Periodically transmit sensor readings.
- Simulate abnormal and normal readings.

### Central Gateway

The main processing system.

Responsibilities:

- Accept connections from sensor nodes.
- Receive telemetry.
- Validate incoming data.
- Process sensor readings.
- Monitor node health.
- Generate alerts.
- Maintain logs.
- Handle graceful shutdown.

### System Administrator

The user who starts, configures, monitors, and stops the gateway.

---

## 7. Functional Requirements

### FR-01: Sensor Node Simulation

The system shall provide software-based sensor nodes capable of generating simulated agricultural telemetry.

### FR-02: Node Identification

Each virtual sensor node shall have a unique node identifier.

### FR-03: Network Communication

Sensor nodes shall communicate telemetry to the central gateway over a network connection.

### FR-04: Concurrent Connections

The gateway shall support communication from multiple sensor nodes concurrently.

### FR-05: Telemetry Validation

The gateway shall validate received telemetry before processing it.

### FR-06: Soil-Moisture Processing

The gateway shall process soil-moisture readings received from sensor nodes.

### FR-07: Configurable Thresholds

Soil-moisture alert thresholds shall be configurable rather than hard-coded into the processing logic.

### FR-08: Alert Generation

The gateway shall generate an alert when a configured soil-moisture condition is detected.

### FR-09: Node Health Monitoring

The gateway shall track sensor-node connectivity and identify nodes that stop communicating.

### FR-10: Logging

The system shall record important telemetry, events, errors, and alerts in log files.

### FR-11: Graceful Shutdown

The gateway shall support controlled shutdown and cleanup of active resources.

### FR-12: Driver Interaction

The project shall include a Linux character-device driver component demonstrating controlled user-space interaction with the Linux kernel.

### FR-13: Configuration

System configuration such as network parameters and alert thresholds shall be maintained separately from application source code.

---

## 8. Non-Functional Requirements

### NFR-01: Reliability

The gateway should continue operating when an individual sensor node disconnects unexpectedly.

### NFR-02: Maintainability

The system shall use modular C++ components with clearly defined responsibilities.

### NFR-03: Performance

The gateway should process telemetry from multiple nodes without unnecessary blocking.

### NFR-04: Concurrency Safety

Shared resources shall be protected using appropriate synchronization mechanisms.

### NFR-05: Portability

The application shall target a Linux environment and use standard C++ and POSIX interfaces where practical.

### NFR-06: Security

The system shall validate network input and avoid blindly trusting malformed telemetry.

### NFR-07: Observability

Important system events, errors, node activity, and alerts shall be logged.

### NFR-08: Code Quality

The implementation shall follow consistent naming, modular design, RAII, exception handling, and appropriate C++/STL practices.

---

## 9. Major System Modules

The planned modules are:

1. Sensor Simulator
2. Communication Manager
3. Gateway Manager
4. Telemetry Processor
5. Data Validator
6. Alert Manager
7. Node Health Monitor
8. Logger
9. Configuration Manager
10. Linux Character Device Driver
11. Test Suite

---

## 10. Example Telemetry

A sensor node may periodically transmit information containing:

- Node ID
- Timestamp
- Soil moisture percentage
- Temperature
- Humidity
- Battery level
- Node status

The exact wire format will be finalized during system design.

---

## 11. High-Level Data Flow

Virtual Sensor Nodes
        |
        | Network Telemetry
        v
Central Gateway
        |
        +--> Data Validation
        |
        +--> Telemetry Processing
        |
        +--> Node Health Monitoring
        |
        +--> Alert Manager
        |
        +--> Logger
        |
        v
System Logs / Monitoring Data

Linux Character Device Driver
        ^
        |
User-Space Gateway Component

---

## 12. Technology Stack

### Programming

- C++

### Operating System

- Ubuntu Linux

### System Programming

- POSIX APIs
- Linux system calls
- Linux file descriptors
- Linux sockets
- Linux process/thread mechanisms

### Networking

- TCP/IP
- Socket programming

### Version Control

- Git
- GitHub

### Build Tools

- g++
- Make

### Testing

- C++ unit tests
- Integration testing
- System testing

### Documentation

- Markdown
- UML diagrams

---

## 13. Expected Outcomes

At the completion of the project, the system should provide:

1. A working multi-node sensor simulation.
2. A working C++ gateway.
3. Concurrent network communication.
4. Telemetry validation and processing.
5. Configurable soil-moisture alerts.
6. Node health monitoring.
7. Persistent system logging.
8. A working Linux character-device driver demonstration.
9. Automated or repeatable tests for major components.
10. Complete architecture and UML documentation.
11. A GitHub repository containing the source code and documentation.

---

## 14. Constraints

- The project is software-only.
- No physical sensor hardware is required.
- Development will be performed in a Linux virtual machine.
- The project must be completed within the available training/project timeline.
- Hardware-specific functionality will be simulated where physical hardware is unavailable.

---

## 15. Future Enhancements

Possible future improvements include:

- Real sensor hardware integration.
- MQTT-based IoT communication.
- Web-based monitoring dashboard.
- Database-backed telemetry storage.
- Cloud deployment.
- Authentication and encrypted communication.
- Predictive irrigation recommendations.
- Integration with GPIO/I2C/SPI hardware.
- Containerized deployment.

---

## 16. Project Success Criteria

The project will be considered successful when:

- Multiple virtual nodes can communicate with the gateway.
- The gateway can process concurrent telemetry.
- Invalid telemetry is rejected safely.
- Soil-moisture conditions can trigger configurable alerts.
- Node failures/disconnections can be detected.
- System events are logged.
- The Linux driver can be loaded and interacted with from user space.
- The complete system can be built and executed on Ubuntu.
- Tests demonstrate the major system components.
- Source code, architecture, UML, testing evidence, and project documentation are available in the Git repository.


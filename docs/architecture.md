# System Architecture

## 1. Architecture Overview

The Smart Agricultural Soil-Moisture Multi-Node Gateway follows a layered, modular architecture.

The system consists of software-based virtual sensor nodes, a central C++ gateway, Linux system interfaces, and a Linux character-device driver.

The architecture is designed to support concurrent sensor communication, telemetry processing, node health monitoring, alert generation, and logging.

---

## 2. High-Level Architecture

```text
+-----------------------+
| Virtual Sensor Node 1 |
+-----------+-----------+
            |
            | TCP
            |
+-----------v-----------+
| Virtual Sensor Node 2 |
+-----------+-----------+
            |
            | TCP
            |
+-----------v-----------+
| Virtual Sensor Node N |
+-----------+-----------+
            |
            v
+----------------------------------+
|          CENTRAL GATEWAY         |
|                                  |
|  +----------------------------+  |
|  | Communication Manager      |  |
|  +-------------+--------------+  |
|                |                 |
|                v                 |
|  +----------------------------+  |
|  | Telemetry Validator        |  |
|  +-------------+--------------+  |
|                |                 |
|                v                 |
|  +----------------------------+  |
|  | Telemetry Processor        |  |
|  +------+------+------+--------+  |
|         |      |      |           |
|         v      v      v           |
|      Alert   Health  Logger       |
|      Engine  Monitor              |
+----------------------------------+
                 |
                 v
        +-------------------+
        | Linux Interface   |
        +---------+---------+
                  |
                  v
        +-------------------+
        | Character Device  |
        | Driver            |
        | /dev/agri_sensor  |
        +-------------------+

---

## 3. Major Components

### 3.1 Virtual Sensor Node

The Virtual Sensor Node simulates an agricultural sensing device.

Responsibilities:

- Generate sensor readings.
- Maintain a unique node ID.
- Connect to the gateway.
- Periodically transmit telemetry.
- Simulate normal and abnormal conditions.
- Detect connection failures.

Example telemetry:

- Node ID
- Timestamp
- Soil moisture
- Temperature
- Humidity
- Battery level
- Node status

---

### 3.2 Communication Manager

The Communication Manager handles network communication between sensor nodes and the gateway.

Responsibilities:

- Create server sockets.
- Bind the gateway to a configured address and port.
- Listen for incoming connections.
- Accept sensor-node connections.
- Receive telemetry.
- Handle connection failures.
- Manage concurrent connections.

The initial implementation will use TCP/IP.

---

### 3.3 Telemetry Validator

The Telemetry Validator verifies incoming sensor data before processing.

Validation includes:

- Required fields are present.
- Node ID is valid.
- Numeric values are within acceptable ranges.
- Message format is valid.
- Malformed input is rejected safely.

---

### 3.4 Telemetry Processor

The Telemetry Processor converts validated telemetry into application-level information.

Responsibilities:

- Process soil-moisture readings.
- Process environmental readings.
- Update node information.
- Forward relevant events to other components.

---

### 3.5 Alert Engine

The Alert Engine evaluates telemetry against configurable thresholds.

Possible states include:

- Normal
- Low moisture
- Critical moisture

The thresholds will be configurable and will not be hard-coded into the processing logic.

---

### 3.6 Node Health Monitor

The Node Health Monitor tracks the communication status of sensor nodes.

It will maintain information such as:

- Last communication time.
- Connection state.
- Node availability.
- Number of received messages.
- Connection failures.

A node that stops communicating for a configured period may be marked as unavailable.

---

### 3.7 Logger

The Logger records important system events.

Examples include:

- Gateway startup.
- Gateway shutdown.
- Sensor connection.
- Sensor disconnection.
- Received telemetry.
- Invalid telemetry.
- Moisture alerts.
- System errors.

Logs will be written to files under the `logs/` directory.

---

### 3.8 Configuration Manager

The Configuration Manager provides centralized configuration for the application.

Configuration may include:

- Gateway IP address.
- TCP port.
- Sensor transmission interval.
- Soil-moisture thresholds.
- Node timeout.
- Logging configuration.

Configuration will be kept outside the main application source code.

---

### 3.9 Linux Character Device Driver

A small Linux character-device driver will demonstrate interaction between user-space software and the Linux kernel.

Conceptually:

```text
+-----------------------------+
| User-Space C++ Application  |
+--------------+--------------+
               |
               | read/write
               v
+-----------------------------+
| /dev/agri_sensor            |
+--------------+--------------+
               |
               v
+-----------------------------+
| Linux Character Driver      |
+--------------+--------------+
               |
               v
+-----------------------------+
| Linux Kernel                |
+-----------------------------+

## 4. Data Flow

The primary data flow is:

```text
Sensor Generation
       |
       v
TCP Transmission
       |
       v
Gateway Reception
       |
       v
Telemetry Validation
       |
       v
Telemetry Processing
       |
       +----------------+
       |                |
       v                v
Alert Evaluation    Health Update
       |                |
       +-------+--------+
               |
               v
             Logger

## 5. Concurrency Model

The gateway must support multiple sensor nodes simultaneously.

The planned design will use C++ multithreading.

A simplified model is:

```text
                Gateway
                   |
          Accept Connections
                   |
       +-----------+-----------+
       |           |           |
       v           v           v
    Thread 1    Thread 2    Thread N
       |           |           |
    Node 1       Node 2      Node N
       |           |           |
       +-----------+-----------+
                   |
                   v
        Shared Gateway State
                   |
              Mutex / Lock
## 6. Data Structures

The project will use appropriate C++ STL data structures.

Planned examples include:

- `std::unordered_map` for active nodes.
- `std::queue` for telemetry processing where required.
- `std::vector` for collections of telemetry data.
- `std::string` for identifiers and messages.
- `std::mutex` for synchronization.
- Smart pointers where dynamic ownership is required.

Data structures will be selected based on actual application requirements rather than being included artificially.

---

## 7. Software Design Principles

The implementation will follow:

- Encapsulation.
- Single Responsibility Principle.
- Separation of concerns.
- RAII.
- DRY.
- KISS.
- Modular design.

Where appropriate, design patterns may be used to simplify communication between components.

---

## 8. Hardware-Software Boundary

Although the project does not require physical hardware, the architecture demonstrates the boundary between software and hardware-oriented components.

The virtual sensor nodes represent the sensing layer.

The Linux character-device driver represents the kernel/device interface.

The C++ gateway represents the application-level processing layer.

```text
Application Layer
       |
       v
C++ Gateway
       |
       v
Linux System Interface
       |
       v
Character Device Driver
       |
       v
Linux Kernel
       |
       v
Simulated / Future Hardware


## 6. Data Structures

The project will use appropriate C++ STL data structures.

Planned examples include:

- `std::unordered_map` for active nodes.
- `std::queue` for telemetry processing where required.
- `std::vector` for collections of telemetry data.
- `std::string` for identifiers and messages.
- `std::mutex` for synchronization.
- Smart pointers where dynamic ownership is required.

Data structures will be selected based on actual application requirements rather than being included artificially.

---

## 7. Software Design Principles

The implementation will follow:

- Encapsulation.
- Single Responsibility Principle.
- Separation of concerns.
- RAII.
- DRY.
- KISS.
- Modular design.

Where appropriate, design patterns may be used to simplify communication between components.

---

## 8. Hardware-Software Boundary

Although the project does not require physical hardware, the architecture demonstrates the boundary between software and hardware-oriented components.

The virtual sensor nodes represent the sensing layer.

The Linux character-device driver represents the kernel/device interface.

The C++ gateway represents the application-level processing layer.

```text
Application Layer
       |
       v
C++ Gateway
       |
       v
Linux System Interface
       |
       v
Character Device Driver
       |
       v
Linux Kernel
       |
       v
Simulated / Future Hardware

## 6. Data Structures

The project will use appropriate C++ STL data structures.

Planned examples include:

- `std::unordered_map` for active nodes.
- `std::queue` for telemetry processing where required.
- `std::vector` for collections of telemetry data.
- `std::string` for identifiers and messages.
- `std::mutex` for synchronization.
- Smart pointers where dynamic ownership is required.

Data structures will be selected based on actual application requirements rather than being included artificially.

---

## 7. Software Design Principles

The implementation will follow:

- Encapsulation.
- Single Responsibility Principle.
- Separation of concerns.
- RAII.
- DRY.
- KISS.
- Modular design.

Where appropriate, design patterns may be used to simplify communication between components.

---

## 8. Hardware-Software Boundary

Although the project does not require physical hardware, the architecture demonstrates the boundary between software and hardware-oriented components.

The virtual sensor nodes represent the sensing layer.

The Linux character-device driver represents the kernel/device interface.

The C++ gateway represents the application-level processing layer.

```text
Application Layer
       |
       v
C++ Gateway
       |
       v
Linux System Interface
       |
       v
Character Device Driver
       |
       v
Linux Kernel
       |
       v
Simulated / Future Hardware

## 9. Network Architecture

The initial communication model is TCP client-server.

```text
+------------------+       TCP        +------------------+
| Virtual Sensor 1 | ---------------> |                  |
+------------------+                  |                  |
                                      |                  |
+------------------+       TCP        |     Gateway      |
| Virtual Sensor 2 | ---------------> |   TCP Server     |
+------------------+                  |                  |
                                      |                  |
+------------------+       TCP        |                  |
| Virtual Sensor N | ---------------> |                  |
+------------------+                  +------------------+

---

## 10. Error Handling

The system shall handle:

- Invalid telemetry.
- Network disconnections.
- Socket errors.
- Configuration errors.
- File I/O errors.
- Driver communication errors.
- Thread synchronization problems.

Errors will be logged where appropriate and the system should avoid terminating the entire gateway because of a single sensor-node failure.

---

## 11. Graceful Shutdown

The gateway will support controlled shutdown.

The shutdown process will:

1. Stop accepting new connections.
2. Signal active workers to stop.
3. Close network sockets.
4. Flush important logs.
5. Release synchronization resources.
6. Close files and descriptors.
7. Exit cleanly.

Linux signals may be used to initiate graceful shutdown.

---

## 12. Deployment Environment

Development and execution environment:

- Ubuntu Linux
- Oracle VirtualBox
- C++
- g++
- GNU Make
- Git
- Linux kernel interfaces
- POSIX APIs

The project will be developed and tested inside the Ubuntu virtual machine.

---

## 13. Future Architecture Extensions

Potential future extensions include:

- UDP communication.
- MQTT communication.
- Database-backed storage.
- Web monitoring dashboard.
- Docker containerization.
- Cloud deployment.
- Authentication and TLS.
- Physical sensor integration.
- GPIO/I2C/SPI device integration.

# Smart Factory IoT Monitoring System

## Project Overview

This project is an IoT-based Smart Factory Monitoring System developed using Arduino, PicsimLab, MQTT, and ThingsBoard Cloud.

The system monitors industrial conditions in real time and supports automation, alarms, and remote device control using cloud dashboards.

It consists of two nodes:

### Node 1 – Production Line
- Temperature and Humidity Monitoring
- Machine Temperature (LM35)
- Vibration Monitoring
- Machine ON/OFF Status
- Relay and LED Status
- High Temperature Alarm Detection

### Node 2 – Warehouse
- Temperature and Humidity Monitoring
- LDR Light Detection
- PIR Motion Detection
- Door Status Monitoring
- Automatic Ventilation using Relay
- RPC-based Remote Relay Control

---

## Tools and Technologies Used

- Arduino Uno
- Arduino IDE
- PicsimLab
- ThingsBoard Cloud
- MQTT Protocol
- DHT22 Sensor
- LM35 Sensor
- LDR Sensor
- PIR Sensor
- Door Switch
- Relay Module
- LEDs
- Ethernet Communication

---

## Features

- Real-time sensor monitoring
- Cloud dashboard visualization
- MQTT-based data communication
- Automatic ventilation control
- RPC-based remote relay control
- Alarm monitoring
- Auto reconnect on MQTT disconnection
- LED status indication
- Security monitoring using PIR and Door Sensor

---

## Dashboard Features

- Live Gauges for Temperature and Humidity
- Time Series Charts for Sensor Trends
- LED Indicators for Machine, Motion, Door, and Relay Status
- Alarm Table for Critical Conditions
- Latest Telemetry Values Display
- RPC Switch for Relay Control

### Relay Control Conditions

- If humidity is **85% or more**, ventilation relay turns ON automatically
- Relay can be turned OFF when humidity becomes normal
- Operators can also manually control relay using ThingsBoard RPC switch

### Alarm Conditions

- High Temperature Alert
- High Humidity Alert
- Low Light Detection
- Motion Detection Alert
- Sensor Failure Warning
- MQTT Disconnection Warning

---

## Platform Used

### PicsimLab

Used to simulate sensors, relays, LEDs, and Ethernet communication without physical hardware.

### ThingsBoard Cloud

Used for real-time dashboards, telemetry visualization, alarms, and remote device control using RPC.

---

## Project Outcome

This project demonstrates how IoT improves industrial monitoring, automation, safety, and efficiency in smart factory environments through real-time monitoring and cloud-based control.

# Smart Factory IoT Monitoring System

## Project Overview
This project is an IoT-based Smart Factory Monitoring System developed using Arduino simulation, PicsimLab, MQTT, and ThingsBoard Cloud.

The system monitors industrial environmental and operational conditions in real time and supports automation and remote device control.

It consists of two nodes:

### Node 1 – Production Line
- Temperature and Humidity Monitoring
- Machine Temperature Monitoring (LM35)
- Vibration Monitoring
- Machine ON/OFF Status
- Relay and LED Status Monitoring

### Node 2 – Warehouse
- Temperature and Humidity Monitoring
- Light Detection using LDR
- Motion Detection using PIR Sensor
- Door Status Monitoring
- Automatic Ventilation using Relay Control

---

## Tools and Technologies Used

- Arduino Uno
- Arduino IDE
- PicsimLab
- ThingsBoard Cloud
- MQTT Protocol
- DHT22 Sensor
- LDR Sensor
- PIR Motion Sensor
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
- Alarm monitoring and status indication

---

## Platform Used

### PicsimLab
Used to simulate sensors, relays, LEDs, and Ethernet communication without physical hardware.

### ThingsBoard Cloud
Used for real-time dashboards, telemetry visualization, alarms, and remote device control using RPC.

---

## Project Outcome

This project demonstrates how IoT can improve industrial monitoring, automation, safety, and efficiency in smart factory environments.

# IoT Smart Aquarium System

## Overview
The **IoT Smart Aquarium System** is a simple yet innovative project that utilizes IoT technology to automate and enhance the maintenance of a home aquarium. This system leverages the **NodeMCU ESP8266** microcontroller and various sensors to monitor and regulate the aquarium environment. 

The project is designed to:
- Stabilize water temperature using a **DS18B20 Temperature Sensor** combined with an aquarium heater.
- Monitor water depth using an **Ultrasonic Sensor**, ensuring proper water volume for aquatic life.

By integrating IoT technologies, this project provides a smart solution for aquarium enthusiasts to maintain a healthy aquatic ecosystem.

---

## System Summary
The **Internet of Things (IoT)** enables everyday objects to connect to the internet, exchange data, and perform automated tasks. This project demonstrates the practical application of IoT in the form of a **Smart Aquarium System**. 

### Features:
1. **Temperature Regulation**:
   - Uses the **DS18B20 Temperature Sensor** to monitor water temperature.
   - Activates the **Aquarium Heater** via a relay to maintain a stable temperature.
   - Helps reduce the growth of fungi and bacteria by maintaining optimal water conditions.

2. **Water Depth Monitoring**:
   - Utilizes an **Ultrasonic Sensor** to measure water depth.
   - Alerts users if the water level drops below the desired level to ensure proper volume.

3. **Real-Time Monitoring and Control**:
   - Data is sent to **Firebase** for cloud storage and remote monitoring.
   - Users can view and control the system via an interface built using **Red Node**.

---

## Technology Stack

### Hardware:
- **NodeMCU ESP8266**: Microcontroller for IoT functionalities.
- **DS18B20 Temperature Sensor**: For water temperature monitoring.
- **Ultrasonic Sensor**: For water depth measurement.
- **Aquarium Heater**: Maintains stable water temperature.
- **Relay**: Controls the heater.
- **Jumper Wires**: Connects components.
- **Mini Aquarium**: Test environment for the system.

### Software:
- **Arduino IDE**: For programming the NodeMCU.
- **Red Node**: Provides a graphical interface for system monitoring and control.
- **Firebase**: Cloud platform for data storage and real-time updates.

---

## How to Use

### Hardware Setup:
1. Connect the **DS18B20 Temperature Sensor** and **Ultrasonic Sensor** to the **NodeMCU ESP8266**.
2. Wire the **Aquarium Heater** to a relay and connect it to the NodeMCU for temperature control.
3. Place the sensors and heater into the mini aquarium.

### Software Setup:
1. Install the **Arduino IDE** and set up the NodeMCU with the required libraries.
2. Program the NodeMCU with the provided source code in the repository.
3. Use **Firebase** to store and retrieve data from the sensors.
4. Set up **Red Node** to create a user interface for monitoring and controlling the system.

### Running the System:
1. Power on the NodeMCU and ensure all components are connected.
2. Open the **Red Node** interface to view real-time data and adjust settings.
3. Monitor temperature and water depth data on the dashboard, and make adjustments as needed.

---

## Tools/Dependencies
- **Arduino IDE**: [Download here](https://www.arduino.cc/en/software)
- **Firebase**: [Firebase Console](https://console.firebase.google.com/)
- **Red Node**: [Node-RED](https://nodered.org/)

---

## Future Improvements
- **pH Sensor Integration**: Add a sensor to monitor water acidity levels.
- **Automatic Water Pump**: Automate water refilling when the level drops below a threshold.
- **Mobile App**: Develop a companion app for easier control and notifications.


---

Feel free to contribute by submitting issues or pull requests to improve the system!

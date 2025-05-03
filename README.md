MAPS: Mechatronic Autonomous Pilot System

An autonomous, touchless-activated, path-following robot that integrates line tracking, obstacle detection, and finish-line recognition. Designed for educational use and rapid prototyping with low-cost components and modular embedded control.

🚀 Project Overview

MAPS is a mobile autonomous robot designed to:
Follow a black tape line on a white background
Detect and avoid obstacles using an ultrasonic sensor
Stop at a designated finish line
Start via a touchless activation (hand wave)
Built using Arduino Uno, IR sensors, and Ultrasonic sensing, this project integrates hardware and software into a lightweight, reliable, and low-cost system.
🔧 Hardware Components

Arduino Uno R3
L298N Motor Driver
TT DC Gearbox Motors
KY-033 IR Line Sensors (x2)
HC-SR04 Ultrasonic Sensor
9V Battery
3D-Printed PLA Chassis
Rubber Wheels
💸 Total Cost: ~$30.83 USD

🧠 Features

Feature	Description
Line Following	Dual IR sensors follow a 2cm-wide black line
Obstacle Avoidance	Ultrasonic sensor halts robot if object <10 cm, resumes when clear
Finish Line Detection	Recognizes 4cm-width end line to stop
Touchless Start	Wave in front of ultrasonic sensor to start operation
High Accuracy	>90% success in line detection and obstacle response under indoor lighting
Portable Design	Lightweight chassis, single-hand carry, approx. 7.0 in. long

🧩 Code Logic (Simplified State Machine)

Remote Start – Waits for ultrasonic trigger (hand wave)
Line Following – Continuously tracks tape using IR sensors
Obstacle Detection – Stops motion if object <10cm; resumes once cleared
Finish Line Detection – Stops robot when finish tape detected
A full technical flowchart is provided in Figure G1 of the project presentation.

📏 Design Specifications

Metric	Value
Avg. Line Deviation	~0.5–1 cm
Steering Overshoot	<10° on 135° turns
Obstacle Detection Range	10 cm (Ultrasonic)
Control Loop Frequency	10–20 Hz
Reaction Time	<250 ms
Detection Accuracy (Finish Line)	9/10 trials
Robot Weight	~0.5 lb

📐 CAD and Circuit Diagrams

3D-Printed Chassis: Compact and component-integrated design
Circuit Schematic: Displays sensor-controller-actuator wiring
Glass Box Diagram: Shows energy & information flow in system

# **[CS427 - Internet of Things] ESP32 IoT Libraries**

## **Description**
This repository contains Arduino projects for individual components for the starter kit included with the CS427 class (Internet of Things) at the University of Portland. Each of these component libraries are meant to be as minimal as
possible, and require little to no extra debugging or refactoring. 

### **Authors**
Jake Uyechi (uyechi23@up.edu, jake.uyechi@gmail.com)\
Surj Patel (patels@up.edu)

### **Related**
Supplementary CS427 Flask Template - https://github.com/uyechi23/CS427-FlaskTemplate

<br>

## **Setup (Windows)**

### **Prerequisites**
- Windows Command Prompt with Git
- Arduino IDE
- ESP32 Board Manager (https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

### **Installation**
Open a new Command Prompt window and navigate to the folder where your Arduino projects are stored (usually, C:\Users\<username>\Documents\Arduino):
```
C:\> chdir C:\Users\<username>\Documents\Arduino
```

Clone this repository:
```
C:\Users\<username>\Documents\Arduino> git clone https://github.com/uyechi23/CS427-IoTLibraries.git
```

Once the files are cloned, you can open the Arduino IDE and go to File > Open... and navigate to the cloned directory.

## **Supplementary Documents**
Additional files can be viewed in the _schematics and _breadboards folder. These folders include the schematic drawings for each example project, as well as
how the breadboard will look like with the completed circuit. Please use these images as a reference when constructing the circuits.

## **Library Descriptions**

### **basic_led**
A simple blink program to turn an LED on and off.

### **buzzer**
Making a noise with a simple buzzer.

### **dht11**
A simple temperature and humidity sensor module.

### **iot_demo**
An IoT demonstration project for the ESP32 to go along with the Flask Template found at https://github.com/uyechi23/CS427-FlaskTemplate.

### **joycon**
A joycon with three parameters - x-position, y-position, and a button to represent a z-position.

### **l293d_motor**
A combination between an L293D integrated circuit chip and a simple D.C. motor. The L293D (a motor driver) is used to change the speed
and direction of the motor's rotation. This example library controls the L293D chip with a potentiometer.

### **led_bar**
A 10-segment LED bar with a moving animation.

### **liquid_crystal_display**
A library for the I2C LCD included in the ESP32 kit. In this example, a button is used to increment a counter, which is displayed on the screen.

### **oled**
A black-and-white OLED display manufactured by Adafruit. The libraries within this folder contain modules that separate the functions of the OLED display,
such as using lines, shapes, text, and more.

### **potentiometer**
Shows the potentiometer's reading as a 12-bit value and voltage value (based on +3.3V).

### **push_button_pulldown and push_button_pullup**
Two libraries for different implementations of a push button.

### **rgb_led**
A 4-pin common anode RGB LED, controlled by 3 potentiometers to adjust red, green, and blue values individually.

### **serial_test**
A simple Hello World program for Serial communication on the ESP32.

### **servo**
A library for the blue servo motor. Uses a potentiometer to control the rotation of the motor.

### **speaker**
A basic speaker library that plays a basic C major scale. Unlike the buzzer library, more precise frequencies and notes can be played.

### **ultrasonic_ranger**
A library to interface with an ultrasonic ranger, which can find the distance between the sensor and an object.

### **wifi_client**
A Wi-Fi initialization library to connect to the internet. Accesses the Flask app that can be found at https://github.com/uyechi23/CS427-FlaskTemplate.

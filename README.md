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

## **Library Descriptions**

### **basic_led**
A simple blink program to turn an LED on and off.

### **iot_demo**
An IoT demonstration project for the ESP32 to go along with the Flask Template found at https://github.com/uyechi23/CS427-FlaskTemplate.

### **joycon**
A joycon with three parameters - x-position, y-position, and a button to represent a z-position.

### **led_bar**
A 10-segment LED bar with a moving animation.

### **liquid_crystal_display**
A library for the I2C LCD included in the ESP32 kit.

### **potentiometer**
Shows the potentiometer's reading as a 12-bit value and voltage value (based on +5V).

### **push_button_pulldown and push_button_pullup**
Two libraries for different implementations of a push button.

### **serial_test**
A simple Hello World program for Serial communication on the ESP32.

### **servo**
A library for the blue servo motor. Uses a potentiometer to control the rotation of the motor.

### **wifi_client**
A Wi-Fi initialization library to connect to the internet. Accesses the Flask app that can be found at https://github.com/uyechi23/CS427-FlaskTemplate.
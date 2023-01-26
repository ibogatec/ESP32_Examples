# Introduction 
Demo projects of programs for ESP32 chips:

1. 01_Blink: Simple Blinking Application. Turns LED ON and OFF repeatedly.

2. 02_Websocket_Server: Application that enables users to turn ON or OFF LED lamp that is connected on ESP32 board using web sockets.



# Getting Started
Source code is written in C++ using C++20 standard.
To successfully develop and compile this project following key components are needed:

1. C/C++ Extension pack for VS Code

2. Espressif IDF VS Code Extension:

	a. This will install: ```C:\Users\<your user name>\esp``` - C++ Components, sorces, docs, examples, etc.
	
	b. ```C:\Users\<your user name>\.espressif``` - tools (Python, compilers, ... etc)

3. arduino-esp32 submodule for using arduino classes and objects (https://github.com/espressif/arduino-esp32.git)

4. arduinoWebSockets submodule: https://github.com/Links2004/arduinoWebSockets.git

5. ESPAsyncWebServer submodule: https://github.com/me-no-dev/ESPAsyncWebServer.git

Open your ```esp-idf``` git repo that should be present in your ```C:\Users\<your user name>\esp\esp-idf``` folder and add submodules 3., 4. and 5.
Note that for submodule ```arduinoWebSockets``` you may need to specify your own ```CMakeLists.txt``` file to enable build and link this submodule with your ESP32 program.



# Build and Test
Build process uses CMake for generating Ninja build files.
To build binaries following steps are needed:

1. Create build folder inside root project folder and go to that folder

2. Assuming main CMakeLists.txt is present inside project root folder, execute ```cmake ..``` (from your build folder).
   This will generate ninja build files

3. Run ```ninja``` to compile and link your source files with required esp libraries and to produce ESP32 compliant binaries.

4. Execute ```idf.py -p COMx flash monitor``` To download (flash) your binaries to ESP32, where COMx is port where your ESP32 is connected.
   This command needs to be executed from project root.



# Contribute
- [ESP32 IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

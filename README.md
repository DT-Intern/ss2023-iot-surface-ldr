# IoT Surface Light-Dependant-Resistor
## Description

This project is a group effort / classroom project for the lecture: **Systems and Control Engineering - Technik und IoT**.


The purpose of the project is to demonstrate the use of IoT devices in a practical application.

## The task
The task involves conducting a classroom project where students are divided into groups of three. Odd-numbered groups measure the color of translucent liquid materials using a RGB LED connected to the Arduino, while the even groups measure the color of solid surface materials using the same setup but optionally with a different case  

The hardware setup requires connecting the RGB LED and a LDR (light dependent resistor) signal to the Arduino, and arranging them according to the task.  

The software part involves switching on the three LED colors and measuring the light intensity for each color, optionally normalizing the values and deriving the color value. The measurement results can be communicated to Processing terminal for recording. Suitable samples should be used to carry out the measurements.

## Team - DTintern
- Alina Simon
- Maximilian Fluegel 
- Jannes Bikker 

# Usage

The IoT device can be accessed and used over the webinterface. But the Arduino device itself is required at all times.

## Prefabricated parts

| NAME | QUANTITY | COMPONENT      |
|------|----------|----------------|
| U1   | 1        | Arduino Uno R3 |
| U1   | 1        | Wifi Shield V2.0|
| D1   | 1        | LED RGB        |
| S1   | 1        | Pushbutton     |
| R1   | 1        | 169 Ω Resistor |
| R3   | 1        | Photoresistor  |

## General Design
![Design](resources/surface-ldr-group6.png)

## Webinterface
**A**: most recent measurement color  
**B**: measurement history, displays the last 10 colors  
**C**: claibrate white (sensor has to be on a white surface, for best results a non reflecting, dense piece of paper)  
**D**:  start single measurement  
**E**: claibrate black (sensor has to be on a black surface, for best results a non reflecting, dense piece of paper/tape)
**F**: chart displaying recent measurements with corresponding RGB vlaues 
![Webinterface](/references/screenshot_annotated.png)

## Circuit Design
![Circuit Design](/resources/circuit-design.png "MarineGEO logo")

## Folder structure

```
.
├── README.md
├── iot-surface-ldr-arduino
│   └── src
│       └── ldr_surface_sensor.ino
├── iot-surface-ldr-frontend
│   ├── frontend.html
│   └── frontend_compressor.py
├── references
│   ├── measurements_black.csv
│   ├── measurements_white.csv
│   ├── plugs.txt
│   ├── proof_of_concept.ino
│   ├── reference_evaluator.py
│   ├── screenshot_annotated.gvdesign
│   └── screenshot_annotated.png
└── resources
    ├── IOT_sLDR_case.FCStd
    ├── circuit-design.png
    ├── parts.csv
    ├── surface-ldr-group6.pdf
    └── surface-ldr-group6.png

6 directories, 16 files
```

## References

- [PlatformIO](https://platformio.org/)
- [Jetbrains Clion PlatformIO](https://www.jetbrains.com/help/clion/platformio.html)
- [Chart.js](https://www.chartjs.org/)
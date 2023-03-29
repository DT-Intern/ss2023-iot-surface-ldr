/**
 * Main script of the IoT-Surface-Sensor project.
 *
 * @author Maximilian Flügel
 * @author Jannes Bikker
 * @author Alina Simon
 * @version 1.0
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFly.h"

#define SSID "iPhone$von$Max"
#define KEY "12345678"

SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

/**
 * Setup method of the program.
 * This method configures all input and outputs pins and starts the UART and Serial interfaces.
 * Furthermore, this method invokes the methods for configuring WiFly and the Network capabilities.
 */
void setup() {
    // Configure all pins
    pinMode(7, INPUT);
    pinMode(A0, INPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(8, OUTPUT);

    // Start all serial interfaces
    uart.begin(9600);
    Serial.begin(9600);
    delay(1000);

    configureWifly();
    connectAndVerifyNetwork();
}

/**
 * Method used for WiFly configuration.
 * This method starts by resetting the WiFi-Interface.
 * After that, the local port is set to 80 (HTTP default).
 * Furthermore, the default string is set to "0" (none) and new requests are buffered to "*OPEN*".
 */
void configureWifly() {
    wifly.reset();
    Serial.println("Starting");

    // Update the preferences
    wifly.sendCommand("set ip local 80\r");
    wifly.sendCommand("set comm remote 0\r");
    wifly.sendCommand("set comm open *OPEN*\r");
}

/**
 * Method that establishes the connection to the WiFi network and verifies the connection.
 * The SSID and KEY variables are used for the connection.
 * By default, WPA2 PSK (Pre-Shared-Key) is used for network authentication.
 * After the connection has been established the controller waits 5 seconds for IP-Address association.
 * After the 5 seconds, the command to retrieve the current IP is invoked and then printed to the Serial monitor.
 */
void connectAndVerifyNetwork() {
    // Connect to the configured network
    while (wifly.join(SSID, KEY, WIFLY_AUTH_WPA2_PSK) == false) {
        Serial.println("Unable to connect");
    }

    Serial.println("Connected");

    // Attempt to fetch the IP-Address
    delay(5000);
    wifly.sendCommand("get ip\r");

    // Print the result
    unsigned char c;
    while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
        Serial.print((char)c);
    }
}

/**
 * Method that is invoked continuously as long as the controller is running.
 * This method checks for any button input and incoming HTTP requests.
 * In case the button is pressed, the surface measurement method is invoked.
 * The controller has two HTTP endpoints:
 * / : Index URL that returns the dashboard of the application.
 * /measure : Invokes a surface measurement and returns the rgb values.
 */
void loop() {
    // Check for button input
    if (digitalRead(7)) {
        measureSurface(false);
        delay(500);
    }

    // Serve the dashboard
    if (wifly.available()) {
        if (uart.find("*OPEN*")) {
            delay(500);
            if (uart.find("measure")) {
                Serial.println("Request type 2");
                uart.print(F("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close"));
                measureSurface(true);
            } else {
                Serial.println("Request type 3");
                uart.print(F("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1740\nConnection: close\n\n"));
                uart.print(F("<!DOCTYPE html><html><head><title>IoT Surface LDR</title><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.5.0/semantic.min.css\" integrity=\"sha512-KXol4x3sVoO+8ZsWPFI/r5KBVB/ssCGB5tsv2nVOKwLg33wTFP3fmnXa47FdSVIshVTgsYk/1734xSk9aFIa4A==\" crossorigin=\"anonymous\" referrerpolicy=\"no-referrer\" /><script src=\"https://cdn.jsdelivr.net/npm/chart.js@4.2.1/dist/chart.umd.min.js\"></script></head><body><div class=\"ui container\"><h1>IoT Surface LDR Dashboard</h1><div id=\"measureOutput\" style=\"width: 100px; height: 100px\"></div><button id=\"measureButton\" class=\"ui fluid button primary\" style=\"margin: 1rem\" onclick=\"measure()\">Start Measurement</button><canvas id=\"historyChart\"></canvas></div><script>const createDataset = (name, color) => {return {label: name,data: [],borderColor: color,};};const context = document.getElementById(\"historyChart\");let labels = [];let redDataset = createDataset(\"Red\", \"rgb(255, 0, 0)\");let greenDataset = createDataset(\"Green\", \"rgb(0, 255, 0)\");let blueDataset = createDataset(\"Blue\", \"rgb(0, 0, 255)\");const chart = new Chart(context, {type: \"line\",data: {labels: labels,datasets: [redDataset,greenDataset,blueDataset,]},});const measure = () => {document.getElementById(\"measureButton\").disabled = true;fetch(\"http://172.20.10.8/measure\").then(r => r.text()).then(colors => {const actualColors = colors.split(\", \");chart.data.datasets[0].data.push(actualColors[0]);chart.data.datasets[1].data.push(actualColors[1]);chart.data.datasets[2].data.push(actualColors[2]);chart.data.labels.push(\"I\");chart.update();document.getElementById(\"measureButton\").disabled = false;document.getElementById(\"measureOutput\").style.backgroundColor = `rgb(${colors})`;});};</script></body></html>"));
            }
        }
    }
}

/**
 * Method that invokes a single surface measurement.
 * This is done by sequentially measuring the light intensity for red, green and blue.
 * After that, the intensity values are mapped to the corresponding RGB color values.
 * The bounds for each color channel are pre-configured and have to be calibrated for the surface.
 * After that, the result is either returned via HTTP or serial.
 *
 * @param http Determines whether the output should be via HTTP or serial.
 */
void measureSurface(bool http) {
    // Measure red
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(8, LOW);
    delay(250);
    int analogRed = analogRead(A0);
    delay(250);

    // Measure green
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(8, LOW);
    delay(250);
    int analogGreen = analogRead(A0);
    delay(250);

    // Measure blue
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(8, HIGH);
    delay(250);
    int analogBlue = analogRead(A0);
    delay(250);

    if (http) {
        // Send the result via HTTP
        String result = "";
        result += mapIntensityToRGB(analogRed, 294.9, 527.8);
        result += ", ";
        result += mapIntensityToRGB(analogGreen, 269.3, 550.7);
        result += ", ";
        result += mapIntensityToRGB(analogBlue, 468.2, 770.6);

        Serial.println(F("Calculated values"));
        Serial.println(result);
        uart.print(F("\nContent-Length: "));
        uart.print(result.length());
        uart.print("\n");
        uart.println();
        uart.print(result);
    } else {
        // Send the result via serial
        String result = "";
        result += analogRed;
        result += ", ";
        result += analogGreen;
        result += ", ";
        result += analogBlue;
        Serial.println(result);
    }

    // Turn the lights off
    digitalWrite(8, LOW);
}

/**
 * Function that maps a given light intensity value from a given range to an RGB value.
 * The following formula is used for conversion: (1 - ((x - min) / (max - min)) * 255.
 *
 * @param value Value that should be converted to RGB.
 * @param lower Lower bounds of the light intensity range.
 * @param upper Upper bounds of the light intensity range.
 *
 * @return Returns the RGB value [0..255].
 */
int mapIntensityToRGB(int value, float lower, float upper) {
    if (value < lower) {
        value = lower;
    } else if (value > upper) {
        value = upper;
    }

    return (1 - ((value - lower) / (upper - lower))) * 255.0;
}
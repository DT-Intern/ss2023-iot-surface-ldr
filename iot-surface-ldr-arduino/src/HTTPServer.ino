#include <Arduino.h>
#include <SoftwareSerial.h>
#include "DashboardHelper.h"
#include "WiFly.h"

#define SSID "iPhone$von$Max"
#define KEY "12345678"
#define AUTH WIFLY_AUTH_WPA2_PSK

SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

/**
 * Method that initializes the program.
 * This method configures the WiFi shield to use port 80 for the webpage.
 * Furthermore, the Arduino is connected to the configured WiFi.
 */
void setup() {
    // Start all serial interfaces
    uart.begin(9600);
    Serial.begin(9600);
    delay(1000);

    // Prepare network interface and connection
    configureWifly();
    connectAndVerify()
}

/**
 * Method that configures the Wifly interface.
 * This method resets the interface and sets the local port to 80.
 * The port 80 is used to serve HTTP requests.
 */
void configureWifly() {
    // Reset the preferences
    Serial.println("Resetting WiFi interface");
    wifly.reset();

    // Update the preferences
    Serial.println("Updating preferences");
    wifly.sendCommand("set ip local 80\r");
    wifly.sendCommand("set comm remote 0\r");
    wifly.sendCommand("set comm open *OPEN*\r");
}

/**
 * Method that connects the interface to the configured network and verifies the connection
 * by attempting to obtain the IP-Address of the device.
 */
void connectAndVerify() {
    // Connect to the configured network
    Serial.println("Connecting to network: " + SSID);
    while (wifly.join(SSID, KEY, AUTH) == false) {
        Serial.println("Unable to connect to: " + SSID);
    }

    Serial.println("Successfully connected to: " + SSID);

    // Attempt to fetch the IP-Address
    Serial.println("Fetching IP-Address");
    delay(3000);
    wifly.sendCommand("get ip\r");

    // Print the result
    char c;
    while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
        Serial.print((char)c);
    }
}

/**
 * Main update method that is invoked continuously.
 */
void loop() {
    // Serve
    if (wifly.available() && wifly.find("*OPEN*")) {
        writeDashboard();
    }
}

/**
 * Method that writes the dashboard to the UART interface.
 * The response is imported from the DashboardHelper header.
 */
void writeDashboard() {
    Serial.println("Writing dashboard contents to host");
    uart.print(dashboard_header);
    uart.print(dashboard_content);
}

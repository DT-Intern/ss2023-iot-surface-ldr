#include <Arduino.h>
#include <SoftwareSerial.h>
#include "frontend.h"
#include "WiFly.h"

#define SSID "iPhone$von$Max"
#define KEY "12345678"
#define AUTH WIFLY_AUTH_WPA2_PSK

SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

void setup() {
    // Pre-initialization step
    uart.begin(9600);
    Serial.begin(9600);
    delay(1000);
    wifly.reset();
    Serial.println("WiFi interface reset");

    wifly.sendCommand("set ip local 80\r");
    delay(500);
    wifly.sendCommand("set comm remote 0\r");
    delay(500);
    wifly.sendCommand("set comm open *OPEN*\r");
    delay(500);

    // Connect to the WiFi
    Serial.println("Connecting to Wifi");
    while (wifly.join(SSID, KEY, AUTH) == false) {
        Serial.println("Unable to connect");
    }
    Serial.println("Connection successful");

    Serial.println("Waiting for IP-Address");
    delay(5000);
    wifly.sendCommand("get ip\r");
    char c;
    while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
        Serial.print((char)c);
    }
}

void loop() {
    if (wifly.available()) {
        if (wifly.find("*OPEN*")) {
            transferHomepage();
        }
    }
}

void transferHomepage() {
    Serial.println("New HTTP request");
    uart.println("HTTP/1.1 200 OK");
    uart.println("Content-Type: text/html; charset=UTF-8");
    uart.println("Connection: close");
    uart.println();

    uart.print(frontend_html);
}

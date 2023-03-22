int lightSensorIN = A0;
int lightSensorValue = 0;

int pushButtonIN = 7;
int pushButtonValue;

int LED_RED = 13;
int LED_GREEN = 12;
int LED_BLUE = 8;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(pushButtonIN, INPUT);
    pinMode(lightSensorIN, INPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
}

void loop() {
    checkPushButton();
}

void turnLEDRed() {
    Serial.println("Turning red");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
}

void turnLEDGreen() {
    Serial.println("Turning green");
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
}

void turnLEDBlue() {
    Serial.println("Turning blue");
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
}

void checkPushButton() {
    pushButtonValue = digitalRead(pushButtonIN);
    Serial.println(pushButtonValue);
    delay(500);
}

void readLightSensor() {
    lightSensorValue = analogRead(lightSensorIN);
    Serial.println(lightSensorValue);
    delay(1000);
}
/**
 * @file esp8266.ino
 * @brief ESP8266 WiFi Module Communication for Home Automation
 * @author Vikum Kalhara
 * @date 2025
 * @version 1.0
 * 
 * This file manages WiFi communication and MQTT connectivity for the home automation system using ESP8266.
 */

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <ESP8266WiFi.h>
#include <Servo.h>  // Include the Servo library

const char DEVICE_LOGIN_NAME[] = "ca1d26ad-2231-41c7-9bab-4d2a8cb102f4"; // Device ID
const char SSID[] = "Pandula_B";    // WiFi SSID
const char PASS[] = "ruslwifi";     // WiFi password
const char DEVICE_KEY[] = "PT9xq!FtP9FH3?y54wdCKgY83"; // Secret key

// Define GPIO pins for LEDs, Window & Door Servos
#define LED1 D1
#define LED2 D2
#define LED3 D3
#define WINDOW1_SERVO D5  // Servo for window
#define DOOR1_SERVO D6    // Servo for door

// Variables for the state of each device
CloudSwitch switch1;
CloudSwitch switch2;
CloudSwitch switch3;
CloudSwitch window1;  // Window control
CloudSwitch door1;    // Door control

Servo windowServo;  // Create servo object for window
Servo doorServo;    // Create servo object for door

int windowPos = 0;  // Current position of window servo
int doorPos = 0;    // Current position of door servo

void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();
void onWindow1Change();
void onDoor1Change();

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
  ArduinoCloud.addProperty(switch2, READWRITE, ON_CHANGE, onSwitch2Change);
  ArduinoCloud.addProperty(switch3, READWRITE, ON_CHANGE, onSwitch3Change);
  ArduinoCloud.addProperty(window1, READWRITE, ON_CHANGE, onWindow1Change);
  ArduinoCloud.addProperty(door1, READWRITE, ON_CHANGE, onDoor1Change);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Initialize device pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Initialize servos
  windowServo.attach(WINDOW1_SERVO);
  doorServo.attach(DOOR1_SERVO);

  // Ensure both servos start at 0° (Closed)
  windowServo.write(0);
  doorServo.write(0);

  // Turn off all LEDs initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Serial.println("Connecting to WiFi...");
}

void loop() {
  ArduinoCloud.update();

  // WiFi Connection Status Check
  if (WiFi.status() == WL_CONNECTED) {
    static bool wifiConnected = false;
    if (!wifiConnected) {
      wifiConnected = true;
      Serial.println("WiFi Connected.");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
    }
  } else {
    static bool wifiDisconnected = false;
    if (!wifiDisconnected) {
      wifiDisconnected = true;
      Serial.println("WiFi Not Connected.");
    }
  }
}

// Function for smooth servo movement
void smoothMove(Servo &servo, int &currentPos, int targetPos) {
  if (currentPos < targetPos) {
    for (int pos = currentPos; pos <= targetPos; pos++) {
      servo.write(pos);
      delay(10);  // Adjust delay for speed
    }
  } else {
    for (int pos = currentPos; pos >= targetPos; pos--) {
      servo.write(pos);
      delay(10);  // Adjust delay for speed
    }
  }
  currentPos = targetPos;
}

// Handle changes from Arduino IoT Cloud
void onSwitch1Change() {
  digitalWrite(LED1, switch1 ? HIGH : LOW);
  Serial.println(switch1 ? "LED1 ON" : "LED1 OFF");
}

void onSwitch2Change() {
  digitalWrite(LED2, switch2 ? HIGH : LOW);
  Serial.println(switch2 ? "LED2 ON" : "LED2 OFF");
}

void onSwitch3Change() {
  digitalWrite(LED3, switch3 ? HIGH : LOW);
  Serial.println(switch3 ? "LED3 ON" : "LED3 OFF");
}

void onWindow1Change() {
  if (window1) {
    Serial.println("Opening WINDOW1...");
    smoothMove(windowServo, windowPos, 120);  // Rotate smoothly to 120°
  } else {
    Serial.println("Closing WINDOW1...");
    smoothMove(windowServo, windowPos, 0);  // Rotate smoothly back to 0°
  }
}

void onDoor1Change() {
  if (door1) {
    Serial.println("Opening DOOR1...");
    smoothMove(doorServo, doorPos, 120);  // Rotate smoothly to 120°
  } else {
    Serial.println("Closing DOOR1...");
    smoothMove(doorServo, doorPos, 0);  // Rotate smoothly back to 0°
  }
}

/**
 * @file uno-rfid.ino
 * @brief Arduino Uno with RFID Module for Home Automation
 * @author Vikum Kalhara
 * @date 2025
 * @version 1.0
 * 
 * This file manages RFID-based authentication for the home automation system using an Arduino Uno.
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Define pins for RFID and Servo
#define SS_PIN 10    // SDA pin for RC522
#define RST_PIN 9    // RST pin for RC522
Servo myServo;

// Create MFRC522 instance
MFRC522 rfid(SS_PIN, RST_PIN);

// Correct RFID UID
byte correctUID[] = {0xFC, 0x9C, 0x60, 0x83};

void setup() {
  Serial.begin(9600);
  SPI.begin();            // Start SPI bus
  rfid.PCD_Init();        // Initialize RFID reader
  myServo.attach(3);      // Attach servo to pin 3
  myServo.write(0);       // Set servo to initial position (0°)
  Serial.println("Place the correct RFID card to rotate servo.");
}

void loop() {
  // Check for new RFID card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Compare scanned UID with the correct UID
  if (isCorrectUID()) {
    Serial.println("Correct RFID detected. Rotating servo...");
    rotateServo();
  } else {
    Serial.println("Incorrect RFID card.");
  }

  // Halt the card after reading
  rfid.PICC_HaltA();
}

// Function to check if scanned UID matches the correct UID
bool isCorrectUID() {
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != correctUID[i]) {
      return false;
    }
  }
  return true;
}

// Function to rotate servo and return after 4s
void rotateServo() {
  myServo.write(120);           // Rotate servo to 90°
  delay(4000);                 // Wait for 4 seconds
  myServo.write(0);            // Return servo to 0°
  Serial.println("Servo returned to initial position.");
}

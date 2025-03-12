/**
 * @file megaboard.ino
 * @brief Arduino Mega Board Control for Home Automation
 * @author Vikum Kalhara
 * @date 2025
 * @version 1.0
 * 
 * This file manages the core functionality of the home automation system using an Arduino Mega board.
 * It handles communication with other modules and executes automation commands.
 */

#include <Servo.h>

// Fire Detection
#define FLAME_SENSOR_PIN 2
#define LED_PIN 3
#define BUZZER_PIN 4

// Main Gate Motion Detection (Updated)
#define PIR_SENSOR_PIN 8
#define PIR_LED_1 12
#define PIR_LED_2 13

// Ultrasonic Sensor
#define ULTRASONIC_TRIG 5
#define ULTRASONIC_ECHO 6

// Servo Motor
#define SERVO_PIN 7

Servo myServo;

void setup() {
    Serial.begin(9600);

    // Fire Detection
    pinMode(FLAME_SENSOR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // PIR Motion Detection
    pinMode(PIR_SENSOR_PIN, INPUT);
    pinMode(PIR_LED_1, OUTPUT);
    pinMode(PIR_LED_2, OUTPUT);

    // Ultrasonic Sensor
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);

    // Servo Initialization
    myServo.attach(SERVO_PIN);
    myServo.write(0);  // Set servo to 0 degrees initially

    Serial.println("✅ System Ready...");
}

void loop() {
    fireDetection();
    ultrasonicServoControl();
    motionDetection();  // 🏃 Added motion detection function
}

// Fire Detection Function
void fireDetection() {
    if (digitalRead(FLAME_SENSOR_PIN) == LOW) {
        Serial.println("🔥 Fire Detected! 🔥");
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, 3000);  // Buzzer ON
    } else {
        digitalWrite(LED_PIN, LOW);
        noTone(BUZZER_PIN);     // Buzzer OFF
    }
}

// PIR Motion Detection Function
void motionDetection() {
    if (digitalRead(PIR_SENSOR_PIN) == HIGH) {
        Serial.println("🏃 Motion Detected! Turning ON LEDs...");
        digitalWrite(PIR_LED_1, HIGH);
        digitalWrite(PIR_LED_2, HIGH);
        delay(4000); 
    } else {
        Serial.println("🛑 No Motion. Turning OFF LEDs...");
        digitalWrite(PIR_LED_1, LOW);
        digitalWrite(PIR_LED_2, LOW);
    }
}

// Smooth Servo Movement Function
void smoothServoMove(int startAngle, int endAngle) {
    if (startAngle < endAngle) {
        for (int pos = startAngle; pos <= endAngle; pos++) {
            myServo.write(pos);
            delay(15);  // Delay between movements for smoothness
        }
    } else {
        for (int pos = startAngle; pos >= endAngle; pos--) {
            myServo.write(pos);
            delay(15);
        }
    }
}

// Ultrasonic Sensor with Smooth Servo Motor Control
void ultrasonicServoControl() {
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);

    long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000);  

    if (duration == 0) {
        Serial.println("⚠️ No object detected or sensor timeout.");
        return;
    }

    float distance = duration * 0.034 / 2.0;

    Serial.print("📏 Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= 15) {
        Serial.println("🚨 Object detected! Moving servo smoothly...");
        smoothServoMove(0, 90);   // Open position smoothly
        delay(5000);              // Wait 5 seconds
        smoothServoMove(90, 0);   // Return to initial position smoothly
        delay(500);               
    }
}

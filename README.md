# Voice-Controlled Home Automation System

🚀 **A Smart Home Automation Prototype using Arduino Mega, ESP8266, and RFID**

## **Features**
- **🎤 Voice Control** - Control appliances via voice commands.
- **🔥 Fire & Motion Detection** - Enhances safety with automatic detection.
- **🔧 Ultrasonic & Servo System** - Detects obstacles and operates a servo motor.
- **🔐 RFID-Based Access** - Secure authentication system using RFID.
- **🌐 WiFi & Cloud Integration** - Remote control via ESP8266 and Arduino IoT Cloud.
- **💡 Smart Appliance Control** - Automate lights, fans, and doors.

---
![WhatsApp Image 2025-03-02 at 11 07 37 (1)](https://github.com/user-attachments/assets/34ed2153-022b-4170-a058-0a7f3ac6f4bc)

## **Project Structure**
```
Voice-Controlled-Home-Automation/
│── megaboard/                # Code for Arduino Mega (Main Controller)
│   ├── megaboard.ino
│── uno-rfid/                 # RFID-Based Access Control (Arduino Uno)
│   ├── uno-rfid.ino
│── esp8266/                  # Cloud-Connected IoT Automation
│   ├── esp8266.ino
│── README.md                 # Project Documentation
│── LICENSE                   # MIT License
│── images/                   # Screenshots & Diagrams
│── docs/                     # Additional Documentation
```

---

## **Setup & Installation**
### **1️⃣ Clone the Repository**
```bash
git clone [https://github.com/YourGitHubUsername/Voice-Controlled-Home-Automation.git](https://github.com/Sl-master123/Voice-Controlled-Home-Automation.git](https://github.com/Sl-master123/Voice-Controlled-Home-Automation.git)
cd Voice-Controlled-Home-Automation
```

### **2️⃣ Upload Code to Arduino**
- Open the `.ino` files in **Arduino IDE**.
- Select the correct **Board** and **COM Port**.
- Click **Upload**.

### **3️⃣ Install Required Libraries**
Install the following libraries in **Arduino IDE**:
```bash
# For ESP8266 Communication
pip install esptool

# Required Arduino Libraries
arduino-cli lib install "Adafruit Unified Sensor"
arduino-cli lib install "DHT sensor library"
arduino-cli lib install "MFRC522"
arduino-cli lib install "Servo"
```

### **4️⃣ Run the Project**
Power the Arduino Mega and Uno with **USB or External Power** and test the system.

---

## **Contributing**
We welcome contributions! 🚀 To contribute:
1. **Fork the repository**.
2. **Create a new branch** (`git checkout -b feature-branch`).
3. **Commit your changes** (`git commit -m "Added new feature"`).
4. **Push to GitHub** (`git push origin feature-branch`).
5. **Open a Pull Request**.

---

## **Upload Your Own Version to GitHub**
Use this Bash script to upload your modifications easily:
![WhatsApp Image 2025![WhatsApp Image 2025-03-02 at 11 07 34](https://github.com/user-attachments/assets/bb9d93fd-f501-4295-9695-90012f47e3b9)
-03-02 at 11 07 33 (1)](https://github.com/user-attachments/assets/f5e0467e-174a-4d2b-a097-5b4b7a87d9ec)

![WhatsApp Image 2025-03-02 at 11 35 04](https://github.com/user-attachments/assets/ed6316e5-8fef-47ca-95fb-d3e76371f4c6)

```bash
#!/bin/bash

# Define variables
REPO_NAME=![Uploading WhatsApp Image 2025-03-02 at 11.07.33 (1).jpeg…]()
"Voice-Controlled-Home-Automation"
GIT_USER="Sl-master123"
GIT_EMAIL="vikumkalhara16@gmail.com"
REMOTE_URL="https://github.com/$GIT_USER/$REPO_NAME.git"

# Initialize Git repository
echo "🚀 Initializing Git repository..."
git init
git config --global user.name "$GIT_USER"
git config --global user.email "$GIT_EMAIL"

# Create README.md
echo "📜 Creating README.md..."
echo "# $REPO_NAME" > README.md
echo "A smart voice-controlled home automation system using Arduino and IoT." >> README.md

# Add files & commit changes
echo "📂 Adding project files..."
git add .
git commit -m "🚀 Initial commit: Added Arduino Mega, Uno RFID & ESP8266 Code"

# Connect to GitHub
echo "🔗 Connecting to GitHub..."
git branch -M main
git remote add origin "$REMOTE_URL"

# Push to GitHub
echo "📤 Pushing to GitHub..."
git push -u origin main

echo "✅ Project uploaded successfully!"
```

Run this script in your project folder to initialize and push to GitHub.

---



## **License**
This project is licensed under the **MIT License**.

📢 *Feel free to contribute and improve this project! 🚀*


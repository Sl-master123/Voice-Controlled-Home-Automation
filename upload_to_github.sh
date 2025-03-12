#!/bin/bash

# Define variables
REPO_NAME="Voice-Controlled-Home-Automation"
GIT_USER="Vikum Kalhara"
GIT_EMAIL="VikumKalhara16@gmail.com"
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

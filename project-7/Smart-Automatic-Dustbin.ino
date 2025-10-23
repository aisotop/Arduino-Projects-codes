#include <Servo.h>
#define PIR_PIN 2 // PIR sensor output pin
#define SERVO_PIN 9 // Servo signal pin
Servo dustbinServo;
int motionDetected = 0;
bool lidOpen = false;
void setup() {
Serial.begin(9600);
pinMode(PIR_PIN, INPUT);
dustbinServo.attach(SERVO_PIN);
dustbinServo.write(0); // Start with lid closed
Serial.println("Smart Dustbin System Initialized.");
}
void loop() {
motionDetected = digitalRead(PIR_PIN);
if (motionDetected == HIGH && !lidOpen) {
Serial.println("Motion Detected! Opening Lid...");
lidOpen = true;
dustbinServo.write(180); // Open lid
delay(3000);
// Wait 3 seconds
Serial.println("Closing Lid...");
dustbinServo.write(0); // Close lid
delay(1000);
// Small delay before rechecking
lidOpen = false; // Ready for next detection
}
// Optional: print status for debugging
delay(100); // Slight delay to avoid rapid triggering
}
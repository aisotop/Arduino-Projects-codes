#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
const int pirPin = 2;     // PIR sensor pin
const int relayPin = 8;   // Relay pin
const int ledPin = 3;     // LED pin

int pirState = LOW;       // Default state
int val = 0;              // PIR reading

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(relayPin, LOW); // Relay OFF initially
  digitalWrite(ledPin, LOW);   // LED OFF initially

  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
display.println("System Ready");
 display.display();
 delay(2000);
}

void loop() {
 val = digitalRead(pirPin); // Read PIR sensor

 if (val == HIGH) { // Motion detected
 digitalWrite(relayPin, HIGH); // Turn ON relay
 digitalWrite(ledPin, HIGH); // Turn ON LED

 if (pirState == LOW) {
 Serial.println("Motion detected → Relay ON");
 showMessage("Motion Detected");
 pirState = HIGH;
 }
 } 
 else { // No motion
 digitalWrite(relayPin, LOW); // Turn OFF relay
 digitalWrite(ledPin, LOW); // Turn OFF LED

 if (pirState == HIGH) {
 Serial.println("Motion ended → Relay OFF");
 showMessage("No Motion");
 pirState = LOW;
 }
 }
}

void showMessage(String msg) {
 display.clearDisplay();
 display.setTextSize(2);
 display.setTextColor(SSD1306_WHITE);
 display.setCursor(0, 20);
 display.println(msg);
 display.display();
}

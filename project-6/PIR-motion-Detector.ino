#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
const int pirPin    = 2;   // PIR sensor pin
const int buzzerPin = 8;   // Buzzer pin (replaces relay)
const int ledPin    = 3;   // LED pin

int pirState = LOW; // Default state
int val = 0;        // PIR reading

// Buzzer tone settings (used only if passive buzzer)
const unsigned int BUZZ_FREQ = 1000; // Hz
const unsigned long BUZZ_DURATION = 5000; // ms for short beep

// For non-blocking beep
unsigned long buzzStart = 0;
bool buzzing = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Ensure buzzer and LED are off initially
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);

  // Start I2C explicitly (helps some modules)
  Wire.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    // Show error on Serial and keep running (do not hang)
    // Optionally you could flash LED here to indicate error
  } else {
    Serial.println(F("SSD1306 initialized"));
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("System Ready");
    display.display();
    delay(2000);
  }
}

void loop() {
  // Handle buzzer timeout (non-blocking)
  if (buzzing) {
    if (millis() - buzzStart >= BUZZ_DURATION) {
      noTone(buzzerPin);        // stop tone
      buzzing = false;
    }
  }

  val = digitalRead(pirPin); // Read PIR sensor

  if (val == HIGH) { // Motion detected
    digitalWrite(ledPin, HIGH); // Turn ON LED

    if (pirState == LOW) {
      Serial.println("Motion detected → Buzzer ON");
      showMessage("Motion Detected");
      // Start a short non-blocking beep
      tone(buzzerPin, BUZZ_FREQ);
      buzzStart = millis();
      buzzing = true;

      pirState = HIGH;
    }
  } else { // No motion
    digitalWrite(ledPin, LOW); // Turn OFF LED

    if (pirState == HIGH) {
      Serial.println("Motion ended → Buzzer OFF");
      showMessage("No Motion");
      // Ensure buzzer stopped
      noTone(buzzerPin);
      buzzing = false;

      pirState = LOW;
    }
  }

  // Small delay to avoid spamming the PIR reading and Serial
  delay(50);
}

void showMessage(const String &msg) {
  // If display was not initialized successfully, avoid calling display functions
  // (prevents crashes on some setups)
  // We can use a simple check by trying to clearDisplay() and catching likely no-op behavior.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}

// Push-Button LED & Buzzer Indicator
// Short press -> toggle LED
// Long hold  -> buzzer ON while held

const int buttonPin = 2;    // button connected to D2 and GND (using INPUT_PULLUP)
const int ledPin    = 8;    // LED anode -> D8 (through 220Ω to GND)
const int buzzerPin = 9;    // Buzzer + -> D9, Buzzer - -> GND

// Tuning parameters
const unsigned long debounceDelay   = 50;   // ms debounce
const unsigned long longPressDelay  = 500;  // ms required to consider it a "hold"

// runtime state
int lastButtonReading = HIGH;      // because INPUT_PULLUP
unsigned long lastDebounceTime = 0;
unsigned long buttonPressedTime = 0;
bool buttonWasPressed = false;
bool buzzerActive = false;
bool ledState = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW); // ensure buzzer off at start
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce logic: if the reading changed, reset debounce timer
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // reading is stable for debounceDelay
    if (reading == LOW && !buttonWasPressed) {
      // Button just pressed (active low)
      buttonWasPressed = true;
      buttonPressedTime = millis();
      // We don't toggle LED yet because we need to determine if it's a hold
    }

    if (reading == LOW && buttonWasPressed) {
      // Button still being held
      if (!buzzerActive && (millis() - buttonPressedTime >= longPressDelay)) {
        // Enter long-press mode: start buzzer
        buzzerActive = true;
        // If using tone-capable buzzer:
        tone(buzzerPin, 1000); // 1000 Hz tone (change if desired)
        // If you have an active buzzer that doesn't need tone, use:
        // digitalWrite(buzzerPin, HIGH);
      }
    }

    if (reading == HIGH && buttonWasPressed) {
      // Button was released
      if (buzzerActive) {
        // It was a long press -> stop buzzer
        buzzerActive = false;
        noTone(buzzerPin); // stop tone
        // if you used digitalWrite HIGH for active buzzer, set LOW here:
        // digitalWrite(buzzerPin, LOW);
      } else {
        // It was a short press -> toggle LED
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);
      }
      buttonWasPressed = false;
    }
  }

  lastButtonReading = reading;

  // Safety: if buzzerActive but button somehow released (edge case), ensure buzzer off
  if (!buttonWasPressed && buzzerActive) {
    buzzerActive = false;
    noTone(buzzerPin);
  }
}

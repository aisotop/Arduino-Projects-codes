// Pin assignments
const int ledPin = 9;
const int potPin = A0;
// PWM pin for LED
// Analog pin for potentiometer
int potValue = 0;
// Variable to store potentiometer reading
int ledBrightness = 0;
// Variable to store mapped LED brightness
void setup() {
pinMode(ledPin, OUTPUT); // Set LED pin as output
Serial.begin(9600);
// Initialize serial monitor for debugging
}
void loop() {
// Read potentiometer value (0 to 1023)
potValue = analogRead(potPin);
// Map potentiometer value to PWM range (0 to 255)
ledBrightness = map(potValue, 0, 1023, 0, 255);
// Set LED brightness
analogWrite(ledPin, ledBrightness);
// Print values to Serial Monitor (optional, for testing)
Serial.print("Potentiometer: ");
Serial.print(potValue);
Serial.print(" -> LED Brightness: ");
Serial.println(ledBrightness);
delay(50); // small delay for stability
}
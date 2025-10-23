/ IR sensors
const int leftIR = 2;
const int rightIR = 3;
// Left motor
const int enA = 10;
const int in1 = 7;
const int in2 = 6;
// Right motor
const int enB = 11;
const int in3 = 5;
const int in4 = 4;
// Motor speed
int motorSpeed = 180;
void setup() {
pinMode(leftIR, INPUT);
pinMode(rightIR, INPUT);
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT); 1
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
Serial.begin(9600);
}
void loop() {
int leftValue = digitalRead(leftIR);
int rightValue = digitalRead(rightIR);
Serial.print("Left: ");
Serial.print(leftValue);
Serial.print(" | Right: ");
Serial.println(rightValue);
// Both sensors on white surface
move forward
if (leftValue == HIGH && rightValue == HIGH) {
moveForward();
}
// Left sensor on black line
turn left
else if (leftValue == LOW && rightValue == HIGH) {
turnLeft();
}
// Right sensor on black line
turn right
else if (leftValue == HIGH && rightValue == LOW) {
turnRight();
}
// Both sensors on black (stop condition)
else {
stopMotors();
 }

}
// Motor control functions
void moveForward() {
// Left motor forward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, motorSpeed);
// Right motor forward
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enB, motorSpeed);
}
void turnLeft() {
// Left motor stop
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
analogWrite(enA, 0);
// Right motor forward
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enB, motorSpeed);
}
void turnRight() {
// Left motor forward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, motorSpeed);
// Right motor stop
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enB, 0);
}
void stopMotors() {
analogWrite(enA, 0);
analogWrite(enB, 0);
}
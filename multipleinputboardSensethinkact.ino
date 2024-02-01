int baselineTemp = 0; // Adjust this value based on your sensor's characteristics
volatile int celsius = 0; // Make it volatile for use in interrupts
int fahrenheit = 0;

// LED pins
const int ledPin2 = 2;
const int ledPin3 = 3;
const int ledPin4 = 4;

// PIR sensor pin
const int pirPin = 6; // Changed to pin 6

void setup() {
  pinMode(A0, INPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(A0), updateTemperature, CHANGE);
}

void updateTemperature() {
  celsius = map(analogRead(A0), 0, 1023, -40, 125);
}

void controlLEDs() {
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  if (celsius >= baselineTemp && celsius < baselineTemp + 10) {
    digitalWrite(ledPin2, HIGH);
  } else if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else if (celsius >= baselineTemp + 20 && celsius < baselineTemp + 30) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  } else if (celsius >= baselineTemp + 30) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  }
}

void loop() {
  baselineTemp = 40;

  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  controlLEDs();

  // Motion detection using PIR sensor
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("Motion detected!");
    // Add your code here to perform actions when motion is detected
    // For example, you can turn on an additional LED or perform other tasks.
  } else {
    Serial.println("No motion detected");
  }

  delay(1000);
}

#include <Servo.h> 

int adcValue;
float firstVoltage;
double amp;

unsigned long lastTelemetryTime = 0;
long telemetryInterval = 200;

float REFERENCE_VOLTAGE = 5.0;
float CIRCUIT_RESISTANCE = 11;

Servo myservo;
int pos = 0;
int servoPin = 12;

void setup() {
  Serial.begin(9600);
  analogReference(REFERENCE_VOLTAGE);

  myservo.attach(servoPin);
}

void loop() {
  adcValue = analogRead(A0);
  firstVoltage = adcValue * (REFERENCE_VOLTAGE / 1023.0);
  
  amp =  (firstVoltage)/ CIRCUIT_RESISTANCE;

  if (millis() - lastTelemetryTime >= telemetryInterval) {
    lastTelemetryTime = millis();
    Serial.print(" v1: ");
    Serial.print(firstVoltage);
    Serial.print(" i: ");
    Serial.println(amp);

    if (pos == 0) {
        myservo.write(180);
        pos = 180;
    } else {
        myservo.write(0);
        pos = 0;
    }
  }
}

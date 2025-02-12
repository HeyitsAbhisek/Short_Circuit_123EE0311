const int GREEN_LED = 7;
const int YELLOW_LED = 4;
const int RED_LED = 2;
const int BUTTON_PIN = 8;
const int TRIG_PIN = 13;
const int ECHO_PIN = 11;

bool emergency_mode = false;
const int DISTANCE_THRESHOLD = 50;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

bool isObjectDetected() {
  int distance = getDistance();
  return (distance > 0 && distance < DISTANCE_THRESHOLD);
}

void loop() {
  if (!emergency_mode) {
    if (!isObjectDetected()) {
      // No object detected - keep red light on
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      delay(100);  // Small delay for sensor readings
    } else {
      // Object detected - run normal traffic light sequence
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      
      for (int i = 0; i < 10; i++) {
        if (digitalRead(BUTTON_PIN) == HIGH) {
          activateEmergencyMode();
          return;
        }
        delay(1000);
      }
      
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      
      for (int i = 0; i < 10; i++) {
        if (digitalRead(BUTTON_PIN) == HIGH) {
          activateEmergencyMode();
          return;
        }
        delay(1000);
      }
      
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      
      for (int i = 0; i < 10; i++) {
        if (digitalRead(BUTTON_PIN) == HIGH) {
          activateEmergencyMode();
          return;
        }
        delay(1000);
      }
    }
  }
}

void activateEmergencyMode() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(5000);
  emergency_mode = false;
}

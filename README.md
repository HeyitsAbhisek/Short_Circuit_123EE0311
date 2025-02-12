# Short_Circuit_123EE0311_Task_1

const int GREEN_LED = 7;
const int YELLOW_LED = 4;
const int RED_LED = 2;
const int BUTTON_PIN = 8;

bool emergency_mode = false;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  if (!emergency_mode) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    
    for (int i = 0; i < 7; i++) {
      if (digitalRead(BUTTON_PIN) == HIGH) {
        activateEmergencyMode();
        return;
      }
      delay(1000);
    }
    
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    
    for (int i = 0; i < 3; i++) {
      if (digitalRead(BUTTON_PIN) == HIGH) {
        activateEmergencyMode();
        return;
      }
      delay(1000);
    }
    
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    
    for (int i = 0; i < 6; i++) {
      if (digitalRead(BUTTON_PIN) == HIGH) {
        activateEmergencyMode();
        return;
      }
      delay(1000);
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

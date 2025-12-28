boolean isOn = true;
boolean lastState = LOW;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(8, OUTPUT);
}

void loop() {
  boolean buttonState = digitalRead(7);

  // detect button press (HIGH → LOW transition)
  if (buttonState == LOW && lastState == HIGH) {
    isOn = !isOn;        // toggle state
    digitalWrite(8, isOn ? HIGH : LOW);
    delay(200);          // debounce delay
  }

  lastState = buttonState;
}

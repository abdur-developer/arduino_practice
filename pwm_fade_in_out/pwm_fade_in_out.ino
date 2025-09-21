int led = 9;

void setup()
{
  pinMode(led, OUTPUT);
  analogWrite(led, 0); // Start with LED off
}

void loop()
{
  // Fade in
  for (int i = 0; i <= 255; i++) {
    analogWrite(led, i);
    delay(5);
  }

  delay(500);

  // Fade out
  for (int i = 255; i >= 0; i--) {
    analogWrite(led, i);
    delay(5);
  }

  delay(500);
}
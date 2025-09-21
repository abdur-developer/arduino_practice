int pir = 13;
int led = 7;
int getValue;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  Serial.begin(9600);
}

void loop() {
  getValue = digitalRead(pir);
  digitalWrite(led, getValue);
  Serial.println(getValue); // 0 বা 1 দেখাবে
}

// #include <Servo.h>

// Servo myservo;

// Ultrasonic pins
const int trigPin = 10;
const int echoPin = 3;
const int led = 2;

// Servo pin
// const int servoPin = 3;

long duration;
int distance;

void setup() {
  // myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  // myservo.write(0); // শুরুতে ঢাকনা বন্ধ
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic trigger পাঠানো
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo রিড করা
  duration = pulseIn(echoPin, HIGH);

  // সেন্টিমিটারে কনভার্ট
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // // যদি 20cm এর মধ্যে কিছু আসে → ঢাকনা খুলবে
  if (distance > 0) {// && distance < 20
    digitalWrite(led, HIGH);
    // myservo.write(90); // ঢাকনা খোলা
    delay(3000);       // 3 সেকেন্ড খোলা থাকবে
  } else {
    digitalWrite(led, LOW);
    delay(500);
    // myservo.write(0);  // ঢাকনা বন্ধ
  }

  // delay(500);
}

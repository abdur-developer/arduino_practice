int led = 2;
int obstaclePin = 10;
int hasObstacle = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(obstaclePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  hasObstacle = digitalRead(obstaclePin);

  digitalWrite(led, hasObstacle);

  delay(200);
  
}

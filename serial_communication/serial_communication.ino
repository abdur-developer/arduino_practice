// C++ code
int led = 7;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("press N to On the LED");
  Serial.println("press F to Off the LED");
}

void loop()
{
  if(Serial.available() > 0 ){
    char c = Serial.read();
    if(c == 'N'){
      	digitalWrite(led, HIGH);
    	delay(1000); // Wait for 1000 millisecond(s)
    }
    if(c == 'F'){
        digitalWrite(led, LOW);
        delay(1000); // Wait for 1000 millisecond(s)
    }
  }
}
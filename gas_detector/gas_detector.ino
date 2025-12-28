int red_led = 13;//indicates gas
int buzzer = 8;//indicates gas
int green_led = 12;//indicates normal
int smokeA0 = A0;//indicates sensor is connected to A5
int sensorThres = 400;//The threshold value

void setup(){
  pinMode(red_led,OUTPUT);//red led as output
  pinMode(buzzer,OUTPUT);
  pinMode(green_led,OUTPUT);//green led as output
  pinMode(smokeA0,INPUT);//sensor as input
  //Serial.begin(9600);//starts the code
}
void loop(){
  int gas_avalue = analogRead(smokeA0);//reads sensor value
  if (gas_avalue > sensorThres){
    digitalWrite(red_led, HIGH);//turns on red led
    digitalWrite(buzzer, HIGH);//turns on red led
    digitalWrite(green_led, LOW);//turns off green led

  }else{
    digitalWrite(red_led, LOW);//turns red led off
    digitalWrite(buzzer, LOW);//turns red led off
    digitalWrite(green_led, HIGH);//turn green led on

  }
  delay(100);//delay 0.1 sec
}
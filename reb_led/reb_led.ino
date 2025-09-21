// C++ code
int red = 6;
int green = 5;
int blue = 3;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop()
{
  setColor(148,0,211); //violet
  setColor(75,0,130); //indigo
  setColor(0,0,255); //blue
  setColor(0,255,0); //green
  setColor(255,255,0); //yellow
  setColor(255,127,0); //orange
  setColor(255,0,0); //red
}

void setColor(int r, int g, int b){
	analogWrite(red, (255-r));
  	analogWrite(green, (255-g));
  	analogWrite(blue, (255-b));
  	delay(1000);
}
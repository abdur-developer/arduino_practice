#include <Keyboard.h>
#c++ code
void setup() {
  Keyboard.begin();
  pinMode (10, INPUT_PULLUP);
  pinMode (11, INPUT_PULLUP);
}

void loop() {
  int c = analogRead(A0);
  int d = analogRead(A1);
  int e = analogRead(A2);
  int f = analogRead(A3);
  int g = analogRead(A6);
  int h = analogRead(A7);
  int i = analogRead(A8);
  int j = analogRead(A9);
  // 8 pad selections

  if(c > 100){
    Keyboard.print("q");
    delay(10);
  }
  if(d > 100){
    Keyboard.print("e");
    delay(10);
  }
  if(f > 100){
    Keyboard.print("w");
    delay(10);
  }
  if(e > 100){
    Keyboard.print("r");
    delay(10);
  }
  if(g > 100){
    Keyboard.print("s");
    delay(10);
  }
  if(h > 100){
    Keyboard.print("d");
    delay(10);
  }
  if(i > 100){
    Keyboard.print("u");
    delay(10);
  }
  if(j > 100){
    Keyboard.print("x");
    delay(10);
  }


  //Tone Selection Keys
  if(!digitalRead(10)){
    Keyboard.press(KEY_UP_ARROW);
    delay(200);
  }else if(!digitalRead(11)){
    Keyboard.press(KEY_DOWN_ARROW);
    delay(200);
  }

  Keyboard.releaseAll();
}

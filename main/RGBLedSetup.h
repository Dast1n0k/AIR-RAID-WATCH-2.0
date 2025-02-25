#ifndef RGBLEDSETUP_H
#define RGBLEDSETUP_H

int red = 25;
int green = 26;
int blue = 27;


void LedSetup(){

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}


void blinkLight(int pin, int blinkCount, int delayTime) {
  for (int i = 0; i < blinkCount; i++) {
    digitalWrite(pin, HIGH); // Включаем свет
    delay(delayTime);
    digitalWrite(pin, LOW);  // Выключаем свет
    delay(delayTime);
  }
}

void red_light(int blinkCount, int delayTime) {
  blinkLight(red, blinkCount, delayTime);
}

void green_light(int blinkCount, int delayTime) {
  blinkLight(green, blinkCount, delayTime);
}
#endif
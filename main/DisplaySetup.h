#ifndef DISPLAYSETUP_H
#define DISPLAYSETUP_H

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;
extern bool alert_flag;

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message; 
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void setup_instructions(void * parameter) {
  while (true) {
    lcd.setCursor(2, 0);
    lcd.print("INSTRUCTION!");
    scrollText(1, "OPEN WIFI SETTIGNS", 450, 16);
    scrollText(1, "CHOOSE WIFI 'AIR_Alarm CLOCK'", 450, 16);
    lcd.clear();
    delay(100);  // Підтримуємо завдання активним, поки його не буде видалено ззовні
  }
  
}


#endif

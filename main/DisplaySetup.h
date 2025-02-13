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

void setup_instructions() {
  while (true) {
    lcd.setCursor(2, 0);
    lcd.print("INSTRUCTION!");
    scrollText(1, "OPEN WIFI SETTIGNS", 450, 16);
    scrollText(1, "CHOOSE WIFI 'AIR_Alarm CLOCK'", 450, 16);
    lcd.clear();
    delay(100);  // Підтримуємо завдання активним, поки його не буде видалено ззовні
  }
  
}

void lcd_print(int col, int row, const char* format, bool clearScreen = false, ...) {
    if (clearScreen) {
        lcd.clear();
    }
    lcd.setCursor(col, row);

    char buffer[17];  // Максимум 16 символов + \0
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    lcd.print(buffer);
}
#endif

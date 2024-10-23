#ifndef DISPLAYSETUP_H
#define DISPLAYSETUP_H

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;
extern bool alert_flag;

void scrollText(int row, const char* message, int delayTime, int lcdColumns) {
    char scrollMsg[32];
    snprintf(scrollMsg, sizeof(scrollMsg), " %s ", message);
    for (int pos = 0; pos < strlen(scrollMsg); pos++) {
        lcd.setCursor(0, row);
        lcd.print(scrollMsg + pos);
        delay(delayTime);
    }
}

#endif

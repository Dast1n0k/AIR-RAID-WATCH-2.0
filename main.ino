#include "WiFiSetup.h"
#include "TimeSetup.h"
#include "HttpRequest.h"
#include "DisplaySetup.h"

String alert_location; 
LiquidCrystal_I2C lcd(0x27, 16, 2);  
bool alert_flag = false; 

void setup() {
    Serial.begin(921600);
    WiFiManagerSetup();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    timeSetup();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        printLocalTime();
        checkAirRaidAlert(alert_location);
    }

    // Задержка между запросами
    delay(3000);
}

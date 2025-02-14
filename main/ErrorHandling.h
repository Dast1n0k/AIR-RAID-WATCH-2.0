#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include "WiFiSetup.h"

extern WiFiManager wfm;

void isLocationConfigured()
{
  if (alert_location == ""){
      lcd_print(1, 0, "Choose location", true);
      buzzer_sound(buzzer, 500, 700);
      lcd_print(2, 1, "Restarting...");
      delay(5000);
      wfm.resetSettings();
      ESP.restart();
    }
}

void checkWiFiStatus()
{
  if (WiFi.status() != WL_CONNECTED){
      lcd_print(1, 0, "Connection Lost");
      buzzer_sound(buzzer, 500, 700);
      delay(5000);
      ESP.restart();   
  }
}

void stopSetupInstructions()
{
  if (setupInstructionsTaskHandle != NULL) {
      vTaskDelete(setupInstructionsTaskHandle); // Завершуємо таску з інструкцією
      setupInstructionsTaskHandle = NULL;       // Обнуляємо ідентифікатор задачі
      lcd.clear();
  }
}

#endif 

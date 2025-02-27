#include "WiFiSetup.h"
#include "TimeSetup.h"
#include "HttpRequest.h"
#include "DisplaySetup.h"
#include "Sound.h"
#include "Tasks.h"
#include "ErrorHandling.h"
#include "RGBLedSetup.h"
#include "ButtonSetup.h"

String alert_location; 
LiquidCrystal_I2C lcd(0x27, 16, 2);  
bool alert_flag = false; 

extern TaskHandle_t setupInstructionsTaskHandle; //ідентифікатор завдання
extern TaskHandle_t timeTaskHandle;
extern TaskHandle_t buttonTaskHandle;
void setup() {
  Serial.begin(921600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  xTaskCreate(
    setup_instructions_task,            // Покажчик на функцію завдання
    "setup_instructions_task",          
    2048,                          // Розмір стеку в байтах
    NULL,                          
    1,                             // Пріоритетність завдань
    &setupInstructionsTaskHandle   // Зберігаємо ідентифікатор завдання
  );
  ButtonSetup();
  LedSetup();
  SoundSetup();
  WiFiManagerSetup();
  TimeSetup();
  xTaskCreate(buttonClickTask, "ButtonClickTask", 2048, NULL, 1, &buttonTaskHandle);
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    // Завершуємо завдання setup_instructions, якщо воно активне
    stopSetupInstructions();
    isLocationConfigured();
    printLocalTime();
    checkAirRaidAlert(alert_location);
    checkWiFiStatus();
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "config") {
            Serial.println("Opening settings...");
            OpenSettingsPortal();
        }
    }
     
  }
  delay(600);
}



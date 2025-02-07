#include "WiFiSetup.h"
#include "TimeSetup.h"
#include "HttpRequest.h"
#include "DisplaySetup.h"

String alert_location; 
LiquidCrystal_I2C lcd(0x27, 16, 2);  
bool alert_flag = false; 
extern TaskHandle_t setupInstructionsTaskHandle; //ідентифікатор завдання

void setup() {
  Serial.begin(921600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //Створюємо таску, яка працює паралельно
  xTaskCreate(
    setup_instructions,            // Покажчик на функцію завдання
    "setup_instructions",          
    2048,                          // Размер стека задачи (в байтах)
    NULL,                          
    1,                             // Пріоритетність завдань
    &setupInstructionsTaskHandle   // Зберігаємо ідентифікатор завдання
  );

  WiFiManagerSetup();
  timeSetup();
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    // Завершуємо завдання setup_instructions, якщо воно активне
    if (setupInstructionsTaskHandle != NULL) {
      vTaskDelete(setupInstructionsTaskHandle); // Завершуємо таску з інструкцією
      setupInstructionsTaskHandle = NULL;       // Обнуляємо ідентифікатор задачі
      lcd.clear();                            
    }

    printLocalTime();
    checkAirRaidAlert(alert_location);
  }
  
  delay(500);
}

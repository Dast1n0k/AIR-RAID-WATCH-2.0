#ifndef TASKS_H
#define TASKS_H

#include "TimeSetup.h"
#include "DisplaySetup.h"
#include "HttpRequest.h"
#include "DisplaySetup.h"

TaskHandle_t setupInstructionsTaskHandle = NULL;
TaskHandle_t timeTaskHandle = NULL;

void setup_instructions_task(void *parameter)
{
  setup_instructions();
}

// void timeTask(void *parameter) {
//   for (;;) {
//     // Захват мьютекса для экрана
//     if (xSemaphoreTake(lcdMutex, portMAX_DELAY) == pdTRUE) {
      
//       // Рисуем время на экране
//       printLocalTime(); // Функция, которая рисует время на экране

//       // Освобождение мьютекса после рисования
//       xSemaphoreGive(lcdMutex);

//       vTaskDelay(1000 / portTICK_PERIOD_MS);
//     } 
//     else 
//     {
//       Serial.println("Unlucky to catch Mutex");
//     }

//     // Задержка перед следующим обновлением
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//   }
// }


void errorTask(void *parameter) {
  Serial.println("[INFO] ErrorTask started. Waiting 10 sec...");
  delay(15000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[ERROR] Failed to connect. Incorrect password?");
    lcd_print(0, 0, "Wrong password!");
    buzzer_sound(buzzer, 500, 700);
    lcd_print(3, 1, "Try Again");
    buzzer_sound(buzzer, 500, 700);
    delay(5000);
    lcd.clear();
  }

  Serial.println("[INFO] ErrorTask finished, deleting...");

  if (setupInstructionsTaskHandle != NULL) {
    lcd.clear();
    vTaskDelete(setupInstructionsTaskHandle);
    setupInstructionsTaskHandle = NULL;
  }

  xTaskCreate(setup_instructions_task, "setup_instructions_task", 2048, NULL, 1, &setupInstructionsTaskHandle);
  vTaskDelete(NULL);  
}

#endif
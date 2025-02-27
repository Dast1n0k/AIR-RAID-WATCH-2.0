#ifndef TASKS_H
#define TASKS_H

#include "TimeSetup.h"
#include "DisplaySetup.h"
#include "DisplaySetup.h"
#include "Sound.h"
#include "RGBLedSetup.h"
#include "ButtonSetup.h"

TaskHandle_t setupInstructionsTaskHandle = NULL;
TaskHandle_t timeTaskHandle = NULL;
TaskHandle_t alertTaskHandle = NULL;
TaskHandle_t buttonTaskHandle = NULL;

void buttonClickTask(void* parameter) {
  while (true) {
    checkButtonClick();  // Отслеживаем нажатие кнопки
    vTaskDelay(10 / portTICK_PERIOD_MS);  // Небольшая задержка, чтобы снизить нагрузку на процессор
  }
}

void alertBlinkTask(void* parameter) {
    int ledPin = *((int*)parameter);

    for (int i = 0; i < 3; i++) {  
        digitalWrite(ledPin, HIGH);
        buzzer_sound(buzzer, 700, 200); 
        delay(700);
        digitalWrite(ledPin, LOW);
        delay(700);
    }

    alertTaskHandle = NULL;  
    vTaskDelete(NULL); 
}


void setup_instructions_task(void *parameter)
{
  setup_instructions();
}

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
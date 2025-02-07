#ifndef WIFIMANAGER_SETUP_H
#define WIFIMANAGER_SETUP_H

#include <WiFiManager.h>
#include "WebContent.h"
#include "DisplaySetup.h"

extern String alert_location;
extern const char custom_html[];
TaskHandle_t errorTaskHandle = NULL; 
extern TaskHandle_t setupInstructionsTaskHandle;

WiFiManager wfm;

void ErrorTask(void *parameter) {
  Serial.println("[INFO] ErrorTask started. Waiting 10 sec...");
  delay(10000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[ERROR] Failed to connect. Incorrect password?");
    lcd_print(0, 0, "Wrong password!");
    lcd_print(3, 1, "Try Again");
    delay(5000);
    lcd.clear();
  }

  Serial.println("[INFO] ErrorTask finished, deleting...");

  if (setupInstructionsTaskHandle != NULL) {
    lcd.clear();
    vTaskDelete(setupInstructionsTaskHandle);
    setupInstructionsTaskHandle = NULL;
  }

  xTaskCreate(
        setup_instructions,       // Функция новой задачи
        "SetupInstructions",      // Имя задачи
        2048,                     // Размер стека
        NULL,                     // Параметры
        1,                        // Приоритет
        &setupInstructionsTaskHandle  // Сохраняем идентификатор
  );

  vTaskDelete(NULL);  
}

void ErrorCallback() {
    Serial.println("[INFO] ErrorCallback triggered! Starting parallel task...");

    if (setupInstructionsTaskHandle != NULL) {
        Serial.println("[INFO] Deleting setupInstructionsTask...");
        lcd.clear();
        vTaskDelete(setupInstructionsTaskHandle);
        setupInstructionsTaskHandle = NULL;
        lcd_print(2, 0, "Connecting...");
    }
    xTaskCreate(
        ErrorTask,       
        "ErrorTask",      
        2048,             
        NULL,          
        2,               
        &errorTaskHandle  
    );
}

void WiFiManagerSetup() {
    std::vector<const char *> customMenu = {"wifi", "exit"};
    wfm.setMenu(customMenu);
    wfm.setTitle("ALERT IN UKRAINE");
    wfm.resetSettings();
    wfm.setDebugOutput(true);
    wfm.setClass("invert");
    wfm.setConnectTimeout(10);
    wfm.setSaveParamsCallback(ErrorCallback);

    WiFiManagerParameter custom_dropdown_html(custom_html);
    WiFiManagerParameter region_id("alert_location", "REGION ID:", "", 50);
    
    wfm.addParameter(&custom_dropdown_html);
    wfm.addParameter(&region_id);


    if (!wfm.autoConnect("AIR_Alarm Clock", "password")) {
      Serial.println("[ERROR] Failed to enter portal mode.");
      //delay(1000);
      ESP.restart();
    }

    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    alert_location = region_id.getValue();
    Serial.print("Selected region or input: ");
    Serial.println(alert_location);  
}
#endif


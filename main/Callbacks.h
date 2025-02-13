#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "DisplaySetup.h"
#include "Tasks.h"

TaskHandle_t errorTaskHandle = NULL;
extern TaskHandle_t setupInstructionsTaskHandle;

void ConnectionErrorCallback() {
    Serial.println("[INFO] ErrorCallback triggered! Starting parallel task...");

    if (setupInstructionsTaskHandle != NULL) {
        Serial.println("[INFO] Deleting setupInstructionsTask...");
        lcd.clear();
        vTaskDelete(setupInstructionsTaskHandle);
        setupInstructionsTaskHandle = NULL;
        lcd_print(2, 0, "Connecting...", true);
    }
    xTaskCreate(
        errorTask,       
        "errorTask",      
        2048,             
        NULL,          
        2,               
        &errorTaskHandle  
    );
}


#endif
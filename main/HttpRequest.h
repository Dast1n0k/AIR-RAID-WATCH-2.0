#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "Tasks.h"
#include "Secrets.h"
#include "DisplaySetup.h"
#include "RGBLedSetup.h"

extern bool alert_flag;
const char* token = TOKEN;
extern TaskHandle_t alertTaskHandle;

void checkAirRaidAlert(String region) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    String url = "https://api.alerts.in.ua/v1/iot/active_air_raid_alerts/" + region + ".json";
    http.begin(client, url);
    http.addHeader("Authorization", "Bearer " + String(token));

    int httpCode = http.GET();
    if (httpCode <= 0) {
        Serial.printf("HTTP GET request failed: %s\n", http.errorToString(httpCode).c_str());
        return;
    }

    if (httpCode == HTTP_CODE_OK) {
        String alert_status = http.getString();
        Serial.println("Alert status: " + alert_status);

        if (alert_status.indexOf('A') != -1) {
          if (!alert_flag){
            alert_flag = true;
            if (alertTaskHandle == NULL) { 
                xTaskCreate(alertBlinkTask, "AlertBlinkTask", 2048, &red, 1, &alertTaskHandle);
            }
          }
          scrollText(1, "AIR Alarm", 500, 16);
        } 

        else if (alert_status.indexOf('N') != -1) {
          if (alert_flag){
            alert_flag = false;
            if (alertTaskHandle == NULL) { 
                xTaskCreate(alertBlinkTask, "AlertBlinkTask", 2048, &green, 1, &alertTaskHandle);
            }
          }
          scrollText(1, "No AIR Alarm", 500, 16);
        }

        else if (alert_status.indexOf('P') != -1){
          if (!alert_flag){
            alert_flag = true;
            if (alertTaskHandle == NULL) { 
                xTaskCreate(alertBlinkTask, "AlertBlinkTask", 2048, &blue, 1, &alertTaskHandle);
            }
          }
          scrollText(1, "Partial Alarm", 470, 16);
        }

        else{
          lcd_print(5, 1, "NO INFO");
        }
    }
    http.end();
}

#endif

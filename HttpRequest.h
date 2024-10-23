#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "Secrets.h"
#include "DisplaySetup.h"

extern bool alert_flag;
const char* token = TOKEN;

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
            alert_flag = true;
            scrollText(1, "Air alarm", 700, 16);
        } else if (alert_status.indexOf('N') != -1) {
            alert_flag = false;
            scrollText(1, "No Alarm", 700, 16);
        }
    }
    http.end();
}

#endif

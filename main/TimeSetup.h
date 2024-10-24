#ifndef TIMESETUP_H
#define TIMESETUP_H

#include "time.h"
#include "esp_sntp.h"
#include "DisplaySetup.h"

// NTP сервера і параметри
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char *time_zone = "EET-2EEST,M3.5.0/3,M10.5.0/4"; //timezone of KIEV; More info about timezones here: https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h 

void timeSyncNotificationCallback(struct timeval *tv) {
    Serial.println("Time synchronized");
}

void timeSetup() {
    sntp_set_time_sync_notification_cb(timeSyncNotificationCallback);
    configTzTime(time_zone, ntpServer1, ntpServer2);
    esp_sntp_servermode_dhcp(1);
}

void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println(F("No time available (yet)"));
        return;
    }
    Serial.println(&timeinfo, "%H:%M");
    lcd.setCursor(6, 0);
    lcd.print(&timeinfo, "%H:%M");
}

#endif

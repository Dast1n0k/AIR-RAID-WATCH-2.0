#ifndef WIFIMANAGER_SETUP_H
#define WIFIMANAGER_SETUP_H

#include <WiFiManager.h>
#include "WebContent.h"

extern String alert_location;
extern const char custom_html[];

void WiFiManagerSetup() {
    WiFiManager wfm;
    std::vector<const char *> customMenu = {"wifi", "exit"};
    wfm.setMenu(customMenu);
    wfm.setTitle("ALERT IN UKRAINE");
    wfm.resetSettings();
    wfm.setDebugOutput(false);
    wfm.setClass("invert");

    WiFiManagerParameter custom_dropdown_html(custom_html);
    WiFiManagerParameter region_id("alert_location", "REGION ID:", "", 50);
    
    wfm.addParameter(&custom_dropdown_html);
    wfm.addParameter(&region_id);

    if (!wfm.autoConnect("AIR_Alarm Clock", "password")) {
        Serial.println("Failed to connect and hit timeout");
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

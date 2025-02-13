#ifndef WIFIMANAGER_SETUP_H
#define WIFIMANAGER_SETUP_H

#include <WiFiManager.h>
#include <Preferences.h>
#include "WebContent.h"
#include "DisplaySetup.h"
#include "Sound.h"
#include "Callbacks.h"

Preferences preferences;

extern String alert_location; 
extern const char custom_html[];
extern TaskHandle_t errorTaskHandle; 

WiFiManager wfm;

void WiFiManagerSetup() {
    preferences.begin("settings", false);
    alert_location = preferences.getString("region", "");  
    Serial.println("Loaded saved region: ");
    Serial.println(alert_location);
    bool autoconnection;
    std::vector<const char *> customMenu = {"wifi", "exit"};
    wfm.setMenu(customMenu);
    wfm.setTitle("ALERT IN UKRAINE");
    wfm.resetSettings(); //func for debuging
    wfm.setDebugOutput(true);
    wfm.setClass("invert");
    wfm.setConnectTimeout(15);
    wfm.setSaveParamsCallback(ConnectionErrorCallback);

    WiFiManagerParameter custom_dropdown_html(custom_html);
    WiFiManagerParameter region_id("alert_location", "REGION ID:", "", 50);

    wfm.addParameter(&custom_dropdown_html);
    wfm.addParameter(&region_id); 
    autoconnection = wfm.autoConnect("AIR_Alarm Clock", "password");
    //Func if success autoconnection 
    // if (WiFi.status() == WL_CONNECTED) {
    //   Serial.println("AutoConnection Success");
    //   Serial.print("Selected region or input: ");
    //   Serial.println(alert_location); 
    //   return;
    // } 
    if (!autoconnection) {
      Serial.println("[ERROR] Failed to autoConnect.");
      delay(1000);
      ESP.restart();
    }
    else {
      vTaskDelete(errorTaskHandle);
      errorTaskHandle = NULL;
      lcd.clear();
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      alert_location = region_id.getValue();
      Serial.print("Selected region or input: ");
      Serial.println(alert_location);  
      preferences.putString("region", alert_location);
      Serial.println("Region saved to NVS.");
        
      preferences.end();  // Закрываем NVS (необязательно, но хорошая практика)
    }
}

// I want to rewrite this fucking shit blyat suka function
void OpenSettingsPortal() {
  Serial.println("Reset Settings");
  wfm.resetSettings();
  lcd_print(2, 0, "Restarting...", true);
  delay(3000);
  ESP.restart();
}


#endif


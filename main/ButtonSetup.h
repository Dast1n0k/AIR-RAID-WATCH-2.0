#ifndef BUTTONSETUP_H
#define BUTTONSETUP_H

#include "WiFiSetup.h"

int button = 13;
extern WiFiManager wfm;

void ButtonSetup(){
  pinMode(button, INPUT);

}

// I want to rewrite this fucking shit blyat suka function
void OpenSettingsPortal() {
  Serial.println("Reset Settings");
  lcd.clear();
  lcd.noBacklight();
  wfm.resetSettings();
  ESP.restart();
}

void checkButtonClick(){
  if (digitalRead(button) == HIGH){
    Serial.println("Opening settings...");
    OpenSettingsPortal();
  }
}

#endif
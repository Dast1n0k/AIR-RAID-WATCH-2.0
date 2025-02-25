#ifndef SOUND_H
#define SOUND_H

const int buzzer = 2;

void SoundSetup()
{
  pinMode(buzzer, OUTPUT);
}


void buzzer_sound(int buzzer_pin, int sound_frequency, int sound_duration){
  tone(buzzer_pin, sound_frequency); 
  delay(sound_duration);        
  noTone(buzzer_pin);     
  delay(sound_duration);
}


#endif
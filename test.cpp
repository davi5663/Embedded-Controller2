/* 
#include "mbed.h"
#include "header.h"
#include "stm32746g_discovery_lcd.h"


extern DigitalOut blueled(D3);
extern DigitalOut redled(D2);
extern InterruptIn button(D4);
extern DigitalOut buzzer(D8);
extern AnalogIn soundsensor(A0);
extern AnalogIn lightsensor(A1);
bool buzzeractive = true;
int noise = 0;

void Light() {
  float light = 0.2,
        Lys; // 0.2 is lightness that I use for my darkness and lightness.
  while (true) {
    Lys = lightsensor.read();
    if (Lys > light) {
      BSP_LCD_ClearStringLine(9); // I use this to clear darkness so the text is not on each other.
      BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)"Det er lyst!",CENTER_MODE);
      printf("Light %f\n", Lys);
      ThisThread::sleep_for(1s);
      blueled = 0;
    }
    if (Lys < light && noise >= 0.4 && buzzeractive) {
      BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)"Det er skummelt!",CENTER_MODE);
      printf("Dark %f\n", Lys);
      ThisThread::sleep_for(1s);
      blueled = 1;
      buzzer = 1;
    }
  }
}

void Alarm() {
  while (1) {
    noise = soundsensor;
    if (noise >= 0.4 && buzzeractive) {

      BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)"Lyden er for grande!",CENTER_MODE);
      redled = 1;
      ThisThread::sleep_for(1s);
    } else {
      redled = 0;

      BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)"                    ",CENTER_MODE);
    }
  }
}
*/



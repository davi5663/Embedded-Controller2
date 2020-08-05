#include "Grove_LCD_RGB_Backlight.h" //Libary for LCD Backligt
#include "mbed.h"
#include "stm32746g_discovery_lcd.h" //Libary for TouchScreen

DigitalOut myblueled(D3);
DigitalOut myredled(D2);
DigitalIn mybutton(D4);
DigitalOut mybuzzer(D8);

// main() runs in its own thread in the OS
int main() {
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt(
      0, 0, (uint8_t *)"TEST",
      CENTER_MODE); // The first number 0 goes more to the right direction

  while (true) {
  }
}

#include "DHT.h"                     //Libary for Tempature & Humidity
#include "Grove_LCD_RGB_Backlight.h" //Libary for LCD Backligt
#include "mbed.h"
#include "stm32746g_discovery_lcd.h" //Libary for TouchScreen
#include <string>

DigitalOut blueled(D3);
DigitalOut redled(D2);
DigitalIn button(D4);
DigitalOut buzzer(D8);
DHT Sensor(D6, DHT22);

int err;



// main() runs in its own thread in the OS
int main() {
  float f = 0.0f;
  

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  char text[25];
  //string office = "Office 345- David";
  sprintf(text, "Office %i", int(text));
  BSP_LCD_DisplayStringAt(0, 180, (uint8_t *)text, CENTER_MODE); // The first number 0 goes more to the right direction
      
  printf("New Test version 2:\n\r");
  while (1) {
    err = Sensor.readData();
    f = Sensor.ReadTemperature(CELCIUS);
    char tempature[25];
    sprintf(tempature, "Temprature %i", int(f));
    BSP_LCD_DisplayStringAt(0,0, (uint8_t *)tempature, CENTER_MODE );

    if (0 == err) {
      f = Sensor.ReadTemperature(FARENHEIT);
      printf("Temp: F %4.2f", f);
      f = Sensor.ReadTemperature(CELCIUS);
      printf(", C %4.2f\n \r", f);
      f = Sensor.ReadHumidity();
      printf("Humidty: H %4.2f\n \r ", f);
      
    }
    wait_us(1000000);
  }
}

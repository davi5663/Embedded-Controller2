#include "DHT.h"                     //Libary for Tempature & Humidity
#include "Grove_LCD_RGB_Backlight.h" //Libary for LCD Backligt
#include "mbed.h"
#include "stm32746g_discovery_lcd.h" //Libary for TouchScreen
#include <string>

DigitalOut blueled(D3);
DigitalOut redled(D2);
InterruptIn button(D4);
DigitalOut buzzer(D8);
DHT Sensor(D6, DHT22);
bool buzzeractive = true;
int err;
int PressCount = 0;

void ButtonCounter(){
 PressCount ++;
}

// main() runs in its own thread in the OS
int main() {
  float f = 0.0f;
  int heat;
  button.rise(&ButtonCounter); //When button is pressed down the event will run 

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  char office[20] = "Kontor 345- David"; //Creating office name
  BSP_LCD_DisplayStringAt(
      0, 0, (uint8_t *)office,
      CENTER_MODE); // The first number 0 goes more to the right direction

  printf("New Test version 2:\n\r");
  while (1) {
     
       
    err = Sensor.readData(); //The sensor will read the temperature 
    f = Sensor.ReadTemperature(CELCIUS);
    heat = f; //Heat variable is the same as my f which read the Temperature
    char tempature[25]; //Creating a char to read my temperature
    sprintf(tempature, "Temperature %i", int(f)); //Reads both my char and int to print out a text which is "Temperature" and the temperature 
    BSP_LCD_DisplayStringAt(0, 50, (uint8_t *)tempature, CENTER_MODE);

    if (0 == err) { //Creating if statements so I can also see it in my mbed studio serial connection tab.
      f = Sensor.ReadTemperature(CELCIUS);
      printf("Celius: C %4.2f\n \r", f);
      f = Sensor.ReadHumidity();
      printf("Humidty: H %4.2f\n \r ", f);
    }
    wait_us(1000000);
    if (heat > 30 && buzzeractive) {
      BSP_LCD_DisplayStringAt(0, 75, (uint8_t *)"Temprature er for varmt!",CENTER_MODE);
        buzzer = 1;
        redled = 1;
        ThisThread::sleep_for(1s);
        buzzer = 0;
        redled = 0;
    }
    else if (heat < 20){
        BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)"Temprature er for koldt!",CENTER_MODE);
        blueled = 1;
    }
    if (heat == 27){
        BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)"Tempraturet er perfekt!",CENTER_MODE);
    }

    if (PressCount >= 2){
        buzzeractive = !buzzeractive;
        buzzer = 0;
        PressCount=0;
    }
  }
}

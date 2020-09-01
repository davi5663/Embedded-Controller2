#include "mbed.h"
#include "DHT.h"                     //Libary for Tempature & Humidity
#include "Grove_LCD_RGB_Backlight.h" //Libary for LCD Backligt
#include "stm32746g_discovery_lcd.h" //Libary for TouchScreen
#include <string>
#include "header.h"

DigitalOut blueled(D3);
DigitalOut redled(D2);
InterruptIn button(D4); //I use IntteruptIn for my button to trigger an event when a digital input pin changes
DigitalOut buzzer(D8);
DHT Sensor(D6, DHT22);
AnalogIn soundsensor(A0);
AnalogIn lightsensor(A1);
bool buzzeractive = true;
static BufferedSerial pc(USBTX, USBRX);
int err;
int PressCount = 0;
int noise = 0;
Thread tAlarm;
Thread tLight;

void ButtonCounter() { PressCount++; }

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

// main() runs in its own thread in the OS
int main() {
  int getTxtInp(char linie[], int MAX); // Tried creating serial communcation and my mbed to work together
  float f = 0.0f;
  float h;
  int heat;

  button.rise(&ButtonCounter); // When button is pressed down the event will run

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  /* char office[20] = "Kontor 345- David"; // Creating office name
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)office,CENTER_MODE); // The first number 0 goes more to the right direction*/

  printf("New Test version 2:\n\r");
  tAlarm.start(&Alarm);
  tLight.start(&Light);

  while (1) {
    err = Sensor.readData(); // The sensor will read the temperature
    f = Sensor.ReadTemperature(CELCIUS);
    h = Sensor.ReadHumidity();
    heat = f; // Heat variable is the same as my f which read the Temperature
    char tempature[25]; // Creating a char to read my temperature
    char humidty[25];
    sprintf(tempature, "Temperature %i",int(f)); // Reads both my char and int to print out a text which is "Temperature"
    BSP_LCD_DisplayStringAt(0, 50, (uint8_t *)tempature, CENTER_MODE);
    sprintf(humidty, "Fugtighed %2.0f", h);
    BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)humidty, CENTER_MODE);

    if (0 == err) { // Creating if statements so I can also see it in my mbed studio serial connection tab.
      f = Sensor.ReadTemperature(CELCIUS);
      printf("Celius: C %4.2f\n \r", f);
      f = Sensor.ReadHumidity();
      printf("Humidty: H %4.2f\n \r ", f);
      printf("Loudness: %f\r\n", soundsensor.read());
    }

    wait_us(1000000);
    BSP_LCD_ClearStringLine(5);
    if (heat > 30 && buzzeractive) {
      BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Temprature er for varmt!",CENTER_MODE);
      buzzer = 1;
      redled = 1;
      ThisThread::sleep_for(1s);
      buzzer = 0;
      redled = 0;
    }

    else if (heat < 20 && buzzeractive) {
      BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Temprature er for koldt!",CENTER_MODE);
      blueled = 1;
    }

    else {
      blueled = 0;
    }

    if (heat >= 27) {
      BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Tempraturet er perfekt!",CENTER_MODE);
    }

    if (PressCount >= 2) { // If you press the button twice you will disable the buzzer and the presscount will also be disabled.
      buzzeractive = !buzzeractive;
      buzzer = 0;
      PressCount = 0;
    }
  }
}

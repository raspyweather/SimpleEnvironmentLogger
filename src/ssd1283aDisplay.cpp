#include <Arduino.h>

#define ARDUINO_ARCH_ESP8266
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library
#include "ssd1283aDisplay.h"
//paramters define
#define MODEL SSD1283A

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

//paramters define
#define MODEL SSD1283A
#define CS   D8
#define CD   D0
//#define SDA  A2   //if you use the hardware spi,this pin is no need to set
//#define SCK  A1   //if you use the hardware spi,this pin is no need to set
#define RST  D0
#define LED  D4   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V


//the definiens of hardware spi mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI mylcd(MODEL,CS,CD,RST,LED); 

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void ssd1283aDisplay::init(void) {
  Serial.println("hello!");
   mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
}



void ssd1283aDisplay::processData(UnifiedSensor_t input) {
  Serial.println("print display");
  mylcd.Set_Text_Mode(0);
  // mylcd.Fill_Screen(0x0000);

  if(!isnan(input.pressure)){
    mylcd.Fill_Rect(0,8,130,8,BLACK);
    mylcd.Set_Text_colour(GREEN);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_Size(1);
    mylcd.Print_String("Pressure", 0, 0);
    mylcd.Print_Number_Float(input.pressure, 2, 0, 8, '.', 0, ' ');  
  }

  if(!isnan(input.temperature)){
    mylcd.Fill_Rect(0,24,130,8,BLACK);
    mylcd.Set_Text_colour(GREEN);
    mylcd.Set_Text_Size(1);
    mylcd.Print_String("Temp", 0, 16);
    mylcd.Print_Number_Float(input.temperature, 2, 0, 24, '.', 0, ' ');  
  }
  if(!isnan(input.lightIntensity)){
    mylcd.Fill_Rect(0,40,130,8,BLACK);
    mylcd.Set_Text_colour(GREEN);
    mylcd.Set_Text_Size(1);
    mylcd.Print_String("Light", 0, 32);
    mylcd.Print_Number_Float(input.lightIntensity, 2, 0, 40 , '.', 0, ' ');  
  }
  if(!isnan(input.humidity)){
    mylcd.Fill_Rect(0,56,130,8,BLACK);
    mylcd.Set_Text_colour(GREEN);
    mylcd.Set_Text_Size(1);
    mylcd.Print_String("Humidity", 0, 48);
    mylcd.Print_Number_Float(input.humidity, 2, 0, 56, '.', 0, ' ');  
  }
  if(!isnan(input.tvoc)){
    mylcd.Fill_Rect(0,72,130,8,BLACK);
    mylcd.Set_Text_colour(GREEN);
    mylcd.Set_Text_Size(1);
    mylcd.Print_String("TVOC", 0, 64);
    mylcd.Print_Number_Float(input.tvoc, 2, 0, 72, '.', 0, ' ');  
  }

}
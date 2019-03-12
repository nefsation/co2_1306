#include <MQ135.h>

#include <OakOLED.h>

#include <Adafruit_SSD1306.h>

#include <Wire.h>

//#include <SPI.h>

/*
 * Carbon Dioxide Parts Per Million Meter
 * CO2PPM
 * 
 * learnelectronics
 * 26 MAR 2017
 * 
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
 */

/*
 * Atmospheric CO2 Level..............400ppm
 * Average indoor co2.............350-450ppm
 * Maxiumum acceptable co2...........1200ppm
 * Dangerous co2 levels.............>2000ppm
 */






//---------------------------------------------------------------------------------------------------------------
//                                                  LIBRARIES
//---------------------------------------------------------------------------------------------------------------
//#include <Wire.h>                             //I2C for OLED
#include <Adafruit_GFX.h>                     //grafix library for OLED
#include <Adafruit_SSD1306.h>                 //OLED Driver
//#include <LiquidCrystal.h>
int backLight = 13;    // pin 13 will control the backlight

//#include <SimpleDHT.h>
//---------------------------------------------------------------------------------------------------------------
//                                                   DEFINES
//---------------------------------------------------------------------------------------------------------------
#define anInput     A0                        //analog feed from MQ135
#define digTrigger   2                        //digital feed from MQ135
#define co2Zero     55                        //calibrated CO2 0 level
//#define led          13                        //led on pin 9
//#define OLED_RESET   4                        //OLED reset on lin 4
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

//---------------------------------------------------------------------------------------------------------------
//                                                LIBRARY CALL
//---------------------------------------------------------------------------------------------------------------
Adafruit_SSD1306 display(OLED_RESET);         //create instance of OLED called display


//---------------------------------------------------------------------------------------------------------------
//                                                  SETUP
//---------------------------------------------------------------------------------------------------------------
void setup() {
  
  pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
  pinMode(digTrigger,INPUT);                  //MQ135 digital feed set for input
//  pinMode(led,OUTPUT);                        //led set for output
  Serial.begin(9600);                         //serial comms for debuging
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //begin display @ hex addy 0x3C
  display.display();                          //show buffer
  display.clearDisplay();                     //clear buffer
  //lcd.begin(20, 4);             // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  //lcd.clear();                  // start with a blank screen
}
//---------------------------------------------------------------------------------------------------------------
//                                               MAIN LOOP
//---------------------------------------------------------------------------------------------------------------
void loop() {
  
int co2now[10];                               //int array for co2 readings
int co2raw = 0;                               //int for raw value of co2
int co2comp = 0;                              //int for compensated co2 
int co2ppm = 0;                               //int for calculated ppm
int zzz = 0;                                  //int for averaging
int grafX = 0;                                //int for x value of graph


  //display.clearDisplay();                     //clear display @ beginning of each loop

  for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(A0);
    delay(200);
  }

for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                            //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,400,5000);      //map value for atmospheric levels

  display.setTextSize(2);                     //set text size
  display.setTextColor(WHITE);                //set text color
  lcd.setCursor(0,0);                     //set cursor
  lcd.println("CO2 Level");               //print title
  Serial.print("CO2: ");                       //skip a line
  Serial.println(co2ppm);                       //skip a line

  //lcd.print(co2ppm);                      //print co2 ppm
  //lcd.print(" PPM");                      //print units
  //grafX = map(co2ppm,0,1000,0,127);           //map value to screen width
  //lcd.fillRect(0, 52, grafX, 10, WHITE);  //print graph 400min 1000max
  //lcd.display();
  }                          //show the buffer
  //if(co2ppm>900){                             //if co2 ppm > 1000
    //digitalWrite(led,HIGH);                   //turn on led
  
//  else{                                       //if not
  //  digitalWrite(led,LOW);                    //turn off led
//  }

#include <Adafruit_NeoPixel.h>

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define PIN 6

#define NUM_LEDS 32

#define BRIGHTNESS 64

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };



char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {


//
  Serial.begin(9600);
//
  delay(1000); // wait for console opening


  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.println("starting, testing lights");

  setRingToColor(255,0,0,0);
  delay(500);
  setRingToColor(0,255,0,0);
  delay(500);
  setRingToColor(0,0,255,0);
  delay(500);
  setRingToColor(0,0,0,255);
  delay(1000);

  Serial.println("finished testing lights");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void printWithLeadingZero(int num){

  if(num < 10){
    Serial.print("0");
    Serial.print(num,DEC);
  }else{
    Serial.print(num,DEC);
  }
  
}

void loop () {
    DateTime now = rtc.now();

    Serial.print("It's ");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
     Serial.print(" at ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    printWithLeadingZero(now.minute());
    Serial.print(':');
    printWithLeadingZero(now.second());

    

    if(now.dayOfTheWeek() == 0 || now.dayOfTheWeek() == 6){
      Serial.println(". It's a weekend.");
      weekend(now);
    }else{
      Serial.print(". It's a weekday. The light is ");
      weekday(now);
    }

    
    Serial.println('.');

    delay(1000);

}

void weekday(DateTime now){
  if(now.hour() < 6){
      // red
      setRingToColor(100,0,0,0);
      Serial.print("red");
    }else if(now.hour() == 6 && now.minute() < 45){
      // red
      setRingToColor(100,0,0,0);
      Serial.print("red");
    }else if(now.hour() == 6 && now.minute() >= 45){
      setRingToColor(100,100,0,0); // yellow
      Serial.print("yellow");
    }else if(now.hour() == 7 && now.minute() < 15){
      setRingToColor(100,100,0,0); // yellow
      Serial.print("yellow");
    }else if(now.hour() == 7){
      // green
      setRingToColor(0,100,0,0);
      Serial.print("green");
    }else if(now.hour() > 21){
      setRingToColor(100,0,0,0);
      Serial.print("red");
    }else{
      setRingToColor(0,0,0,0);
      Serial.print("off");
    }
}

void weekend(DateTime now){
  if(now.hour() < 7){
      // red
      setRingToColor(100,0,0,0);
      Serial.print("red");
    }else if(now.hour() == 7 && now.minute() < 30){
      setRingToColor(100,100,0,0); // yellow
      Serial.print("yellow");
    }else if(now.hour() == 7 && now.minute() >= 30){
      // green
      setRingToColor(0,100,0,0);
      Serial.print("green");
    }else if(now.hour() == 8){
      // green
      setRingToColor(0,100,0,0);
      Serial.print("green");
    }else if(now.hour() > 21){
      setRingToColor(100,0,0,0);
      Serial.print("red");
    }else{
      setRingToColor(0,0,0,0);
      Serial.print("off");
    }
}


void setRingToColor(int r, int g, int b, int w){
  int ledCount = 32;

  for(int i=0; i<ledCount; i++ ){
    strip.setPixelColor(i, neopix_gamma[r], neopix_gamma[g], neopix_gamma[b], neopix_gamma[w]);
  }
  strip.show();
}

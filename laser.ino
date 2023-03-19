#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
#define PLAY_E 4
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground
 
// set to false if using a common cathode LED
#define commonAnode true
 
// our RGB -> eye-recognized gamma color
byte gammatable[256];
 
 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
// Arduino and KY-018 module

void setup() {
  Serial.begin(9600); // initialize serial monitor
  Serial.println("A0       A1");
  pinMode(3, OUTPUT);
  //Serial.println("Color View Test!");
 
  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
 
  // use these three pins to drive an LED
  pinMode(4, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
 
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
 
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }
  // initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.clear();
  
}

void loop() {
   // send analog input to serial monitor
   //lcd.clear();
  digitalWrite(3, LOW);
  int a0 = analogRead(A0);
  Serial.print(a0);
  Serial.print("\t");

  int a1 = analogRead(A1);
  Serial.print(a1);
  Serial.println();

  if (a0 < 70){
    if (a1<70){
      Serial.println("==================Laser==================");
      /// convert lock to red led in pin 3
      digitalWrite(3, HIGH);
      lcd.print("     02:04     ");

      while(true){
        float red, green, blue;
        tcs.setInterrupt(false);  // turn on LED
        delay(60);  // takes 50ms to read
        tcs.getRGB(&red, &green, &blue);
        tcs.setInterrupt(true);  // turn off LED

        //color check

        if (red>200){
            if(blue>green){
              Serial.print("my color!");
              lcd.clear();
              lcd.print("CONGRADULATIONS!");
              while(true){
                digitalWrite(PLAY_E, HIGH);
                // delay(50);
                digitalWrite(PLAY_E, LOW);
              }
              exit(0);
            }
          }
        
        Serial.print("R:\t"); Serial.print(int(red));
        Serial.print("\tG:\t"); Serial.print(int(green));
        Serial.print("\tB:\t"); Serial.print(int(blue));
      
        Serial.print("\n");
        delay(1000);
      
        analogWrite(redpin, gammatable[(int)red]);
        analogWrite(greenpin, gammatable[(int)green]);
        analogWrite(bluepin, gammatable[(int)blue]);
      }
   }
  }
  delay(1000);
}

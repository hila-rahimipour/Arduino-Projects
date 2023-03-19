#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int analogPin = 0;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 10000;
float R2 = 0;
float buffer = 0;

void setup(){
  Serial.begin(9600);
  	// initialize the LCD
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();

  /// add lock to pin 5!!!!
  /// check for 2 pins in 3 (electro and lock)
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);

}

void loop(){
  raw = analogRead(analogPin);
  
  if(raw){
    buffer = raw * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R2= R1 * buffer;
    Serial.print("Vout: ");
    Serial.println(Vout);
    Serial.print("R2: ");
    Serial.println(R2);
    lcd.clear();
    lcd.print(R2);
    /// check resistance values and update!!!
    //2000, 3700
    if (R2>2000){
      Serial.print("big 2000");
      if(R2<3700){
        
        
        digitalWrite(3, HIGH);
        digitalWrite(5, HIGH);
        lcd.clear();
        while(true){
          lcd.clear();
          lcd.print("Open The Door!");
        }
      }
    }
    delay(1000);
  }
}
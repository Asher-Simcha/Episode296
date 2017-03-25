#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Wire.begin();
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void LCDtest()
{
  lcd.setCursor(0,0);
  lcd.print("Line1");

  lcd.setCursor(0,1);
  lcd.print("Line2");

  lcd.setCursor(0,2);
  lcd.print("Line3");

  lcd.setCursor(0,3);
  lcd.print("Line3");
  
  delay(100);
}

void loop()
{
  LCDtest();
}


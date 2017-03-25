#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DS3231_I2C_ADDRESS 0x68 // The address of the RTC
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int LastHour = 99;
int LastMin = 99;
int LastSec = 99;

void setup()
{
  Wire.begin();
  lcd.init();                      // initialize the lcd 
}

// ------------------------------------------- Start Decimal to Byte Conversion----------------------------------------//
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}

// This function converts binary to decimal
// Required for most RTC functions
// ------------------------------------------- End Decimal to Byte Conversion----------------------------------------//


// ------------------------------------------- Start Byte to Decimal Conversion----------------------------------------//
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}
// ------------------------------------------- End Byte to Decimal Conversion------------------------------------------//

// ------------------------------------------- Start RTC Time-Set  ------------------------------------------//
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
// ------------------------------------------- End RTC Time-Set  ------------------------------------------//

// ------------------------------------------- Start Read Time --------------------------------------------------------//

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
// ------------------------------------------- End Read Time --------------------------------------------------------//

// ------------------------------------------- Start HomeScreen (Mode 1) --------------------------------------//
// This function reads from the RTC, then displays day, hour, minute, second on the OLED
void HomeScreen()
{

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Time:");

  // We COULD just use the lcd.clear() function to wipe the screen every cycle, but that makes the screen flicker
  // Instead, the following logic only changes the parts of the display that need refreshing

  if(LastHour != hour)
  {
    if(hour < 10)
    {
      lcd.setCursor(12,0);
      lcd.print("0");
      lcd.print(hour);
    }
    else
    {
      lcd.setCursor(12,0);
      lcd.print(hour);
    }

    lcd.setCursor(14,0);
    lcd.print(":");
  }

  if(LastMin != minute)
  {
    if(minute < 10)
    {
      lcd.setCursor(15,0);
      lcd.print("0");
      lcd.print(minute);
    }
    else
    {
      lcd.setCursor(15,0);
      lcd.print(minute);
    }
    
  lcd.setCursor(17,0);
  lcd.print(":");
  }

  if(LastSec != second)
  {
    if(second < 10)
    {
      lcd.setCursor(18,0);
      lcd.print("0");
      lcd.print(second);
    }
    else
    {
      lcd.setCursor(18,0);
      lcd.print(second);
    }    
  }
  
  LastHour = hour;
  LastMin = minute;
  LastSec = second;

delay(100);

}
// ------------------------------------------- End Home Screen --------------------------------------------------------//

void loop()
{
 HomeScreen();
}


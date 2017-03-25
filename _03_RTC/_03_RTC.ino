#include <Wire.h> 

#define DS3231_I2C_ADDRESS 0x68 // The address of the RTC

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(13, OUTPUT);
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

// ------------------------------------------- Start displayTime() --------------------------------------------------------//
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}

// ------------------------------------------- End displayTime() --------------------------------------------------------//

// ------------------------------------------- Start TickTock --------------------------------------------------------//

void TickTock()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  Serial.println((second%2));
  if((second%2) == 1)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}

// ------------------------------------------- End TickTock --------------------------------------------------------//


void loop()
{
 displayTime(); // display the real-time clock data on the Serial Monitor
 TickTock();
 delay(1000);
}


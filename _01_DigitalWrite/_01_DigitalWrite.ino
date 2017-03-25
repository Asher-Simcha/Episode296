// This is the Arduino version of ""Hello World""
// We're using a digital pin to power a 5V LED
// Connect the ""Long leg"" of the LED to the digital pin and the short leg to GND

// Let's up our game a little
// We're going to use the ""define"" function to set our digital pin as a constant at program start
// This will make it easier to redefine what pin we'll use for our LED
// We're also going to use a constant to set our delay period 

#define dpin 7
#define wait 500

void setup() 
{
  pinMode(dpin, OUTPUT);
  // The first step is to tell the Arduino where we're going to connect the LED
  // ""7"" tells the pinMode function that we're connecting the positive led to digital pin 7
  // ""OUTPUT"" tells the pinMode function that we're using the pin for output, not input
}

// Remember that the Arduino will loop the code inside of ""loop()"" continously

void loop() {
  digitalWrite(dpin, HIGH);
  // Power-on Digital pin 7
  
  delay(wait);   
  // Wait 1000 ms

  digitalWrite(dpin, LOW);
  // Power-off Digital pin 7

  delay(wait);
  // Wait 1000ms
}

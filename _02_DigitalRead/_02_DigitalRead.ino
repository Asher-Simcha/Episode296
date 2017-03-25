// Using constants to define to which pin each button is connected

#define buttonPin1 2
int OnOff;

// This is the variable that stores the state of the button"
void setup()
{
  // Open the serial port so we can see the values of our button
  Serial.begin(9600);
  
  // Setting the mode for the pin to which the button is connected
  pinMode(buttonPin1, INPUT);     

}
void loop()
{

  // Call the first Button
  OnOff = digitalRead(buttonPin1);
  if (OnOff == HIGH)
  {     
  Serial.print("High");
  Serial.print("\t");
  } 
  else 
  {
  Serial.print("Low");
  Serial.print("\t");
  } 
    
  Serial.print("\n");
}

int buttonpin = 3; // define D0 Sensor Interface
int val = 0;// define numeric variables val
int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor


void setup ()
{
  Serial.begin (9600);
  pinMode (buttonpin, INPUT) ;// output interface D0 is defined sensor
}
 
void loop ()
{
  val = digitalRead(buttonpin);// digital interface will be assigned a value of pin 3 to read val
  if (val == HIGH) // When the sound detection module detects a signal, LED flashes
  {
    Serial.println("Clap On");
  }
  else
  {
    Serial.println("Clap OFF");
  }
sensorValue = analogRead (sensorPin);
  Serial.println("Sensor Value");
  Serial.println (sensorValue, DEC);
  delay (1000);

}
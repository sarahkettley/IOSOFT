// IOSOFT
//
// Capacitant Rug Slave code for the Particle Photon
// Created by Sarah Kettley
//
//  Capacitant Node Notes:
//      The data from the nodes is delivered in a data bus of 8 values in the array capData.
//      Since there are only 5 Nodes the remaining 3 elements of capData are redundant
//
//  Publishing Stream Notes:
//      "iost-rug-data" is publishing the state of each node check to see there are 3 values at 0 at the end
//                      If changes to the nodes are too quick this will overwhelm the 1 message per second
//                      limit imposed by Particle
//
//      "button-BB" is publishing the message "off" at setup, this may be redundant
//
//      rugNodePublishName is the stream under which triggering the nodes will publish a message which is limited to 1 per second
//                         any trigger of the nodes in between the buffer period defined by `interval` will be ignored
//
//  I've made a change here

//================================================================================
#define bitRead(value, bit) (((value) >> (bit)) & 0x01 ) // Register the pin that the button is connected to [DEFFINE MACROS == BAD]
//================================================================================
// Publishing Stream Names
const char* rugNodePublishName = "sarah_kettley_cap_rug_node";
const char* rugNodePublishData = "MESSAGE TO SEND WHEN NODE IS TRIGGERED";
//================================================================================
// External Device Pins: These do not change so marked constant
const int buttonPin = D6;
const int potPin = A2;
const int photonPins[] = {D0,D1,D2,D3,D4,D5,D7,D7,D7};
//================================================================================
bool pressed = false; // Register and Initialise a flag to hold current state.
int period = 100;     // Register a delay period to slow things down if needed.
int capData[] = {0,0,0,0,0,0,0,0};
byte arcByte;
//================================================================================
/// Timing variables: helping to ensure that publishing isn't constant
unsigned long previousMillis = 0; // will store last time data was published
const long interval = 1000;       // interval at which to publish in milliseconds
//================================================================================

void setup()
{
  digitalWrite(buttonPin, HIGH);

  for(int i = 0; i < 8; ++i)
  {
    pinMode (photonPins[i], OUTPUT);
  }

  pinMode (buttonPin, INPUT);
  pinMode (potPin, INPUT);
  bool pressed = false;

  Particle.publish("button-BB", "off");

  Serial.begin(9600);
  Serial1.begin(9600);
}

//================================================================================

void loop()
{
  unsigned long currentMillis = millis(); // get the uptime in milliseconds
  byte fred = arcByte;
  //================================================================================
  if (Serial1.available())
  {
    fred = Serial1.read();

    for (int i = 0; i < 8; ++i) // Read in the bits
    {
      capData[i] = bitRead(fred, i);
      digitalWrite(photonPins[i], capData[i]);

      if (capData[i] > LOW) // if Node is touched
      {
        if (currentMillis - previousMillis >= interval) // if the interval has passed
        {
          Particle.publish (rugNodePublishName, rugNodePublishData);
          previousMillis = currentMillis;
        }
      }
    }
    //================================================================================
    // Serial debugging

    Serial.print("[");

    for(int i = 0; i < 8; ++i)
    {
      Serial.print(capData[i]);

      if(i != 7)
      {
        Serial.print(",");
      }
    }

    Serial.print("]");
    Serial.print(" : ");
    Serial.print(fred);
    Serial.println();
  }

  // Check to see if change in state

  if(arcByte != fred)
  {
    //Particle.publish("iost-rug-data", String(fred));
  }

  // Archive previous states
  arcByte = fred;
  delay(period);
}

//================================================================================
// EOF

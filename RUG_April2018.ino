// IOSOFT
//
// Capacitant Rug Slave code for the Particle Photon
// Created by Sarah Kettley


//================================================================================
#define bitRead(value, bit) (((value) >> (bit)) & 0x01 ) // Register the pin that the button is connected to [DEFFINE MACROS == BAD]
//================================================================================
// External Device Pins: These do not change so marked constant
const int buttonPin = D6;
const int potPin = A2;
//================================================================================
bool pressed = false; // Register and Initialise a flag to hold current state.
int period = 100;     // Register a delay period to slow things down if needed.
int capData[] = {0,0,0,0,0,0,0,0};
int photonPins[] = {D0,D1,D2,D3,D4,D5,D7,D7,D7};
byte arcByte;
//================================================================================
//================================================================================
/// Timing variables: helping to ensure that publishing isn't constant
//================================================================================
unsigned long previousMillis = 0; // will store last time data was published
const long interval = 1000;       // interval at which to publish in milliseconds
//================================================================================
void setup()
{

    digitalWrite(buttonPin, HIGH);

    for(int i = 0; i < 8; ++i)
    {
        pinMode(photonPins[i], OUTPUT);
    }

    // Set the button pin as an input

    pinMode(buttonPin, INPUT);
    pinMode(potPin, INPUT);

    // Set the pressed flag to false

    bool pressed = false;

    // Set the initial state of subscriber
    // to off just in case.

    Particle.publish("button-BB", "off");

    Serial.begin(9600);
    Serial1.begin(9600);

}

//================================================================================

void loop()
{
    unsigned long currentMillis = millis(); // get the uptime in milliseconds
    byte fred = arcByte;

    if (Serial1.available())
    {

        fred = Serial1.read();

        // Read in the bits

        for(int i=0; i < 8; i++)
        {
            capData[i] = bitRead(fred, i);
            digitalWrite(photonPins[i], capData[i]);


            if (capData[i] > LOW)
            {
                if (currentMillis - previousMillis >= interval)
                {
                    Particle.publish (rugNodePublishName, rugNodePublishString);
                    previousMillis = currentMillis;
                }
            }
        }

        // Serial debugging

        Serial.print("[");

        for(int i=0; i < 8; i++)
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
            Particle.publish("iost-rug-data", String(fred));
        }

        // Archive previous states

       arcByte = fred;

    delay(period);
}

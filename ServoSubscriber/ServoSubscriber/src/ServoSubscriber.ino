/*
* Project ServoSubscriber
* Description:
* Author:
* Date:
*/
//==============================================================================
const char* rugNodePublishName = "rug_01";
//==============================================================================
void setup()
{
  pinMode(D7, OUTPUT);
  Particle.subscribe (rugNodePublishName, handle);
}
//==============================================================================
void loop()
{
}
//==============================================================================
// Subscription Function
void handle (const char* event, const char* data)
{
  rotateServo(D0, D1, 10, 1);
}
//==============================================================================
/** rotate a servo a number of times */
void rotateServo (int servo1Pin, int servo2Pin, int interval, int repeat)
{
    Servo firstServo, secondServo;
    firstServo.attach(servo1Pin);
    secondServo.attach(servo2Pin);
    for (int i = 0; i < repeat; ++i)
    {
         for (int degrees = 0; degrees < 180; ++degrees)
         {
          firstServo.write(degrees);
          secondServo.write(180-degrees);
          delay(interval);
         }
    }

  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D7, LOW);
  delay(500);
}
//==============================================================================

/*
* Project ServoSubscriber
* Description:
* Author:
* Date:
*/

void setup()
{
  Particle.subscribe ("rug01", mattsHandleFunc);
}

void loop()
{
}

// Subscription Function
void mattsHandleFunc (const char* event, const char* data)
{
  rotateServo(D0, 100, 3);
}

/** rotate a servo a number of times */
void rotateServo (int servoPin, int interval, int repeat)
{
  Servo rotatingServo, secondServo;
  rotatingServo.attach(servoPin);
  secondServo.attach(D1);
  for (int i = 0; i < repeat; ++i)
  {
    for (int degrees = 0; degrees < 180; ++degrees)
    {
      rotatingServo.write(degrees);
      secondServo.write(180-degrees);
      delay(interval);
    }
  }
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  delay(500);
  digitalWrite(D2, LOW);
  delay(500);
}

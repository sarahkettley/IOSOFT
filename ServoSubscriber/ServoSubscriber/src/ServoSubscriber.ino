/*
* Project ServoSubscriber
* Description:
* Author:
* Date:
*/

void setup()
{
  Particle.subscribe ("rug_node01", mattsHandleFunc, MY_DEVICES);
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
//  Servo rotatingServo, secondServo;
  // rotatingServo.attach(servoPin);
  // secondServo.attach(D1);
  // for (int i = 0; i < repeat; ++i)
  // {
  //   for (int degrees = 0; degrees < 180; ++degrees)
  //   {
  //     rotatingServo.write(degrees);
  //     secondServo.write(180-degrees);
  //     delay(interval);
  //   }
  // }
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D7, LOW);
  delay(500);
}

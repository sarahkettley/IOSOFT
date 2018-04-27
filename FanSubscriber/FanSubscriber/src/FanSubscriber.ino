/*
 * Project FanSubscriber
 * Description:
 * Author:
 * Date:
 */
//================================================================================
const char* rugNodePublishName = "ENTER_PUBLISH_NAME";
const int relaySwitchPin = D3; // Pin connected to switch pin of a relay
//================================================================================
void setup()
{
  pinMode(relaySwitchPin, OUTPUT);
  Particle.subscribe(rugNodePublishName, subsciberFunction)
}
//================================================================================
void loop()
{
}
//================================================================================
void subsciberFunction (const char* event, const char* data)
{
  // ENTER WHAT YOU WANT TO HAPPEN WHEN PUBLISH EVENT OCCURS HERE
}
//================================================================================

/*
This is for the clouds for Johns big table build. Very simple. Make lightening. Job done. Really.
Designed to work with a Carew Castle board.
*/

//For positive logic:
#define LEDPOLARITYON 0
#define LEDPOLARITYOFF 1

class Lightning
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin

  // These maintain the current state
  int state;                      // Define the state (0 = off, 1 = Pre-Flash, 2 Flash On, 3 Flash Off)
  unsigned long delayTillNextState;        // delay between states
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a candle flicker
  // and initializes the member variables and state
  public:
  Lightning(int pin)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
  state = 0;
  delayTillNextState = 0;  
  previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
         
    if(currentMillis - previousMillis >= delayTillNextState)
    {
      switch (state){
        case 0: // LEDCold: // Light off for a random time between 1 second and 4 seconds.
          digitalWrite(ledPin, LEDPOLARITYOFF);
          state = 1;
          delayTillNextState = random(3000, 8000);
          break;
          
        case 1: //LEDOnFlash: // Ballast Flash - Full power zap for 20mS (1/50th of a second)
          digitalWrite(ledPin, LEDPOLARITYON);
          state = 2;
          delayTillNextState = 30;
          break;
          
        case 2: //LEDoffFlash: // Ballast Flash Off - Zero for 1/50th of a second
          digitalWrite(ledPin, LEDPOLARITYOFF);
          state = 0;
          delayTillNextState = 0;
          if (int(random(3)) == 2){ // will it repeat again?
            state = 1;
            delayTillNextState = 80;
          }
          break;
        }
      previousMillis = currentMillis;  // Remember the time
  }
  
  }
};

Lightning ledA(0);
Lightning ledB(1);

void setup()
{
}
void loop()
{
  ledA.Update(); // Add a line like this for every LED you added.
  ledB.Update();
}
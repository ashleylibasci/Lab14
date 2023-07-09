#include "oled-wing-adafruit.h"
#include "Particle.h"
#include <Wire.h>

SYSTEM_THREAD(ENABLED);

#define yellowCounter D6
#define greenInterrupt D7

OledWingAdafruit display;

volatile int counter = 0;
volatile bool buttonPressed = false;
volatile bool interruptsEnabled = true;

void incrementCounter()
{
  if (interruptsEnabled)
  {
    counter++;
    buttonPressed = true;
  }
}

void toggleInterruptsState()
{
  if (interruptsEnabled)
  {
    detachInterrupt(yellowCounter);
    interruptsEnabled = false;
  }
  else
  {
    attachInterrupt(yellowCounter, incrementCounter, FALLING);
    interruptsEnabled = true;
  }
}

void setup()
{
  display.setup();
  display.clearDisplay();
  display.display();

  pinMode(yellowCounter, INPUT_PULLUP);
  pinMode(greenInterrupt, INPUT_PULLUP);

  attachInterrupt(yellowCounter, incrementCounter, FALLING);
  attachInterrupt(greenInterrupt, toggleInterruptsState, FALLING);
}

void loop()
{
  display.loop();

  if (buttonPressed)
  {
    delay(100);
    buttonPressed = false;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(counter);
    display.display();
  }
}
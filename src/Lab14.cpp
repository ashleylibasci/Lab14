/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/ashleylibasci/IoTFolderLabs/Lab14/src/Lab14.ino"
#include "oled-wing-adafruit.h"
#include "Particle.h"
#include <Wire.h>

void incrementCounter();
void toggleInterrupts();
void setup();
void loop();
#line 5 "/Users/ashleylibasci/IoTFolderLabs/Lab14/src/Lab14.ino"
SYSTEM_THREAD(ENABLED);

#define yellowCounter D6
#define greenInterrupt D7

OledWingAdafruit display;

volatile int counter = 0;
volatile bool buttonPressed = false;
bool interruptsEnabled = true;

void incrementCounter()
{
  if (interruptsEnabled)
  {
    counter++;
    buttonPressed = true;
  }
}

void toggleInterrupts()
{
  interruptsEnabled = !interruptsEnabled;
  if (interruptsEnabled)
  {
    attachInterrupt(yellowCounter, incrementCounter, FALLING);
  }
  else
  {
    detachInterrupt(yellowCounter);
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
  attachInterrupt(greenInterrupt, toggleInterrupts, RISING);
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
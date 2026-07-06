#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Input Pins
const int startButton = 2;
const int irSensor = 3;
const int capacitiveSensor = 4;

// Relay Output Pins
const int conveyorRelay = 5;
const int metalRelay = 6;
const int plasticRelay = 7;

bool systemRunning = false;

void setup()
{
  pinMode(startButton, INPUT);
  pinMode(irSensor, INPUT);
  pinMode(capacitiveSensor, INPUT);

  pinMode(conveyorRelay, OUTPUT);
  pinMode(metalRelay, OUTPUT);
  pinMode(plasticRelay, OUTPUT);

  digitalWrite(conveyorRelay, LOW);
  digitalWrite(metalRelay, LOW);
  digitalWrite(plasticRelay, LOW);

  lcd.begin(16, 2);
  lcd.print("Waste Sorting");
  lcd.setCursor(0, 1);
  lcd.print("Press START");
}

void loop()
{
  // Start the system
  if (digitalRead(startButton) == HIGH)
  {
    systemRunning = true;
    delay(300);
  }

  if (systemRunning)
  {
    // Conveyor ON
    digitalWrite(conveyorRelay, HIGH);

    lcd.clear();
    lcd.print("Conveyor ON");

    // Object detected by IR sensor
    if (digitalRead(irSensor) == HIGH)
    {
      digitalWrite(conveyorRelay, LOW);

      lcd.clear();
      lcd.print("Object Found");

      delay(500);

      // Plastic detected
      if (digitalRead(capacitiveSensor) == HIGH)
      {
        lcd.clear();
        lcd.print("Plastic Waste");

        digitalWrite(plasticRelay, HIGH);
        delay(2000);
        digitalWrite(plasticRelay, LOW);

        lcd.clear();
        lcd.print("Plastic Sorted");
        delay(1000);
      }
      else
      {
        lcd.clear();
        lcd.print("Metal Waste");

        digitalWrite(metalRelay, HIGH);
        delay(2000);
        digitalWrite(metalRelay, LOW);

        lcd.clear();
        lcd.print("Metal Sorted");
        delay(1000);
      }

      // Restart Conveyor
      digitalWrite(conveyorRelay, HIGH);
    }
  }
}
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 13, A1, A2, A3, A4);

const int metalPot = A0;
const int organicPot = A5;

const int redLED = 3;
const int greenLED = 4;
const int blueLED = 5;
const int whiteLED = 6;

const int metalMotor = 9;
const int organicMotor = 10;
const int inorganicMotor = 11;

int metalValue = 0;
int organicValue = 0;

int activeBin = 0;
unsigned long actionTime = 0;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  
  pinMode(metalMotor, OUTPUT);
  pinMode(organicMotor, OUTPUT);
  pinMode(inorganicMotor, OUTPUT);
  
  digitalWrite(whiteLED, HIGH);
  
  digitalWrite(metalMotor, LOW);
  digitalWrite(organicMotor, LOW);
  digitalWrite(inorganicMotor, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  
  lcd.begin(16, 2);
  lcd.print("Waste Sorter");
  delay(1500);
  lcd.clear();
  lcd.print("Ready");
  lcd.setCursor(0, 1);
  lcd.print("Place waste");
}

void loop() {
  if (activeBin != 0) {
    if (millis() - actionTime >= 3000) {
      digitalWrite(metalMotor, LOW);
      digitalWrite(organicMotor, LOW);
      digitalWrite(inorganicMotor, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      digitalWrite(blueLED, LOW);
      activeBin = 0;
      lcd.clear();
      lcd.print("Ready");
      lcd.setCursor(0, 1);
      lcd.print("Place waste");
    }
    return;
  }
  
  metalValue = analogRead(metalPot);
  organicValue = analogRead(organicPot);
  
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.print(metalValue);
  lcd.print(" O:");
  lcd.print(organicValue);
  lcd.print("    ");
  
  // Threshold 99% = 1013
  if (metalValue > 1013) {
    lcd.setCursor(0, 1);
    lcd.print("METAL! Bin 1   ");
    digitalWrite(redLED, HIGH);
    digitalWrite(metalMotor, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(organicMotor, LOW);
    digitalWrite(inorganicMotor, LOW);
    activeBin = 1;
    actionTime = millis();
  }
  else if (organicValue > 1013) {
    lcd.setCursor(0, 1);
    lcd.print("ORGANIC! Bin 2 ");
    digitalWrite(greenLED, HIGH);
    digitalWrite(organicMotor, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(metalMotor, LOW);
    digitalWrite(inorganicMotor, LOW);
    activeBin = 2;
    actionTime = millis();
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("INORGANIC Bin 3");
    digitalWrite(blueLED, HIGH);
    digitalWrite(inorganicMotor, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(metalMotor, LOW);
    digitalWrite(organicMotor, LOW);
    activeBin = 3;
    actionTime = millis();
  }
  
  delay(50);
}
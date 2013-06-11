#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo;
const int pingPin = 8;
int pos = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 2);
  servo.attach(9);
}

void loop() {
  lcd.clear();
  long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  lcd.setCursor(0, 0);
  lcd.print("Target Range:");
  lcd.setCursor(0, 1);
  lcd.print(inches);
  
  if(inches > 99)
  {
    lcd.setCursor(4, 1);
  }
  else if(inches < 100 && inches > 9)
  {
    lcd.setCursor(3, 1);
  }
  else if(inches < 10)
  {
    lcd.setCursor(2, 1);
  }
  lcd.print("in");
  delay(100);
  
  if (inches < 2 && inches > 0)
  {
    Serial.write(pos);
    for(pos = 0; pos < 180; pos += 1)
    {
      servo.write(pos);
      delay(15); 
    } 
    for(pos = 180; pos>=1; pos-=1)
    {                                
      servo.write(pos);
      delay(15);
    } 
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 4, 5, 6, 7);

const int redLED = 11;
const int greenLED = 13;
const int yellowLED = 12;
const int button = 10;
const int whiteLED = 2;
bool game = 0;
bool buttonPressed = 0;
int ran;
bool Timer;
unsigned long startTime;
unsigned long endTime;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("REACTION TIME");
  delay(1000);
  lcd.clear();
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop()
{
  while (game == 0){
    countdown();
  }
 
  while (buttonPressed == 0){
    digitalWrite(whiteLED, HIGH);
    if (digitalRead(button) == LOW && Timer) {
      buttonPressed = 1;
      endTime = millis();
      unsigned long duration = endTime - startTime;
      lcd.clear();
      lcd.print("Reaction Time=");
      lcd.setCursor(0, 1);
      lcd.print(duration);
      lcd.print("ms");
      digitalWrite(whiteLED, LOW);
    }
  }
  delay(2000);
  lcd.clear();
  digitalWrite(whiteLED, LOW);
  game = 0;
  buttonPressed = 0;
}

void countdown() {
  lcd.print("READY");
  digitalWrite(greenLED, HIGH);
  for (int i = 0; i < 10; i++) {
    if (digitalRead(button) == LOW) {
      warning();
      
      return;
    }
    delay(100);
  }
  digitalWrite(greenLED, LOW);
  lcd.clear();
 lcd.print("SET");
  digitalWrite(yellowLED, HIGH);
  for (int i = 0; i < 10; i++) {
    if (digitalRead(button) == LOW) {
      warning();
      
      return;
    }
    delay(100);
  }
  digitalWrite(yellowLED, LOW);
  lcd.clear();
  lcd.print("WAIT");
  ran = random(900, 4900);
  digitalWrite(redLED, HIGH);
  for (int i = 0; i < ran; i+=10){
    if (digitalRead(button) == LOW){
      warning();
     
     return;
    }
    delay(10);
  }
  lcd.clear();
  digitalWrite(redLED, LOW);
  startTime = millis();
  Timer = true;
  lcd.print("GO!");
  game = 1;
}

void warning() {
  lcd.clear();
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
   
  for (int i = 0; i < 6; i++) {
  digitalWrite(redLED, HIGH);
  lcd.print("TOO EARLY!");
  delay(100);
  digitalWrite(redLED, LOW);
  lcd.clear();
  delay(100);
  }
  game = 0;
  lcd.clear();
}
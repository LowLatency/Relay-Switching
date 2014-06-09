#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
// RS, E, 1 ,2 ,3 ,4 
/*
* LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 */


int relay[5] = {
  2,3,6,5,4};
long interval[5] = {
  10000,10000,10000,10000,10000};
//int relay[2] = {2,3};

int RelayState[5] = {
  0,0,0,0,0};
long previousMillis[5] = {
  0,0,0,0,0};
unsigned long currentMillis = millis();


//For keeping time
int minute = 0;
int seconds = 0;

//change patterns flag
int flag = 0;

void setup() {

  int i;  
  // initialize the digital pin as an output.
  for(i = 0 ; i < 5 ; i++){
    pinMode(relay[i], OUTPUT);
  }

  lcd.begin(0, 2);
  lcd.print("0 1 2 3 4");

}
void loop() {
  unsigned long currentMillis = millis();  

  //pattern switching
  if(millis() < 5000)
  {
    flag = 1;
  }
  if(millis() > 5000 && millis() < 10000)
  {
    flag = 2;
  }
  if(millis() > 10000 && millis() < 20000)
  {
    flag = 3;
  }
  if(millis() > 20000)
  {
    flag = 4;
  } 

  //pattern speeds
  switch (flag)
  {
  case 1:
    interval[0] = 1000;
    interval[1] = 1050;
    interval[2] = 100;
    interval[3] = 5000;
    interval[4] = 500;
    break;

  case 2:
    interval[0] = 1000;
    interval[1] = 1100;
    interval[2] = 150;
    interval[3] = 2000;
    interval[4] = 2025;
    break;

  case 3:
    interval[0] = 1000;
    interval[1] = 1020;
    interval[2] = 250;
    interval[3] = 300;
    interval[4] = 111;
    break;

  case 4:
    interval[0] = 1000;
    interval[1] = 1100;
    interval[2] = 200;
    interval[3] = 250;
    interval[4] = 2025;
    break;

  default:
    break;

  }

  //Display time since started on right side.
  if(millis()%60000 == 0 )
  {
    lcd.setCursor(14,0);
    lcd.print(minute);
    minute++; 
  }

  if(seconds < 10)
  {
    lcd.setCursor(15,1);
  }
  else
  {
    lcd.setCursor(14,1);
  }
  if(millis()%1000 == 0)
  {
    lcd.print(seconds);
    seconds++;
    if(seconds == 60)
    {
      seconds = 0;
    }
  }

  for(int i = 0 ; i < 5 ; i++ ){
    if(currentMillis - previousMillis[i] > interval[i]) {
      // save the last time you blinked the LED
      previousMillis[i] = currentMillis;  

      // if the LED is off turn it on and vice-versa:
      lcd.setCursor(i*2,1);
      if (RelayState[i] == LOW){
        RelayState[i] = HIGH;
        lcd.print("O");
      }
      else{
        RelayState[i] = LOW;
        lcd.print("I");
      }
      digitalWrite(relay[i], RelayState[i]);
    }
  }

}
/*
void TurnOn(int output, int time){ 
 //time in ms
 digitalWrite(relay[output], HIGH);
 delay(time);
 digitalWrite(relay[output], LOW);
 }
 */


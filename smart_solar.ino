
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int sens1 = A1;  // photoresistor 1 
int sens2 = A0;  //photoresistor 2 
int tolerance = 2;
int pos = 90;


void setup()
{
  myservo.attach(7);
  lcd.init(); 
  lcd.backlight();
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  Serial.begin(9600);
  myservo.write(pos);
  delay(1000);
 
}

void loop()
{

  int val1 = analogRead(sens1); 
  int val2 = analogRead(sens2);
  Serial.print("\n ------------------- \n ");
  Serial.print(String("left PR value: ")+String(val1));
  delay(500);

  Serial.print(" \n ------------------- \n ");
  Serial.print(String("right PR value: ")+String(val2));
  delay(500);

  if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    //do nothing if the difference between values is within the tolerancw  
    lcd.clear();                 
    lcd.setCursor(0, 0);         
    lcd.print("the difference ,");        // print message at (0, 0)
    lcd.setCursor(2, 1);         // move cursor to   (2, 1)
    lcd.print("between values"); // print message at (2, 1)
    delay(2000);                 // display the above for two seconds

    lcd.clear();                  // clear display
    lcd.setCursor(1, 0);          // move cursor to   (3, 0)
    lcd.print("is within");        // print message at (3, 0)
    lcd.setCursor(0, 1);          // move cursor to   (0, 1)
    lcd.print("the tolerance"); // print message at (0, 1)
    delay(2000);  

  } else {    

    if(val1 > val2)
    {
      pos = pos-10;
      lcd.clear();                 
      lcd.setCursor(0, 0);
      lcd.print(String("Sun on the right ") +String(val1));
      delay(2000);
    }
    if(val2 > val1) 
    {
      pos = pos+10;
      lcd.clear();                 
      lcd.setCursor(0, 0);
      lcd.print(String("Sun on the left ") + String(val2));
      delay(2000);
    }
  }
  
  if(pos > 170) { pos = 170; } 
  if(pos < 0) { pos = 0; } 

  myservo.write(pos); // write the position to servo
  delay(100);
  
}
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);//RS,EN,D4,D5,D6,D7
int voltageadjust =125;//starting initial variable output at 2.5V
float check =0;
void setup()
{
                pinMode(3,OUTPUT);//PWM output pin
                pinMode(4,INPUT);//button 1
                pinMode(5,INPUT);//button 2
                lcd.begin(16, 2);//number of characters on LCD
                // Print a logo message to the LCD.
                lcd.print("  CIRCUITDIGEST");
                lcd.setCursor(0, 1);
                delay (2500);
                delay (2500);
                lcd.clear();
                lcd.print("VOLTAGE= ");//printing name
                lcd.setCursor(9, 0);
}
void loop()
{
                float VOLTAGEVALUE = (analogRead(A0));//read ADC value at A0
                VOLTAGEVALUE = (VOLTAGEVALUE*5)/1024;//converting digital value to voltage
                if ((check > (VOLTAGEVALUE+0.05))|(check < (VOLTAGEVALUE-0.05)))
// if voltage change is higher or lower than 0.5 of previous value (to avoid fluctuations)
                {
                                lcd.print(VOLTAGEVALUE);
                                lcd.print("V ");
                                lcd.setCursor(9, 0);//go to position 9 on LCD
                                check = VOLTAGEVALUE;//store previous value
                }
                analogWrite(3,voltageadjust);//provide PWM at PIN3
                if (digitalRead(4)==LOW)
                {
                                if (voltageadjust<250)
                                {
                                                voltageadjust++;//if button1 is pressed and value is less than 250 increment the PWM value
                                                delay(30);
                                }
                }
                if (digitalRead(5)==LOW)
                {
                                if (voltageadjust>0)
                                {
                                                voltageadjust--;// if button2 is pressed and value is greater than 0 decrement the PWM value
                                                delay(30);
                                }
                }
                delay(200);
}
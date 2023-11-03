#include <Servo.h>       // servo library
#include "DHT.h"         //temperature and humidity sensor
#include <LiquidCrystal.h>   //for lcd
LiquidCrystal lcd(5,4,3,2,1,0);   //pins are defined for lcd 
#define DHTPIN 12         //setting the dht pin
#define DHTTYPE DHT11
#define SensorPin A2        //the ph meter analog output is connected with the arduino analog
unsigned long int avgValue;     //store the average value of the sensor feedback
float b;
int buf[10],temp;

DHT dht(DHTPIN, DHTTYPE);
Servo myservo;
int m=0;
int n=0;
int pos = 0;
int to=48;

void setup()
{
  lcd.begin(20,4);     // Print a message to the LCD.
  pinMode(6,OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Temp:24C,Rel-Hum:60%");
  lcd.setCursor(0,1);
  lcd.print("soil moisture:90"); // put your setup code here, to run once:
  lcd.setCursor(0,2);
  lcd.print("ph :- 7.5");
  lcd.setCursor(0,3);
  lcd.write("Automated system");
  
  dht.begin();                          //for dht to begin
  pinMode(A0, INPUT_PULLUP);           // Soil Moisture Sensor 1 PIN A0
  pinMode(A1, INPUT_PULLUP);           // Soil Moisture Sensor 1 PIN A1
  pinMode(8,OUTPUT);                             // Relay Module PIN D8
  Serial.begin(9600);                                  //  Sensor Buart Rate
  Serial.println("Ready ");   //testing the seril monitor
  myservo.attach(9);                                   //  Servo PIN D9
  digitalWrite(8, HIGH);      // Relay Normally Hight for OFF condition
  digitalWrite(6,HIGH);
 // lcd.clear();
  delay(500);
  
}

void loop()
{
// put your main code here, to run repeatedly:

 
float h = dht.readHumidity();                    // read humidity
float f = dht.readTemperature(true);             //read temperature in Fahrenheit

float value=0;
value = analogRead(SensorPin);
float phvalue = value*5.0/1024;           //converting analog into milivolt
phvalue= 3.5*phvalue;
Serial.print(" ph ");
Serial.print(phvalue,2);
delay(800);
lcd.clear();

 int m= analogRead(A0);                         // Soil Moisture Sensor 1 PIN A0
 int n= analogRead(A1);                           // Soil Moisture Sensor 1 PIN A1
 Serial.println(m);
 delay(10);
 Serial.println(n);
 delay(200);
 if (m>=980)
 {
  myservo.write(90);              // tell servo to go to position in variable 'pos'
 digitalWrite(8, LOW);       // Relay ON
 delay(1000);
 }
 else if(m<=970)
 {
  digitalWrite(8, HIGH);      // Relay ON
 }
 if (n>=980)
 {
  myservo.write(0);              // tell servo to go to position in variable 'pos'

 digitalWrite(8, LOW);       // Relay ON
 delay(1000);
 }
 else if(n<=970)
 {
  digitalWrite(8, HIGH);    // Relay OFF
 }

 else
 {
  digitalWrite(8, HIGH);   // Relay OFF
 }

}

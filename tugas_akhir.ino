#include <Servo.h>
Servo myservo,myservo2,servomagnet;
#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

//#define echoPin 10 //Echo Pin
//#define trigPin 12 //Trigger Pin
////IO Sensor   2
//#define echoPin2 6 //Echo Pin
//#define trigPin2 13 //Trigger Pin
#define trig3 A2
#define echo3 A1
//Buzzer
const int pinBuzzer = 2;
 float range3;
 long echotime; 
int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak
 
int maximumRange2 = 200;
int minimumRange2 = 00; 
long duration2, distance2; 
unsigned long blinkTime = 0;

void blink(void)
{  static int x = 0;                   /* Current LED state 0=>off, 1=>on
   blinkTime = millis();               /* Schedule next state change          */
}
void watch(void)
{  if (millis() - blinkTime >= 1)    /* If it's time to change state        */
      blink();                         /*  then go do it                      */
}
#define conveyor 4
#define relay 8  
int prosessampah=0;
unsigned long interval=8000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
unsigned long interval2=12000; // the time we need to wait
unsigned long previousMillis2=0; // millis() returns an unsigned long.
unsigned long interval3=14000; // the time we need to wait
unsigned long previousMillis3=0; // millis() returns an unsigned long.
  
bool ledState = false; // state variable for the LED
int pos = 0;
int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
int jenissampah;
void setup () {
 Serial.begin (9600);
//pinMode(trigPin, OUTPUT);
//pinMode(echoPin, INPUT); 
//pinMode(trigPin2, OUTPUT);
//pinMode(echoPin2, INPUT);
pinMode(conveyor, OUTPUT);
pinMode(relay,OUTPUT);
digitalWrite(conveyor,HIGH);
  myservo.attach(5);
  myservo2.attach(3);
  servomagnet.attach(9);
  myservo.write(15);
  myservo2.write(45);
  servomagnet.write(70);
  digitalWrite(relay,HIGH);
    Serial.begin(9600);  
 //myservo2.write(45);

//LCD PROGRAM
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("  Jenis Sampah : "); 
  lcd.setCursor(0, 1); 
  lcd.print("           ");

//Buzzer Program
pinMode(pinBuzzer, OUTPUT);
//sensor
 pinMode(trig3, OUTPUT); 
 pinMode(echo3, INPUT);
 digitalWrite(trig3, LOW);
 
}
void ultrasonic(){
digitalWrite(conveyor,HIGH);
//digitalWrite(trigPin, LOW);delayMicroseconds(2);
//digitalWrite(trigPin, HIGH);delayMicroseconds(10);
//digitalWrite(trigPin, LOW);
//duration = pulseIn(echoPin, HIGH);
// 
//digitalWrite(trigPin2, LOW);delayMicroseconds(2);
//digitalWrite(trigPin2, HIGH);delayMicroseconds(10);
//digitalWrite(trigPin2, LOW);
//duration2 = pulseIn(echoPin2, HIGH);
// 
////perhitungan untuk dijadikan jarak
//distance = duration/58.2;
//distance2 = duration2/58.2;
// 
//Serial.println(distance);Serial.print(" cm");
//Serial.println(distance2);Serial.print(" cmp");
//  if (distance <= 12 || distance2 <= 12){
//    prosessampah=0;
//    myservo2.write(45);
//  }
//  unsigned long currentMillis3 = millis();
//   if ((unsigned long)(currentMillis3 - previousMillis3) >= interval3) {
   delay(6000);
   prosessampah=0;
   myservo2.write(45);
 //  previousMillis3 = millis();
 //}
}
void bacadata(){
    digitalWrite(relay,HIGH);
    digitalWrite(conveyor,LOW);
  // unsigned long currentMillis = millis(); // grab current time
    servomagnet.write(70);
  delay(3000);
  val = analogRead(analogPin);  // read the input pin
  val = map(val, 0, 1023, 0, 255);
  Serial.println(val);  // save the "current" time
 // check if "interval" time has passed (1000 milliseconds)
 //if ((unsigned long)(currentMillis - previousMillis) >= interval) {
   prosessampah=1;
 
  
  if(prosessampah==1){
    if(val<=240){
    jenissampah=1;
   myservo2.write(0);
//  servomagnet.write(70);
  lcd.setCursor(0, 0);
  lcd.print("  Jenis Sampah : "); 
  lcd.setCursor(0, 1); 
  lcd.print("  Sampah basah  ");
  }
  else{
    jenissampah=0;
  myservo2.write(0);
  lcd.setCursor(0, 0);
  lcd.print("  Jenis Sampah : "); 
    lcd.setCursor(0, 1); 
  lcd.print(" Sampah kering  ");
  }
   if(jenissampah==1){
   myservo.write(95);
 }
 else{
  myservo.write(15);
 }
}
//Serial.print("currentMillis: ");
//Serial.println(previousMillis);

}
void sensor3(){
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  echotime= pulseIn(echo3, HIGH);
  range3= 0.0001*((float)echotime*340.0)/2.0;
if(range3<4){
  digitalWrite(pinBuzzer, HIGH);
    lcd.setCursor(0, 0); 
  lcd.print("  logam penuh  ");
    lcd.setCursor(0, 1); 
  lcd.print("Harap Kosongkan ");
}
else{
  digitalWrite(pinBuzzer, LOW);
//   lcd.setCursor(0, 0); 
//lcd.print("  Jenis Sampah : "); 
//    lcd.setCursor(0, 1); 
//  lcd.print("               ");
}

}
void sensormetal(){
  
  //servomagnet.write(70);
//  unsigned long currentMillis2 = millis(); // grab current time
// // / check if "interval" time has passed (1000 milliseconds)
//  if ((unsigned long)(currentMillis2 - previousMillis2) >= interval2) {
  delay(3000);
  servomagnet.write(0);  
  delay(2000);
  digitalWrite(relay,LOW);
  delay(1000);
  //previousMillis2 = millis();
  prosessampah=2; 
   //} 
Serial.print("currentMillis2  ");
Serial.println(previousMillis);

}
void loop () {
 if(prosessampah==0){
bacadata();  
 }
 if(prosessampah==1){
sensormetal();
}
if(prosessampah==2){
ultrasonic(); 

}
//  myservo.write(90);
//    myservo2.write(45);
//  delay(1500);
////
////  myservo.write(0);
//  myservo2.write(0);
//  delay(1500);
sensor3();
}

#include <LiquidCrystal.h>
#include <MQ2.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <EEPROM.h>
int addr = 1;
#include <SimpleTimer.h>
int buton = 9;
int butondurumu = 0; // variable for reading the pushbutton status
  
  
SimpleTimer timer;
void(* resetFunc) (void) = 0;
void OnceOnlyTask() {
for (int z= 0 ; z < 10000 ; z = z+1 ){
for (int i = 0; i < 3000; i = i + 1){ 
tone(10, i,20);   } 
tone(10, 3000,200); 
for (int j = 30000; j > 0; j = j - 1){
  
  
}
  
Serial.println("Sure Bitti");
}
}
  
void DigitalClockDisplay() {
lcd.clear();
lcd.setCursor(4,0);
int h,m,s;
s = millis() / 1000;
m = s / 60;
h = s / 3600;
s = s - m * 60;
m = m - h * 60;
Serial.print(h);
lcd.print(h);
printDigits(m);
printDigits(s);
Serial.println();
}
  
void printDigits(int digits) {
Serial.print(":");
lcd.print(":");
  
if(digits < 10){ Serial.print('0'); 
lcd.print('0');} lcd.print(digits); 
Serial.print(digits); }   
void setup() { 
Serial.begin(9600); 
lcd.begin(16, 2); 
pinMode(buton, INPUT);   // this is where the "polling" occurs 
int oku = EEPROM.read(addr); 
unsigned long alarm =oku*60; 
alarm = alarm * 1000; 
timer.setTimeout(alarm, OnceOnlyTask); 
timer.setInterval(1000, DigitalClockDisplay); 
lcd.clear(); lcd.print(oku); 
lcd.print ("Dk.SONRA ALARM"); 
lcd.setCursor(0,1);
 lcd.print (" AKTIF OLACAK");   
delay(5000); 
}   
void loop() {   
timer.run();   
butondurumu = digitalRead(buton);   
int a= analogRead(A0);   
int zaman = map(a ,0,1023,1,120);   
lcd.setCursor(0,1); 
lcd.print(zaman); 
lcd.print (" DK.ALARM CAL"); 
Serial.println (zaman,DEC); 
if (butondurumu == HIGH) {   
EEPROM.write(addr,zaman ); 
for (int g=0; g>5;g++){
tone(10,2000,100);
delay(200);
tone(10,2000,100);
}
resetFunc(); //call reset
}
  
int gaz= analogRead(A1); // Doğal Gaz veya LPG sensörü Herhangi birisi olabilir .
///////////////////////////////////
Serial.println(gaz);
delay(1000);
if (gaz >100 ){ // ELEKTİRİĞİ ve GAZI KESTİRMEK İÇİN
  
digitalWrite (6, HIGH);
digitalWrite (7, HIGH);
lcd.clear();
lcd.setCursor(0,0);
lcd.print (" TEHLIKE");
Serial.println("TEHLIKE");
  
lcd.setCursor(0,1);
lcd.print ("GAZ SEVIYE:");
lcd.print (gaz);
  
for (int z= 0 ; z < 10000 ; z = z+1 ){
for (int i = 0; i < 3000; i = i + 1){ 
tone(10, i,20);   } 
tone(10, 3000,200); 
for (int j = 30000; j > 0; j = j - 1) {
  
  
}
}
delay (1000);
}
digitalWrite (6, LOW);
digitalWrite (7, LOW);
  
  
}

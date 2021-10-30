#include <Servo.h>
Servo myservo;
#define yesilLED 12
#define kirmiziLED 13


void setup() {
Serial.begin(9600);
myservo.attach(9);
digitalWrite(yesilLED, 0);
digitalWrite(kirmiziLED, 0);
}


void loop() {
int sensorIceri1 = analogRead(A0);
int sensorIceri2 = analogRead(A1);
int sensorIceri3 = analogRead(A2);
int sensorDisari = analogRead(A4);

    if (sensorIceri1 > 800){
      Serial.print("1B");       //1. otopark boşken 1B sollıcak
    }
    else {
      Serial.print("1D");     //1. otopark dolu iken 1D yolluıcak
    }
    
    if (sensorIceri2 > 800){
      Serial.print("2B");     //2. otopark boş iken 2B 
    }
    else {
      Serial.print("2D");     //2. otopark dolu iken 2D 
    }
    
    if (sensorIceri3 > 800){    //3. otopark boş iken 3B
      Serial.print("3B");
    }
    else {
      Serial.print("3D");       //3. otopark dolu iken 3D
    }

    if (sensorIceri1 < 800 && sensorIceri2 < 800 && sensorIceri3 < 800){
      digitalWrite(yesilLED, 0);
      digitalWrite(kirmiziLED, 1);
      myservo.write(120);
    }
    else {
      digitalWrite(yesilLED, 1);
      digitalWrite(kirmiziLED, 0);

        if (sensorDisari < 800){
          myservo.write(10);
          delay(250);
        }
        else{
          myservo.write(120);
        }
    }

delay(100);

}

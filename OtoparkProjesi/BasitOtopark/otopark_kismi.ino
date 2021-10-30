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

  if ((sensorIceri1 > 800) || (sensorIceri2 > 800) || (sensorIceri3 > 800)){
    digitalWrite(yesilLED, 1);
    digitalWrite(kirmiziLED, 0);
    
    Serial.println("BOS");
    
      if (sensorDisari < 799){
        myservo.write(10);
        Serial.println("Kapi Acik");
        delay(250);
      }
        else if (sensorDisari >= 800){
          myservo.write(120);
          Serial.println("Kapi Kapali");
          delay(250);
          }
        }
    else if ((sensorIceri1 < 799) && (sensorIceri2 < 799) && (sensorIceri3 < 799)){
      digitalWrite(yesilLED, 0);
      digitalWrite(kirmiziLED, 1);
    
      Serial.println("DOLU");
      Serial.println("Kapi Acilmaz");
      myservo.write(120);
      }

delay(1000);

}

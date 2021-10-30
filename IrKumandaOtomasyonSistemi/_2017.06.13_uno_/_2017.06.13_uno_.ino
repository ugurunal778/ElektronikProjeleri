/* KÜTÜPHANELER TANIMLANIYOR */
#include "DHT.h"
#include <IRremote.h>
#include <Wire.h>
#include <DS1307new.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(16, 17, 12, 13, 14, 15);  //E, RS, D4, D5, D6, D7

/* SICAKLIK NEM SENSÖRÜ TANIMLANIYOR */
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/* KUMANDA TUŞLARI İÇİN KODLAR TANIMLANYOR */
#define CH1 0xFFA25D          //1
#define CH 0xFF629D           //2
#define CH2 0xFFE21D          //3
#define PREV 0xFF22DD         //4
#define NEXT 0xFF02FD         //5
#define PLAYPAUSE 0xFFC23D    //6
#define VOL1 0xFFE01F         //7
#define VOL2 0xFFA857         //8
#define EQ 0xFF906F           //9
#define BUTON0 0xFF6897       //10
#define BUTON100 0xFF9867     //11
#define BUTON200 0xFFB04F     //12
#define BUTON1 0xFF30CF       //13
#define BUTON2 0xFF18E7       //14
#define BUTON3 0xFF7A85       //15
#define BUTON4 0xFF10EF       //16
#define BUTON5 0xFF38C7       //17
#define BUTON6 0xFF5AA5       //18
#define BUTON7 0xFF42BD       //19
#define BUTON8 0xFF4AB5       //20
#define BUTON9 0xFF52AD       //21

/* DS1307 ADRESLERİ */
uint16_t startAddr = 0x0000;
uint16_t lastAddr;
uint16_t TimeIsSet = 0xaa55;

/* KUMANDA PİNİ BELİRLENİP DECODE EDİLİYOR */
int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
/* İNT DEGERİNDE DEĞİŞKENLER VE RÖLELERİN PİNLERİ TANIMLANIYOR*/

//---------------1. MODUL--------------------//
#define role1 2     //masa, klavye -      buton1 (in4)
#define role2 3     //            n   -      buton2 (in5)
#define role3 4     //             -      buton3 (in6)
#define role4 5     //             -      buton4 (in8)
#define role5 6     //salon ışığı            -      buton5 (in1)

#define r 9
#define g 10
#define b 11

//--------------RÖLE VE SAYAC DEĞİŞKENLERİ TANIMLANIYOR---------------------------//
int
r1, r2, r3, r4, r5, yil, Asayac, Ysayac, ranNum;

//-----------------------------------------------------------------------//
void setup() {
  Serial.begin(9600);     //SERİ HABERLEŞME HIZI 9600 BAUD RATE OLARAK BELİRLENİYOR

  /* DHT VE LCD HABERLEŞMESİ BAŞLATILIYOR VE LCD ARKA IŞIK AKTİF EDİLİYOR */
  dht.begin();
  lcd.begin(20, 4);

  /* röle ÇIKIŞLARI AYARLANIYOR */
  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  pinMode(role3, OUTPUT);
  pinMode(role4, OUTPUT);
  pinMode(role5, OUTPUT);

  /* RÖLELERE LOJİK 1 VERİLEREK BAŞLANGIÇTA KAPATILMASI SAĞLANIYOR*/
  digitalWrite(role1, 1);
  digitalWrite(role2, 1);
  digitalWrite(role3, 1);
  digitalWrite(role4, 1);
  digitalWrite(role5, 1);
  delay(10);

  irrecv.enableIRIn();

  //----------------------SAAT AYARLANIYOR--------------------//
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));


  if (TimeIsSet != 0xaa55) {
    RTC.stopClock();
    RTC.fillByYMD(2017, 06, 14);
    RTC.fillByHMS(18, 21, 00);                                     //  BU KISIM SADECE SAAT AYARLANIRKEN AKTİF EDİLECEKTİR
    RTC.setTime();
    TimeIsSet = 0xaa55;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
  }
  else {
    RTC.getTime();
  }
}


void kirmizi(){
for (int R = 0; R < 255; R++) {
  analogWrite(r, R);
  delay(5);
}
for (int R = 255; R > 0; R--) {
  analogWrite(r, R);
  delay(5);
}
}


void yesil(){
for (int G = 0; G < 255; G++) {
  analogWrite(g, G);
  delay(5);
}
for (int G = 255; G > 0; G--) {
  analogWrite(g, G);
  delay(5);
}
}


void mavi(){
for (int B = 0; B < 255; B++) {
  analogWrite(b, B);
  delay(5);
}
for (int B = 255; B > 0; B--) {
  analogWrite(b, B);
  delay(5);
}
}


void sari(){
for (int S = 0; S < 255; S++) {
  analogWrite(r, S);
  analogWrite(g, S);
  delay(5);
}
for (int S = 255; S > 0; S--) { //SARI'DAN TURKUAZ'A GEÇİŞ
  analogWrite(r, S);
  analogWrite(g, S);
  delay(5);
}
}


void turkuaz(){
for (int T = 0; T < 255; T++) {
  analogWrite(b, T);
  analogWrite(g, T);
  delay(5);
}
for (int T = 255; T > 0; T--) { //TURKUAZ'DAN MOR'A GEÇİŞ
  analogWrite(g, T);
  analogWrite(b, T);
  delay(5);
}
}


void mor(){
for (int M = 0; M < 255; M++) {
  analogWrite(r, M);
  analogWrite(b, M);
  delay(5);
}
for (int M = 255; M > 0; M--) { //TURKUAZ'DAN MOR'A GEÇİŞ
  analogWrite(r, M);
  analogWrite(b, M);
  delay(5);
}
}


void beyaz(){
for (int Be = 0; Be < 255; Be++) {
  analogWrite(r, Be);
  analogWrite(g, Be);
  analogWrite(b, Be);
  delay(5);
}
for (int Be = 255; Be > 0; Be--) {
  analogWrite(r, Be);
  analogWrite(g, Be);
  analogWrite(b, Be);
  delay(5);
}
}


void loop() {

  /*DHT22 OKUNUYOR*/
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //-----------------SAAT VE TARİH OKUNUYOR------------------------//
  RTC.getTime();

  //----------------SAAT İLE GECE AYDINLATMASI KONTROL EDİLİYOR----------------------//
  if (RTC.hour > 19 || RTC.hour < 6) {
    digitalWrite (role3, 0);
  }
  else if (RTC.hour >= 6 && RTC.hour <= 19) {
    digitalWrite (role3, 1);
  }

  //---------------IR KUMANDA İLE AÇMA- KAPATMA KOMUTLARI--------------------//
  if (irrecv.decode(&results)) {
    if (results.value == BUTON1) {
      digitalWrite(role1, !digitalRead(role1));     //ARKA
    }
    else if (results.value == BUTON2) {
      digitalWrite(role2, !digitalRead(role2));     //AMPUL ((DEVRE DIŞI))
    }
    else if (results.value == BUTON3) {
      digitalWrite(role3, !digitalRead(role3));     //SALON VE AMFİ LEDİ
    }
    else if (results.value == BUTON4) {
      digitalWrite(role4, !digitalRead(role4));     //RGB LEDLER
    }
    else if (results.value == BUTON5) {
      digitalWrite(role5, !digitalRead(role5));     //KLAVYE VE MASA
    }
    else if (results.value == CH1) {
      digitalWrite(role1, 1);
      digitalWrite(role2, 1);
      digitalWrite(role3, 1);
    }
    else if (results.value == CH2) {
      digitalWrite(role1, 0);
      digitalWrite(role2, 0);
      digitalWrite(role3, 0);
    }
    else if (results.value == VOL1) {
      digitalWrite(role1, 1);
      digitalWrite(role2, 1);
      digitalWrite(role3, 1);
      digitalWrite(role4, 1);
      digitalWrite(role5, 1);
    }
    else if (results.value == VOL2) {
      digitalWrite(role1, 0);
      digitalWrite(role2, 0);
      digitalWrite(role3, 0);
      digitalWrite(role4, 0);
      digitalWrite(role5, 0);
    }
    irrecv.resume();
  }
  delay(50);

  /*--------------------RÖLELERİN DURUMLARI OKUNUP ATANIYOR (RÖLELER LOJİK 0 İLE TETİKLENDİĞİ İÇİN TERSİ YAZDIRILIYOE)-------------------------*/
  r1 = !digitalRead(role1);
  r2 = !digitalRead(role2);
  r3 = !digitalRead(role3);
  r4 = !digitalRead(role4);
  r5 = !digitalRead(role5);

  /*--------------------------------LCD YAZILIYOR----------------------------------*/
  if (Ysayac < 40) {
    if (Ysayac == 0) {
      lcd.clear();
    }

    if (Ysayac > 0) {
      //SICAKLIK SENSÖRÜ YAZILIYOR
      if (isnan(t) || isnan(h)) {
        lcd.setCursor(0, 2);
        lcd.print("SENSOR OKUNAMIYOR");
      }
      else {
        lcd.setCursor(0, 2);
        lcd.print("SICAKLIK: "); lcd.print(t); lcd.print("C");
        lcd.setCursor(0, 3);
        lcd.print("NEM ORAN: "); lcd.print(h); lcd.print("%");
      }

      //SAAT VE TARİH YAZILIYOR
      if (RTC.hour < 10) {
        lcd.setCursor(0, 0); lcd.print("0"); lcd.print(RTC.hour, DEC); lcd.print(":");
      }
      else {
        lcd.setCursor(0, 0); lcd.print(RTC.hour, DEC); lcd.print(":");
      }

      if (RTC.minute < 10) {
        lcd.setCursor(3, 0); lcd.print("0"); lcd.print(RTC.minute, DEC); lcd.print(":");
      }
      else {
        lcd.setCursor(3, 0); lcd.print(RTC.minute, DEC); lcd.print(":");
      }

      if (RTC.second < 10) {
        lcd.setCursor(6, 0); lcd.print("0"); lcd.print(RTC.second, DEC);
      }
      else {
        lcd.setCursor(6, 0); lcd.print(RTC.second, DEC);
      }

      if (RTC.day < 10) {
        lcd.setCursor(0, 1); lcd.print("0"); lcd.print(RTC.day, DEC); lcd.print("/");
      }
      else {
        lcd.setCursor(0, 1); lcd.print(RTC.day, DEC); lcd.print("/");
      }

      if (RTC.month < 10) {
        lcd.setCursor(3, 1); lcd.print("0"); lcd.print(RTC.month, DEC); lcd.print("/");
      }
      else {
        lcd.setCursor(3, 1); lcd.print(RTC.month, DEC); lcd.print("/");
      }

      lcd.setCursor(6, 1); yil = (RTC.year); lcd.print(yil - 2000);

      lcd.setCursor(8, 0); //GÜNÜ YAZILACAĞI KONUM
      //HAFTANIN GÜNLERİ YAZILIYOR
      switch (RTC.dow) {
        case 0:
          lcd.print(" (:PAZAR:)");
          break;
        case 1:
          lcd.print("|-PAZARTESI|");
          break;
        case 2:
          lcd.print("|<:>SALI<:>|");
          break;
        case 3:
          lcd.print("|*CARSAMBA*|");
          break;
        case 4:
          lcd.print("|*PERSEMBE*|");
          break;
        case 5:
          lcd.print("|*_*CUMA*_*|");
          break;
        case 6:
          lcd.print("|*CUMARTESI|");
          break;
      }
      //----------------GÜN İÇİN ÇERÇEVE--------------------------//
      lcd.setCursor(8, 1); lcd.print("+----------+");
    }
  }

  //AÇIK VEYA KAPALI RÖLELER GÖSTERİLİYOR
  if (Ysayac >= 40) {
    if (Ysayac == 40) {
      lcd.clear();
    }
    if (Ysayac > 40) {
      lcd.setCursor(0, 0); lcd.print("ARKA LED: "); lcd.print(r1); lcd.print("   ranNum");
    }
    if (Ysayac > 42) {
      lcd.setCursor(0, 1); lcd.print("SALON LEDI: "); lcd.print(r3); lcd.print("      "); lcd.print(ranNum);
    }
    if (Ysayac > 44) {
      lcd.setCursor(0, 2); lcd.print("RGB LEDLER: "); lcd.print(r4);
    }
    if (Ysayac > 46){
      lcd.setCursor(0, 3); lcd.print("MASA LEDI: "); lcd.print(r5);
    }
  }

  Asayac++;
  if (Asayac == 2) {
    Ysayac++;
    Asayac = 0;
    if (Ysayac == 80) {
      Ysayac = 0;
    }
  }
  if (r4 == 1){
  if (Ysayac == 0 || Ysayac == 7 || Ysayac == 14 || Ysayac == 21 || Ysayac == 28 || Ysayac == 35 || Ysayac == 42 || Ysayac == 49 || Ysayac == 56 || Ysayac == 63 || Ysayac == 70 || Ysayac == 77){
    kirmizi();
  }
  if (Ysayac == 1 || Ysayac == 8 || Ysayac == 15 || Ysayac == 22 || Ysayac == 29 || Ysayac == 36 || Ysayac == 43 || Ysayac == 50 || Ysayac == 57 || Ysayac == 64 || Ysayac == 71 || Ysayac == 78){
    yesil();
  }
  if (Ysayac == 2 || Ysayac == 9 || Ysayac == 16 || Ysayac == 23 || Ysayac == 30 || Ysayac == 37 || Ysayac == 44 || Ysayac == 51 || Ysayac == 58 || Ysayac == 65 || Ysayac == 72 || Ysayac == 79){
    mavi();
  }
  if (Ysayac == 3 || Ysayac == 10 || Ysayac == 17 || Ysayac == 24 || Ysayac == 31 || Ysayac == 38 || Ysayac == 45 || Ysayac == 52 || Ysayac == 59 || Ysayac == 66 || Ysayac == 73 || Ysayac == 80){
    sari();
  }
  if (Ysayac == 4 || Ysayac == 11 || Ysayac == 16 || Ysayac == 25 || Ysayac == 32 || Ysayac == 39 || Ysayac == 46 || Ysayac == 53 || Ysayac == 60 || Ysayac == 67 || Ysayac == 74){
    turkuaz();
  }
  if (Ysayac == 5 || Ysayac == 12 || Ysayac == 17 || Ysayac == 26 || Ysayac == 33 || Ysayac == 40 || Ysayac == 47 || Ysayac == 54 || Ysayac == 61 || Ysayac == 68 || Ysayac == 75){
    mor();
  }
  if (Ysayac == 6 || Ysayac == 13 || Ysayac == 18 || Ysayac == 27 || Ysayac == 34 || Ysayac == 41 || Ysayac == 48 || Ysayac == 55 || Ysayac == 62 || Ysayac == 69 || Ysayac == 76){
    beyaz();
  }
}
}

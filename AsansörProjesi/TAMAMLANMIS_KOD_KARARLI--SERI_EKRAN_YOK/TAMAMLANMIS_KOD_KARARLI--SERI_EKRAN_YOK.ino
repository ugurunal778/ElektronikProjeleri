int
buton0 = 2,         //BUTONLAR TANIMLANIYOR
buton1 = 3,
buton2 = 4,

kat0 = A0,           //LDRLER TANIMLANIYOR
kat1 = A1,
kat2 = A2,

m1 = 10,              // MOTOR UCLARI TANIMLANIYOR
m2 = 11,


B = 8,              //DİSPLAY BACAKLARI TANIMLANIYOR
A = 9,
F = 12,
G = 13,
C = 7,
D = 6,
E = 5,
//---------------------------DEĞİŞKELER TANIMLANIYOR--------------------//
buton0durum = 0,    //BUTONLAR OKUNUP BU DEĞERE ATAACAK
buton1durum = 0,
buton2durum = 0,

buton0sond = 0,     // BUTONLARIN SON DURUMLARI KAYDEDİLECEK
buton1sond = 0,
buton2sond = 0,

buton0sayac = 0,    // BUTONLARA KAÇ DEFA BASILDIĞI SAKLANACAK
buton1sayac = 0,
buton2sayac = 0,

kat0buton = 0,    //
kat1buton = 0,
kat2buton = 0,

kat0deger = 0,
kat1deger = 0,
kat2deger = 0,
katdurum = 0;

void setup() {

  //--------------------I/O'LAR AYARLANIYOR------------------//
  pinMode(buton0, INPUT);
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);

  pinMode(kat0, INPUT);
  pinMode(kat1, INPUT);
  pinMode(kat2, INPUT);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  //--------------------BAŞLANGIÇ SET AYARI YAPILIYOR-------//
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);

  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
}


//-------------------MOTOR DURUMLARI AYARLANIYOR-------------------------------//
void ileri() {                              // MOTORU İLERİ SÜRMEK İÇİN BU KISIM DEVREYE GİRECEK
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
}

void geri() {                               // MOTORU GERİ SÜRMEK İÇİN BU KISIM DEVREYE GİRECEK
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
}

void dur() {                                // MOTORU DURDURMAK İÇİN BU KISIM DEVREYE GİRECEK
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
}

void loop() {

      // OKUNAN DEGERLER BELİRLENEN DEĞİŞKENLERE ATANIYOR

  buton0durum = digitalRead (buton0); 
    if (buton0durum != buton0sond){
      if (buton0durum == HIGH){
        buton0sayac++;
      }
    }
      buton0sond = buton0durum ;
      if (buton0sayac == 1 ){
        kat0buton = HIGH;
      }
      else {
        kat0buton = LOW;
      }

    
  buton1durum = digitalRead (buton1); 
    if (buton1durum != buton1sond){
      if (buton1durum == HIGH){
        buton1sayac++;
      }
    }
      buton1sond = buton1durum ;
      if (buton1sayac == 1 ){
        kat1buton = HIGH;
      }
      else {
        kat1buton = LOW;
      }

    
  buton2durum = digitalRead (buton2); 
    if (buton2durum != buton2sond){
      if (buton2durum == HIGH){
        buton2sayac++;
      }
    }
      buton2sond = buton2durum ;
      if (buton2sayac == 1){
        kat2buton = HIGH;
      }
      else {
        kat2buton = LOW;
      }

  kat0deger = analogRead (kat0);
  kat1deger = analogRead (kat1);
  kat2deger = analogRead (kat2);
  //-----------------------------ASANSOR KONTROL EDILIYOR--------------------------//

  //----------------------------ZEMIN KATA BASILDIGINDA------------------------------------------//
  if (kat0buton == HIGH && katdurum != 0) {

    if (katdurum == 1) {    
      if (kat0deger > 500) {        
      Serial.println("iniyor");  
        geri();
      }
      else if (kat0deger < 500) {
      Serial.println("duruyor");  
      buton0sayac = 0;
        dur();
      }
    }
    
    else if (katdurum == 2) {
      if (kat0deger > 500) {
      Serial.println("iniyor");
        geri();
      }
      else if (kat0deger < 500) {
      Serial.println("duruyor");   
      buton0sayac = 0;
      dur();
      }
    }
  }
  if (kat0deger < 500) {
    katdurum = 0;
  }


  //-------------------------------BIRINCI KATA BASILDIGINDA----------------------------------------//
  if (kat1buton == HIGH && katdurum != 1) {
    if (katdurum == 0) {
      if (kat1deger > 200) {
      Serial.println("cikiyor");
        ileri();
      }
      else if (kat1deger < 200) {
      Serial.println("duruyor");
      buton1sayac = 0;
        dur();
      }
    }
    
    else if (katdurum == 2) {
      if (kat1deger > 200) {
      Serial.println("iniyor");
        geri();
      }
      else if (kat1deger < 200) {
      Serial.println("duruyor");
      buton1sayac = 0;
        dur();
      }
    }
  }
  if (kat1deger < 200) {
    katdurum = 1;
  }


  //-----------------------------------IKINCI KATA BASILDIGINDA-----------------------------------------//
  if (kat2buton == HIGH && katdurum != 2) {

    if (katdurum == 0) {
      if (kat2deger > 700) {        
      Serial.println("cikiyor");
        ileri();
      }
      else if (kat2deger < 700) {        
      Serial.println("duruyor");
      buton2sayac = 0;
        dur();
      }
    }
    
    else if (katdurum == 1) {
      if (kat2deger > 700) {        
      Serial.println("cikiyor");
        ileri();
      }
      else if (kat2deger < 700){        
      Serial.println("duruyor");
      buton2sayac = 0;
        dur();
      }
    }
  }
  if (kat2deger < 700) {
    katdurum = 2;
  }

  //--------------------------SERİ EKRAN VE DİSPLAY İÇİN KAT BİLGİLERİ YAZILIYO-------------------------//
  if (katdurum == 0) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
  }
  else if (katdurum == 1) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }
  else if (katdurum == 2) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }
}

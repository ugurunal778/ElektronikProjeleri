/*
Arduino ile TFT LCD ekran arasında bağlantı yepmaya gerek yoktur direk Arduino Mega'nın üzerine oturtularak bağlantı tamamlanır.
LCD'deki saati ayarlamaya gerek yoktur saat kendisini otomatik olarak bilgisayardan ayarlar
*/

#include <TFT_HX8357.h> // tft lcd kütüphanesi ekleniyor

TFT_HX8357 tft = TFT_HX8357();       

#define TFT_GREY 0x5AEB

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // saat, dakika, saniye ile x,y değişkenleri tanımlanıyor
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120; // saat, dakika, saniye ile x,y koordinatları tanımlanıyor
int16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
uint32_t targetTime = 0;                    // 1 samiyelik zaman aşımı

uint16_t xpos; // saatin x pozisyonu

uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time
boolean initial = 1;

void setup(void) {
  tft.init();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_RED, TFT_BLACK);  // yazı ve yazıların arka plan renkleri

  // Draw clock face
  xpos = tft.width() / 2; // xpos değişkeni ekranın ortasına ayarlanıyor
  tft.fillCircle(40, 40, 20, TFT_GREEN);
  tft.fillCircle(xpos, 120, 118, TFT_BLUE);
  tft.fillCircle(xpos, 120, 110, TFT_GREY);

  // Draw 12 lines
  for (int i = 0; i < 360; i += 30) {
    sx = cos((i - 90) * 0.0174532925);
    sy = sin((i - 90) * 0.0174532925);
    x0 = sx * 114 + xpos;
    yy0 = sy * 114 + 120;
    x1 = sx * 100 + xpos;
    yy1 = sy * 100 + 120;

    tft.drawLine(x0, yy0, x1, yy1, TFT_GREEN);
  }

  for (int i = 0; i < 360; i += 6) {
    sx = cos((i - 90) * 0.0174532925);
    sy = sin((i - 90) * 0.0174532925);
    x0 = sx * 102 + xpos;
    yy0 = sy * 102 + 120;
    
    tft.drawPixel(x0, yy0, TFT_WHITE);

    if (i == 0 || i == 180) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
    if (i == 90 || i == 270) tft.fillCircle(x0, yy0, 2, TFT_WHITE);
  }

  tft.fillCircle(xpos, 121, 3, TFT_WHITE);


  tft.drawCentreString("LEVENT TURKLER - SIST. ANALIZI", xpos, 260, 4);
  tft.drawCentreString("MURAT KISKANC - SERKAN AKTAS", xpos, 290, 4);

  targetTime = millis() + 1000;
}
void yanik(){          //yanik komutu geldiğinde bu kısım devreye girer
   tft.fillCircle(40, 40, 20, TFT_GREEN);
   tft.drawCentreString("AKTIF", 40, 70, 4); 
}

void sonuk() {        //sonuk komutu geldiğinde bu kısım devreye girer
   tft.fillCircle(40, 40, 20, TFT_GREY);
   tft.drawCentreString("PASIF", 40, 70, 4);
}
void loop() {
  if (targetTime < millis()) {
    targetTime = millis() + 1000;
    ss++;              // saniyeyi artır
    
    if (ss == 60) {
      ss = 0;
      mm++;            // dakikayı artır
      if (mm > 59) {
        mm = 0;
        hh++;          // saati artır
        if (hh > 23) {
          hh = 0;
        }
      }
    }
     if (ss < 6) {      //ledin 5sn aralıkla yanıp sönmesini sağlar
      yanik();
     }
     else if (ss > 5 && ss <=10){
      sonuk();
     }
     else if (ss > 10 && ss <=15){
      yanik();
     }
     else if (ss > 15 && ss <=20){
      sonuk();
     }
     else if (ss > 20 && ss <=25){
      yanik();
     }
     else if (ss > 25 && ss <=30){
      sonuk();
     }
     else if (ss > 30 && ss <=35){
      yanik();
     }
     else if (ss > 35 && ss <=40){
      sonuk();
     }
     else if (ss > 40 && ss <=45){
      yanik();
     }
     else if (ss > 45 && ss <=50){
      sonuk();
     }
     else if (ss > 50 && ss <=55){
      yanik();
     }
     else if (ss > 55){
      sonuk();
     }
    
    

    sdeg = ss * 6; 
    mdeg = mm * 6 + sdeg * 0.01666667;
    hdeg = hh * 30 + mdeg * 0.0833333; 
    hx = cos((hdeg - 90) * 0.0174532925);
    hy = sin((hdeg - 90) * 0.0174532925);
    mx = cos((mdeg - 90) * 0.0174532925);
    my = sin((mdeg - 90) * 0.0174532925);
    sx = cos((sdeg - 90) * 0.0174532925);
    sy = sin((sdeg - 90) * 0.0174532925);

    if (ss == 0 || initial) {
      initial = 0;
      // akrep ve yelkovan çubukları konum değiştirince arkada nıraktıkları izleri siler
      tft.drawLine(ohx, ohy, xpos, 121, TFT_GREY);
      ohx = hx * 62 + xpos + 1;
      ohy = hy * 62 + 121;
      tft.drawLine(omx, omy, xpos, 121, TFT_GREY);
      omx = mx * 84 + xpos;
      omy = my * 84 + 121;
      
    }

    // akrep, yelkovan çubuklarını ayarlar
    tft.drawLine(osx, osy, xpos, 121, TFT_GREY);
    osx = sx * 90 + xpos + 1;
    osy = sy * 90 + 121;
    tft.drawLine(osx, osy, xpos, 121, TFT_RED);
    tft.drawLine(ohx, ohy, xpos, 121, TFT_WHITE);
    tft.drawLine(omx, omy, xpos, 121, TFT_WHITE);
    tft.drawLine(osx, osy, xpos, 121, TFT_RED);

    tft.fillCircle(xpos, 121, 3, TFT_RED);
  }
}




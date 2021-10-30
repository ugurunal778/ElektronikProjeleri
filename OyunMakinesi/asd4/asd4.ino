/* 
 *  Motor sürmede röle kullanıldı, ve normal şartlarda logic "1" enerji verip logic "0" enerji keserken kullandığımız röle logic "0" ile tetiklendiği için burada durum tam tersi,
 *  eğer daha sonradan motor sürücü veye logic "1" ile tetiklenen röle kullanılırsa "ileri ve geri" değişkenlerine gönderilen durumların(digitalWrite komutlarının) tam tersine çevirilmesi gerekmektedir
 */



#define ileri 8                                                       // I/O pinleri belirleniyor
#define geri 9
#define signalPin 10

int dongu;

void setup(){
  pinMode(signalPin, INPUT);                                          // pinlerin I/O olup olmadığı belirleniyor
  pinMode(ileri, OUTPUT);
  pinMode(geri, OUTPUT);
  Serial.begin(9600);                                                 //seri haberleşme başlatılıp hızı belirleniyor
  digitalWrite(ileri, 0);                                             // başlangıç için motorun daha önceden hareket erme lasılığı göze alınarak motor kitleniyor
  digitalWrite(geri, 0);
  delay(10);
  dongu = 1;                                                          //gecikmeler karışmasın diye "true" mantığı ile dongu değişkeni atanıyor
}

void loop(){
  int sensor = analogRead(A0);                                        //par atmak için kızılötesi sensor okunuyor

  if (Serial.available());{
    int a = Serial.read(); 

    if (a == '2'){                                                    // eğer a = 2 ise aşağıdaki komutları çalıştırır                    |
      int signalState = digitalRead(signalPin);                       // signalState değişkeni oluştur ve acceptor durumunu ona ata       |
      if (dongu == 1 && signalState == LOW){                          // 2 şart birden var (dongu = 1 ve acceptorda para var) ise         |
        Serial.println('C');                                          // seri porttan "C" değerini yolla                                  |
        delay (10);                                                   //                                                                  |
        }                                                             //                                                                  |
      else if (dongu == 1 && signalState == HIGH){                    // yine 2 şart var (dongu = 1 ve acceptorda para yok) ise           |
        Serial.println('D');                                          // seri porttan "D" değerini yolla                                  |
        delay (10);                                                   //                                                                  |
      }                                                               //                                                                  |
    }                                                                 //                                                                  |
    
    if (dongu == 1){
      if (sensor > 900 ){
        Serial.println('F');                                          //para atma makinesi her para attığında C# saysın diye seri porttan "F" değeri yolluyor
        delay (100);
     }
                                                                      //seri porttan gelen değer a değişkenine atanıyor
      if (a == '1'){                                                  // a = "1" ise motor ileri sürülüyor
        digitalWrite(ileri, 0);
        digitalWrite(geri, 1);
      }
      else if (a == '0'){                                            // a = "0" ise motor ataletini kırmak için kilitleniyor ardından enerjisi kesiliyor
        digitalWrite(ileri, 0);
        digitalWrite(geri, 0);
        delay(10);
        digitalWrite (ileri, 1);
        digitalWrite (geri, 1);
      }   
     }            
   }
 }

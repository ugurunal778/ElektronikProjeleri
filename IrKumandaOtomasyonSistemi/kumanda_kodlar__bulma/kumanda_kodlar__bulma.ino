#include <IRremote.h>
 
int RECV_PIN = 11; //foto transistör bağlantısı
IRrecv irrecv(RECV_PIN);
decode_results kod;
void setup()
{
Serial.begin(9600);
irrecv.enableIRIn(); // alma için hazırlandı
}
 
void loop()
{
if (irrecv.decode(&kod)){
Serial.println(kod.value, DEC); // Kodun Desimal Değere çevirerek göster
irrecv.resume();} // Yeni kod alımına hazır
}

const int trigPin = 8;   //Ultrasonik sensörün TRIG pini
const int echoPin = 9;   //Ultrasonik sensörün ECHO pini
const int buzzer = 10;   //Buzzer pini
const int led = 11;      //LED pini

long sure;               //Ses dalgasının gidiş-dönüş süresini saklamak için
int mesafe;              //Hesaplanan mesafe (cm cinsinden)

void setup() {
  pinMode(trigPin, OUTPUT); //Trig pini çıkış olarak ayarlanıyor
  pinMode(echoPin, INPUT);  //Echo pini giriş olarak ayarlanıyor
  pinMode(buzzer, OUTPUT);  //Buzzer çıkış olarak ayarlanıyor
  pinMode(led, OUTPUT);     //Led çıkış olarak ayarlanıyor
  Serial.begin(9600);       //Seri iletişim başlatılıyor (ölçümleri görmek için)
}

void loop() {
  //Ultrasonik sensörden mesafe ölçümü
  digitalWrite(trigPin, LOW);    //TRIG pini sıfırlar
  delayMicroseconds(2);          //2 µs bekleniyor
  digitalWrite(trigPin, HIGH);   //TRIG pini 10 µs boyunca HIGH yapılıyor
  delayMicroseconds(10);         //10 µs bekleniyor
  digitalWrite(trigPin, LOW);    //TRIG pini tekrar LOW yapılıyor

  sure = pulseIn(echoPin, HIGH); //Echo pininden gelen süre ölçülüyor
  mesafe = sure * 0.034 / 2;     //Ses hızına göre mesafe hesaplanıyor

  //Ölçülen mesafeyi seri port ekranına yazdırır
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");

  //Mesafeye göre LED ve buzzer kontrolü
  if (mesafe > 20) {  // Eğer mesafe 20 cm’den büyükse
    digitalWrite(led, LOW);   // LED kapalı
    noTone(buzzer);   // Buzzer sessiz
  } 
  else if (mesafe <= 20 && mesafe > 10) { //Eğer mesafe 20–10 cm arasındaysa
    digitalWrite(led, HIGH);     // Led yanar
    tone(buzzer, 1000);         // Buzzer 1000 Hz ses üretir
    delay(200);                // 200 ms ötme süresi
    noTone(buzzer);           // Buzzer susturulur
    delay(200);              // 200 ms bekleme süresi
  } 
  else if (mesafe <= 10) {      // Eğer mesafe 10 cm’den küçükse
    digitalWrite(led, HIGH);   // LED yanar
    tone(buzzer, 1000);       // Buzzer sürekli öter
  }
}
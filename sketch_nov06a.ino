#define SolMotorGeri 31
#define SolMotorileri 33
#define SagMotorileri 35
#define SagMotorGeri 37
#define trigPin 50
#define echoPin 52

String gelenVeri;
void setup() {
  
pinMode(SolMotorileri,OUTPUT);
pinMode(SolMotorGeri,OUTPUT);
pinMode(SagMotorileri,OUTPUT);
pinMode(SagMotorGeri,OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600); //iletişim ayarı
}
void loop() {
  while (Serial.available()){  
  delay(10);
  char b = Serial.read();
  gelenVeri += b; 
  }   
  if (gelenVeri.length() > 0) {
    gelenVeri.toLowerCase();
    gelenVeri.trim();
    Serial.println(gelenVeri); 
        // Harflerin olmasının sebebi ise android uygulamadan da kontrol edilebilmesi içindir
         if(gelenVeri == "ileri git" || gelenVeri=="f" ) 
         {
            IleriGitme();
         } 
         if(gelenVeri == "geri git" || gelenVeri =="b")
         {
          GeriGitme();
          while(true)
          {
            double sonuc = MesafeOlcum(); // Ultrasonik sensör ile arabanın arkasının çarpmaması için yapılan kontrol
            if(sonuc<10)
            {
            Durdurma();  
            break;
            }
            if(Serial.available())
            {
            break;
            }
           }
         } 
         if(gelenVeri =="sağa dön")
         {
            SagaDonme();
            delay(600);
            Durdurma();  
         }
         if(gelenVeri=="r"){
          SagaDonme();
         }
         if(gelenVeri =="sola dön" )
         {
            SolaDonme();
            delay(600);
            Durdurma();         
         }
         if(gelenVeri=="l"){
          SolaDonme();
         }
         if(gelenVeri =="dur" || gelenVeri=="s"){
            Durdurma();
         }                       

}//GELEN VERİ UZUNLUK SONU
gelenVeri="";
}//LOOP SONU
void IleriGitme(){
digitalWrite(SolMotorileri,HIGH);
digitalWrite(SagMotorileri,HIGH);
digitalWrite(SolMotorGeri,LOW);
digitalWrite(SagMotorGeri,LOW);  }

void GeriGitme(){
digitalWrite(SolMotorGeri,HIGH);
digitalWrite(SagMotorGeri,HIGH);
digitalWrite(SolMotorileri,LOW);
digitalWrite(SagMotorileri,LOW); }

void SagaDonme(){
digitalWrite(SagMotorileri,LOW);
digitalWrite(SolMotorileri,HIGH);
digitalWrite(SagMotorGeri,HIGH);
digitalWrite(SolMotorGeri,LOW);}

void SolaDonme(){
digitalWrite(SolMotorileri,LOW);
digitalWrite(SagMotorileri,HIGH);
digitalWrite(SolMotorGeri,HIGH);
digitalWrite(SagMotorGeri,LOW);}

void Durdurma(){
digitalWrite(SolMotorileri,LOW);
digitalWrite(SagMotorileri,LOW);
digitalWrite(SolMotorGeri,LOW);
digitalWrite(SagMotorGeri,LOW);  }

int MesafeOlcum(){
long sure,mesafe;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
sure = pulseIn(echoPin, HIGH);
mesafe = (sure/2) / 29.1;
return mesafe;}

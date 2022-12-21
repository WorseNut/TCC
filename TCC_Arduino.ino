#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Servo.h>
// Inclui as bibliotecas

#define RST_PIN         D3
#define SS_PIN          D4
#define LED_G D1
#define LED_R D0
// define as funções das portas do arduino

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Cria a instancia do MFRC522
Servo myservo;  // Cria o objeto servo para controlar ele
int buzzerPin = D8; // Variavel para nomear a porta D8 como buzeerPin

void setup() {
  Serial.begin(9600);        // Inicia a comunicação serial com o computador
  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(D2);

  pinMode (LED_G, OUTPUT);
  pinMode (LED_R, OUTPUT);

  Serial.println("Passe o cartão para leitura...");
  Serial.println();
  
}
//loop infinito
void loop() {
  int pos; // Variavel responsavel pelo movimento do servo
  
    // verifica se há um cartão para realizar a função
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

   // Lê as informações do cartão que foi passado
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
        return;
    }
//mostra o UID no motor serial
 Serial.println("UID tag : ");
  String content="";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte [i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte [i], HEX));  
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "4B DD 14 36")//UID do cartão
  {
    Serial.println("Acesso Autorizado");
    Serial.println();
    delay(500);

    digitalWrite(LED_G, HIGH);
    delay(1000);

    digitalWrite(LED_G, LOW);
    delay(1000);

    pinMode(buzzerPin, OUTPUT);
    tone(buzzerPin,2500,250);
    delay(250);
    noTone(buzzerPin);

    for (pos = 0; pos <= 270; pos += 7) 
    {
    myservo.write(pos);              // passa para o servo a posição que ele tem ir
    delay(15);             
    }
    for (pos = 270; pos >= 0; pos -= 7) 
    {
    myservo.write(pos);              // passa para o servo a posição que ele tem ir
    delay(15);             
    }
    
  }
    else if (content.substring(1) == "53 ED 43 05")// UID do cartão
  {
    Serial.println("Acesso Autorizado");
    Serial.println();
    delay(500);

    digitalWrite(LED_G, HIGH);
    delay(500);

    digitalWrite(LED_G, LOW);
    delay(500);

    pinMode(buzzerPin, OUTPUT);
    tone(buzzerPin,2500,250);
    delay(250);
    noTone(buzzerPin);
    
for (pos = 0; pos <= 270; pos += 7) 
    {
    myservo.write(pos);              // passa para o servo a posição que ele tem ir
    delay(15);             
    }
    for (pos = 270; pos >= 0; pos -= 7) 
    {
    myservo.write(pos);              // passa para o servo a posição que ele tem ir
    delay(15);             
    }
  }

  else{
    Serial.println("Acesso Negado");
    digitalWrite(LED_R, HIGH);
    delay(1000);
    digitalWrite(LED_R, LOW);
    delay(1000);
    pinMode(buzzerPin, OUTPUT);
    tone(buzzerPin,1750,250);
  }
}
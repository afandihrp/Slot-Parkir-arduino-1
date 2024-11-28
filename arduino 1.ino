#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10  // Pin for RC522 SDA
#define RST_PIN 9  // Pin for RC522 RST

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

LiquidCrystal_I2C lcd(0x27,16,2);

int jumlah_kendaraan_yang_masuk=0;

String kendaraan_masuk_sebelumnya[10];

bool parkir_udah_penuh = false;

byte bar1[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};



void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  lcd.init();
  lcd.createChar(1,bar1);
  lcd.createChar(2,bar2);
  lcd.createChar(3,bar3);
  lcd.createChar(4,bar4);
  lcd.createChar(5,bar5);
  lcd.createChar(6,bar6);
  lcd.createChar(7,bar7);
  lcd.createChar(8,bar8);
  lcd.backlight();

  Serial.begin(9600);  // Start Serial Monitor
  SPI.begin();         // Start SPI communication
  mfrc522.PCD_Init();  // Initialize RC522
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  // Serial.println("Place your RFID tag near the reader...");
}

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  } if (value == 10)
  {
    custom1(col);
    custom0(col);
  }
  
}


void print_data_tersimpan()
{
  int arraySize = sizeof(kendaraan_masuk_sebelumnya) / sizeof(kendaraan_masuk_sebelumnya[0]);
  for(int x=0;x<arraySize;x++)
  {
    Serial.println(String(x+1)+"."+String(kendaraan_masuk_sebelumnya[x]));
  }
}

bool cek_kendaraan_yang_masuk(String uid_kendaraan){
  int arraySize = sizeof(kendaraan_masuk_sebelumnya) / sizeof(kendaraan_masuk_sebelumnya[0]);
  for(int x=0;x<arraySize;x++)
  {
    Serial.println("sebelum: "+ kendaraan_masuk_sebelumnya[x]+"--dengan: "+uid_kendaraan);
    if(kendaraan_masuk_sebelumnya[x].equals(uid_kendaraan) && !jumlah_kendaraan_yang_masuk == 0)
    {
      kendaraan_masuk_sebelumnya[x]="";
      jumlah_kendaraan_yang_masuk-=1;
      parkir_udah_penuh = false;
      print_data_tersimpan();
      Serial.println("data ditemukan, silahkan Keluar");
      return false;
    }    
  }
  for(int x=0;x<arraySize;x++)
  {
    Serial.println("dengan: "+ kendaraan_masuk_sebelumnya[x]+"--sebelumnya: "+uid_kendaraan);
    if(kendaraan_masuk_sebelumnya[x].equals(""))
    {
      kendaraan_masuk_sebelumnya[x]=uid_kendaraan;
      jumlah_kendaraan_yang_masuk+=1;
      print_data_tersimpan();
      Serial.println("data Tidak ketemu, Silahkan Masuk");
      return true;
    }
  }
  parkir_udah_penuh = true;
  Serial.println("data penuh, parkir sudah penuh");
}

bool card_terdeteksi= false;

void loop() {
  String recievedUID;
  lcd.setCursor(0, 0);
  lcd.print("Kendaraan:");
  printNumber(jumlah_kendaraan_yang_masuk, 10);
  

  if (mfrc522.PICC_IsNewCardPresent()) {  // If a new card is detected
    String uidString = "";
    // Initialize an empty string for UID
    if (mfrc522.PICC_ReadCardSerial()) {  // If card is read successfully
      uidString= "";
      // Loop through each byte of the UID and append it to the string
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Append each byte to the string as a hexadecimal value
        uidString += String(mfrc522.uid.uidByte[i], HEX);
      }
      // uidString.trim();
      
      // Print the complete UID string
      Serial.println(uidString);
      delay(10);
      // receivedUID=uidString;      
      mfrc522.PICC_HaltA();  // Stop reading the card
      recievedUID=uidString;


      Serial.println(recievedUID);

      if(cek_kendaraan_yang_masuk(uidString) && !parkir_udah_penuh)
      {
        
        Serial.println("Gerbang masuk Buka");
        digitalWrite(2, LOW);
        
        Serial.println("kendaraan sudah masuk, memulai counter 2 detik");  
        // delay(1000);
        digitalWrite(2, HIGH);
        
        Serial.println("Gerbang masuk Tutup");

      }
      else if(!parkir_udah_penuh)
      {

        Serial.println("Gerbang keluar Buka");
        digitalWrite(3, LOW);
        Serial.println("kendaraan sudah masuk, memulai counter 2 detik");
        // delay(2000);
        digitalWrite(3, HIGH);

        Serial.println("Gerbang keluar Tutup");  

      }
      Serial.println();
      Serial.println("Jumlah Kendaraan: "+String(jumlah_kendaraan_yang_masuk));
      Serial.println();

    }
  }
}


#include <Servo.h>

#define pin_trigger_pintu_masuk 4
#define pin_echo_pintu_masuk 5

#define pin_trigger_pintu_keluar 7
#define pin_echo_pintu_keluar 6

bool pintu_masuk_sudah_tertutup = true;
bool pintu_keluar_sudah_tertutup = true;

Servo pintu_masuk;  // Create a servo object
Servo pintu_keluar;

void setup() {

  pintu_masuk.attach(9);  // Attach the servo to pin 9
  pintu_keluar.attach(10);

  pintu_masuk.write(180);
  pintu_keluar.write(90);

  Serial.begin(9600);
  Serial.println("test");
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);



  pinMode(pin_trigger_pintu_masuk, OUTPUT);
  pinMode(pin_trigger_pintu_keluar, OUTPUT);

  pinMode(pin_echo_pintu_masuk, INPUT);
  pinMode(pin_echo_pintu_masuk, INPUT);
}

int baca_sensor_pintu(uint8_t pin_trigger, uint8_t pin_echo)
{
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  int test = pulseIn(pin_echo,HIGH)*0.034 / 2;
  Serial.println("Distance: "+String(test));
  delay(10);
  return test;
}

unsigned long timer1 = 0, timer2 = 0;
uint16_t lama_delay = 1000;

void loop() {
  

  if(!digitalRead(2) || !pintu_masuk_sudah_tertutup)
  {
    uint16_t jarak = baca_sensor_pintu(pin_trigger_pintu_masuk, pin_echo_pintu_masuk);

    if(jarak<=3 || pintu_masuk_sudah_tertutup)
    {  
      pintu_masuk_sudah_tertutup = false;
      pintu_masuk.write(90);
      Serial.println("pintu masuk terbuka");
      timer1 = millis();
    }
    else if(jarak>3 && millis()-timer1 > lama_delay)
    {      
      pintu_masuk_sudah_tertutup = true;
      pintu_masuk.write(180);
      Serial.println("pintu masuk ditutup");      
    }
    else
    {
      int anjeng = millis()-timer1;
      Serial.println();
      Serial.println("Timer: "+String(anjeng));
    }
  }


  if(!digitalRead(3) || !pintu_keluar_sudah_tertutup)
  {
    uint16_t jarak = baca_sensor_pintu(pin_trigger_pintu_keluar, pin_echo_pintu_keluar);

    if(jarak<=4 || pintu_keluar_sudah_tertutup)
    {      
      pintu_keluar_sudah_tertutup = false;
      pintu_keluar.write(90);
      Serial.println("pintu keluar terbuka");
      timer2 = millis();
    }
    else if(jarak>4 && millis()-timer2 > lama_delay)
    {
      pintu_keluar.write(180);
      pintu_keluar_sudah_tertutup = true;
      Serial.println("pintu keluar ditutup");      
    }
    else
    {
      int anjeng = millis()-timer2;
      Serial.println();
      Serial.println("Timer: "+String(anjeng));
    }
  }
  
}

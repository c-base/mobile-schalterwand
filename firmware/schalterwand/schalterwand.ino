#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define MOSI 13
#define SCK 6
#define LATCH A2

#include <SPI.h>

struct R1 {
  uint8_t
          : 1,
  Br2 : 1,
  Y1   : 1;
};

struct R2 {
  uint8_t
  LED_4 : 1,
  LED_3 : 1,
  LED_8 : 1,
  LED_7 : 1,
  Y2        : 1,
  Y3        : 1,
  Br3      : 1,
  Br1      : 1;
};

struct R3 {
  uint8_t
  LED_2 : 1,
  LED_5 : 1,
  LED_6: 1,
              : 1, // ???
  LED_1: 1;
};

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);
  pinMode(MOSI, OUTPUT); // 11
  pinMode(LATCH, OUTPUT); // A2
  pinMode(SCK, OUTPUT); // 13

  Serial.begin(115200);
  SPI.begin();  
}

void loop() {   
  R1 r1 = {0};
  R2 r2 = {0};
  R3 r3 = {0};

  r3.LED_1 = 1;
  r3.LED_2 = 0;
  r2.LED_3 = 0;
  r2.LED_4 = 0;
  r3.LED_5 = 0;
  r3.LED_6 = 0;
  r2.LED_7 = 0;
  r2.LED_8 = 0;
  
  while(true) {       
    digitalWrite(LATCH, LOW);
    delay(100);    

    SPI.transfer(*reinterpret_cast<uint8_t*>(&r3));    
    delay(100);
    SPI.transfer(*reinterpret_cast<uint8_t*>(&r2));
    delay(100);
    SPI.transfer(0);
    delay(100);
  
    digitalWrite(LATCH, HIGH);  
    delay(500);
  }
}

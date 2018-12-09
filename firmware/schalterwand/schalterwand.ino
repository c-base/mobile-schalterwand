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
  LED_A : 1,
  LED_B : 1,
  LED_C : 1,
  LED_D : 1,
  Y2        : 1,
  Y3        : 1,
  Br3      : 1,
  Br1      : 1;
};

struct R3 {
  uint8_t
  LED_E : 1,
  LED_F : 1,
  LED_G: 1,
  LED_H: 1;
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
  SPI.setClockDivider(SPI_CLOCK_DIV128);
}

void loop() {
  R1 r1 = {0};
  R2 r2 = {0};
  R3 r3 = {0};

  r2.LED_A = 1;
  r2.LED_B = 0;
  r2.LED_C = 0;
  r2.LED_D = 0;
  r3.LED_E = 0;
  r3.LED_F = 0;
  r3.LED_G = 0;
  r3.LED_H = 0;

  digitalWrite(LATCH, LOW);
  delay(10);

  SPI.transfer(*reinterpret_cast<uint8_t*>(&r1));
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&r2));
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&r3));

  delay(10);
  digitalWrite(LATCH, LOW);
  
  while(true)
    ;
}

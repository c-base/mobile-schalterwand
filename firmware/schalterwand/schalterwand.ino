#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define MOSI 13
#define SCK 6
#define LATCH A2

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SCK, OUTPUT);
}

void loop() {
  
}

#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define SER_IN 13
#define SRCLK 6
#define RCLK A2

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);
  pinMode(SER_IN, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop() {
  
}

#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define LATCH A2

#include <SPI.h>

struct {
  uint8_t
          : 1,
  Br2 : 1,
  Y1   : 1;
} _r1 = {0};

struct {
  uint8_t
  LED_4 : 1,
  LED_3 : 1,
  LED_8 : 1,
  LED_7 : 1,
  Y2        : 1,
  Y3        : 1,
  Br3      : 1,
  Br1      : 1;
} _r2 = {0};

struct {
  uint8_t
  LED_2 : 1,
  LED_5 : 1,
  LED_6 :  1,
              :  1,
  LED_1 : 1;
} _r3 = {0};

void xferRegisters() {
  digitalWrite(LATCH, LOW);
  delay(10);    

  SPI.transfer(*reinterpret_cast<uint8_t*>(&_r3));    
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&_r2));
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&_r1));
  delay(10);
    
  digitalWrite(LATCH, HIGH);  
  delay(10);
}

#define readWire(Y, Br, Bl, enY, enBr) ({   \
  bool __wireState;                                            \
  {                                                                         \
    Y = enY;                                                          \
    Br = enBr;                                                      \
    xferRegisters();                                            \
                                                                            \
    __wireState = digitalRead(Bl);                   \
                                                                            \
    Y = 0;                                                              \
    Br = 0;                                                            \
    xferRegisters();                                            \
  }                                                                        \
                                                                            \
  __wireState;                                                    \
})

#define readBrownWire(Y, Br, Bl) readWire(Y, Br, Bl, 0, 1)
#define readYellowWire(Y, Br, Bl) readWire(Y, Br, Bl, 1, 0)

class Switch {
public:
  enum class Position {
    LeftOrRight = 0,
    Down = 1,
    Up = 2,
  };

  Switch::Position readPos();
  const char* readPosStr();
  
private:
  virtual bool brown() = 0;
  virtual bool yellow() = 0;
};

Switch::Position Switch::readPos() {
  if(brown())
    return Position::Down;
  else if (yellow())
    return Position::Up;
  else
    return Position::LeftOrRight;
}

const char* Switch::readPosStr() {
  switch(readPos()) {
    case Switch::Position::Down: return "Down";
    case Switch::Position::Up: return "Up";
    case Switch::Position::LeftOrRight: "Left or Right";

    default: return "Unknown";
  }
}

// SW1:  Y1, Br1, Bl4
class Sw1 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r1.Y1, _r2.Br1, BL4); }
  virtual bool yellow() final override { return readYellowWire(_r1.Y1, _r2.Br1, BL4); }
};

// SW2: Y2, Br2, Bl4
class Sw2 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y2, _r1.Br2, BL4); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y2, _r1.Br2, BL4); }
};

// SW3: Y2, Br2, Bl3
class Sw3 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y2, _r1.Br2, BL3); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y2, _r1.Br2, BL3); }
};

// SW4: Y1, Br1, Bl3
class Sw4 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r1.Y1, _r2.Br1, BL3); }
  virtual bool yellow() final override { return readYellowWire(_r1.Y1, _r2.Br1, BL3); }
};

// SW5: Y1, Br1, Bl1
class Sw5 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r1.Y1, _r2.Br1, BL1); }
  virtual bool yellow() final override { return readYellowWire(_r1.Y1, _r2.Br1, BL1); }
};

// SW6: Y2, Br2, Bl1
class Sw6 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y2, _r1.Br2, BL1); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y2, _r1.Br2, BL1); }
};

// SW7: Y2, Br2, Bl2
class Sw7 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y2, _r1.Br2, BL2); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y2, _r1.Br2, BL2); }
};

// SW8: Y1, Br1, Bl2
class Sw8 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r1.Y1, _r2.Br1, BL2); }
  virtual bool yellow() final override { return readYellowWire(_r1.Y1, _r2.Br1, BL2); }
};

// SW9: Y3, Br3, Bl1
class Sw9 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y3, _r2.Br3, BL1); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y3, _r2.Br3, BL1); }
};

// SW10: Y3, Br3, Bl4
class Sw10 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y3, _r2.Br3, BL4); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y3, _r2.Br3, BL4); }
};

// SW11: Y3, Br3, Bl3
class Sw11 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y3, _r2.Br3, BL3); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y3, _r2.Br3, BL3); }
};

// SW12, Y3, Br3, Bl2
class Sw12 : public Switch {
  virtual bool brown() final override { return readBrownWire(_r2.Y3, _r2.Br3, BL2); }
  virtual bool yellow() final override { return readYellowWire(_r2.Y3, _r2.Br3, BL2); }
};

Sw1 _sw1;
Sw2 _sw2;
Sw3 _sw3;
Sw4 _sw4;
Sw5 _sw5;
Sw6 _sw6;
Sw7 _sw7;
Sw8 _sw8;
Sw9 _sw9;
Sw10 _sw10;
Sw11 _sw11;
Sw12 _sw12;

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);  
  pinMode(LATCH, OUTPUT);

  Serial.begin(115200);
  SPI.begin();  
}

void loop() {  
  _r3.LED_1 = 1;
  _r3.LED_2 = 0;
  _r2.LED_3 = 0;
  _r2.LED_4 = 0;
  _r3.LED_5 = 0;
  _r3.LED_6 = 0;
  _r2.LED_7 = 0;
  _r2.LED_8 = 0;
  
  while(true) {           
    Serial.print("SW1: ");   Serial.print(_sw1.readPosStr());   Serial.print(", ");
    Serial.print("SW2: ");   Serial.print(_sw2.readPosStr());   Serial.print(", ");
    Serial.print("SW3: ");   Serial.print(_sw3.readPosStr());   Serial.print(", ");
    Serial.print("SW4: ");   Serial.print(_sw4.readPosStr());   Serial.print(", ");
    Serial.print("SW5: ");   Serial.print(_sw5.readPosStr());   Serial.print(", ");
    Serial.print("SW6: ");   Serial.print(_sw6.readPosStr());   Serial.print(", ");
    Serial.print("SW7: ");   Serial.print(_sw7.readPosStr());   Serial.print(", ");
    Serial.print("SW8: ");   Serial.print(_sw8.readPosStr());   Serial.print(", ");
    Serial.print("SW9: ");   Serial.print(_sw9.readPosStr());   Serial.print(", ");
    Serial.print("SW10: "); Serial.print(_sw10.readPosStr()); Serial.print(", ");
    Serial.print("SW11: "); Serial.print(_sw11.readPosStr()); Serial.print(", ");
    Serial.print("SW12: "); Serial.print(_sw12.readPosStr()); Serial.print(", ");
  }
}

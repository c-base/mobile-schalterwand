#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define LATCH A2

#include <SPI.h>

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
  LED_6 :  1,
              :  1,
  LED_1 : 1;
};

//------------------------------------------
// Switch
//------------------------------------------

class Switch {
public:
  enum class Position {
    Invalid,
    LeftOrRight,
    Down,
    Up,
  };

  Switch(R1* pR1, R2* pR2, R3* pR3) : pR1_(pR1), pR2_(pR2), pR3_(pR3) { }
  Switch::Position readPos();
  const char* readPosStr();
  void xferRegisters();

protected:
// TODO: make private:
  R1* const pR1_;
  R2* const pR2_;
  R3* const pR3_;
// --
  
private:
  virtual bool brown() = 0;
  virtual bool yellow() = 0;
};

void Switch::xferRegisters() {
    digitalWrite(LATCH, LOW);
    delay(10);    

    SPI.transfer(*reinterpret_cast<uint8_t*>(pR3_));    
    delay(10);
    SPI.transfer(*reinterpret_cast<uint8_t*>(pR2_));
    delay(10);
    SPI.transfer(*reinterpret_cast<uint8_t*>(pR1_));
    delay(10);
    
    digitalWrite(LATCH, HIGH);  
    delay(10);
  }

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

    default: return "Invalid";
  }
}

// SW1:  Y1, Br1, Bl4
class Sw1 : public Switch {
public:
  Sw1(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR1_->Y1, pR2_->Br1, BL4); }
  virtual bool yellow() final override { return readYellowWire(pR1_->Y1, pR2_->Br1, BL4); }
};

// SW2: Y2, Br2, Bl4
class Sw2 : public Switch {
public:
  Sw2(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y2, pR1_->Br2, BL4); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y2, pR1_->Br2, BL4); }
};

// SW3: Y2, Br2, Bl3
class Sw3 : public Switch {
public:
  Sw3(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y2, pR1_->Br2, BL3); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y2, pR1_->Br2, BL3); }
};

// SW4: Y1, Br1, Bl3
class Sw4 : public Switch {
public:
  Sw4(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR1_->Y1, pR2_->Br1, BL3); }
  virtual bool yellow() final override { return readYellowWire(pR1_->Y1, pR2_->Br1, BL3); }
};

// SW5: Y1, Br1, Bl1
class Sw5 : public Switch {
public:
  Sw5(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR1_->Y1, pR2_->Br1, BL1); }
  virtual bool yellow() final override { return readYellowWire(pR1_->Y1, pR2_->Br1, BL1); }
};

// SW6: Y2, Br2, Bl1
class Sw6 : public Switch {
public:
  Sw6(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y2, pR1_->Br2, BL1); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y2, pR1_->Br2, BL1); }
};

// SW7: Y2, Br2, Bl2
class Sw7 : public Switch {
public:
  Sw7(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y2, pR1_->Br2, BL2); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y2, pR1_->Br2, BL2); }
};

// SW8: Y1, Br1, Bl2
class Sw8 : public Switch {
public:
  Sw8(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR1_->Y1, pR2_->Br1, BL2); }
  virtual bool yellow() final override { return readYellowWire(pR1_->Y1, pR2_->Br1, BL2); }
};

// SW9: Y3, Br3, Bl1
class Sw9 : public Switch {
public:
  Sw9(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y3, pR2_->Br3, BL1); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y3, pR2_->Br3, BL1); }
};

// SW10: Y3, Br3, Bl4
class Sw10 : public Switch {
public:
  Sw10(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y3, pR2_->Br3, BL4); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y3, pR2_->Br3, BL4); }
};

// SW11: Y3, Br3, Bl3
class Sw11 : public Switch {
public:
  Sw11(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y3, pR2_->Br3, BL3); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y3, pR2_->Br3, BL3); }
};

// SW12, Y3, Br3, Bl2
class Sw12 : public Switch {
public:
  Sw12(R1* pR1, R2* pR2, R3* pR3) : Switch(pR1, pR2, pR3) {}

private:
  virtual bool brown() final override { return readBrownWire(pR2_->Y3, pR2_->Br3, BL2); }
  virtual bool yellow() final override { return readYellowWire(pR2_->Y3, pR2_->Br3, BL2); }
};

//------------------------------------------
// SchalterWand
//------------------------------------------

class SchalterWand {
public:
  SchalterWand() :
    sw1_(&r1_, &r2_, &r3_),
    sw2_(&r1_, &r2_, &r3_),
    sw3_(&r1_, &r2_, &r3_),
    sw4_(&r1_, &r2_, &r3_),
    sw5_(&r1_, &r2_, &r3_),
    sw6_(&r1_, &r2_, &r3_),
    sw7_(&r1_, &r2_, &r3_),
    sw8_(&r1_, &r2_, &r3_),
    sw9_(&r1_, &r2_, &r3_),
    sw10_(&r1_, &r2_, &r3_),
    sw11_(&r1_, &r2_, &r3_),
    sw12_(&r1_, &r2_, &r3_) {
  
  }

  // TODO: make private:
  Sw1 sw1_;
  Sw2 sw2_;
  Sw3 sw3_;
  Sw4 sw4_;
  Sw5 sw5_;
  Sw6 sw6_;
  Sw7 sw7_;
  Sw8 sw8_;
  Sw9 sw9_;
  Sw10 sw10_;
  Sw11 sw11_;
  Sw12 sw12_;

  R1 r1_;  
  R2 r2_;
  R3 r3_;
  // --
  
private:  
  
};

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);  
  pinMode(LATCH, OUTPUT);

  Serial.begin(115200);
  SPI.begin();  
}

SchalterWand _schalterWand;

void loop() {
  _schalterWand.r3_.LED_1 = 1;
  _schalterWand.r3_.LED_2 = 0;
  _schalterWand.r2_.LED_3 = 0;
  _schalterWand.r2_.LED_4 = 0;
  _schalterWand.r3_.LED_5 = 0;
  _schalterWand.r3_.LED_6 = 0;
  _schalterWand.r2_.LED_7 = 0;
  _schalterWand.r2_.LED_8 = 0;
  
  while(true) {           
    Serial.print("SW1: ");   Serial.print(_schalterWand.sw1_.readPosStr());   Serial.print(", ");
    Serial.print("SW2: ");   Serial.print(_schalterWand.sw2_.readPosStr());   Serial.print(", ");
    Serial.print("SW3: ");   Serial.print(_schalterWand.sw3_.readPosStr());   Serial.print(", ");
    Serial.print("SW4: ");   Serial.print(_schalterWand.sw4_.readPosStr());   Serial.print(", ");
    Serial.print("SW5: ");   Serial.print(_schalterWand.sw5_.readPosStr());   Serial.print(", ");
    Serial.print("SW6: ");   Serial.print(_schalterWand.sw6_.readPosStr());   Serial.print(", ");
    Serial.print("SW7: ");   Serial.print(_schalterWand.sw7_.readPosStr());   Serial.print(", ");
    Serial.print("SW8: ");   Serial.print(_schalterWand.sw8_.readPosStr());   Serial.print(", ");
    Serial.print("SW9: ");   Serial.print(_schalterWand.sw9_.readPosStr());   Serial.print(", ");
    Serial.print("SW10: "); Serial.print(_schalterWand.sw10_.readPosStr()); Serial.print(", ");
    Serial.print("SW11: "); Serial.print(_schalterWand.sw11_.readPosStr()); Serial.print(", ");
    Serial.print("SW12: "); Serial.print(_schalterWand.sw12_.readPosStr()); Serial.print(", ");
  }
}

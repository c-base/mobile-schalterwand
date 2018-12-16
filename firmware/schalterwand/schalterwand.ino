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
    pReg_->write();                                            \
                                                                            \
    __wireState = digitalRead(Bl);                   \
                                                                            \
    Y = 0;                                                              \
    Br = 0;                                                            \
    pReg_->write();                                            \
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
// Registers
//------------------------------------------

class Registers {
public:
  void write();

  R1 r1_;
  R2 r2_;
  R3 r3_;
};

void Registers::write() {
  digitalWrite(LATCH, LOW);
  delay(10);

  SPI.transfer(*reinterpret_cast<uint8_t*>(&r3_));
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&r2_));
  delay(10);
  SPI.transfer(*reinterpret_cast<uint8_t*>(&r1_));
  delay(10);

  digitalWrite(LATCH, HIGH);
  delay(10);
}

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

  Switch(Registers* pReg) : pReg_(pReg) { }
  Switch::Position readPos();
  const char* readPosStr();

protected:
  Registers* const pReg_; // TODO: make private
  
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

    default: return "Invalid";
  }
}

// SW1:  Y1, Br1, Bl4
class Sw1 : public Switch {
public:
  Sw1(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL4); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL4); }
};

// SW2: Y2, Br2, Bl4
class Sw2 : public Switch {
public:
  Sw2(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL4); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL4); }
};

// SW3: Y2, Br2, Bl3
class Sw3 : public Switch {
public:
  Sw3(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL3); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL3); }
};

// SW4: Y1, Br1, Bl3
class Sw4 : public Switch {
public:
  Sw4(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL3); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL3); }
};

// SW5: Y1, Br1, Bl1
class Sw5 : public Switch {
public:
  Sw5(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL1); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL1); }
};

// SW6: Y2, Br2, Bl1
class Sw6 : public Switch {
public:
  Sw6(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL1); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL1); }
};

// SW7: Y2, Br2, Bl2
class Sw7 : public Switch {
public:
  Sw7(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL2); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y2, pReg_->r1_.Br2, BL2); }
};

// SW8: Y1, Br1, Bl2
class Sw8 : public Switch {
public:
  Sw8(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL2); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r1_.Y1, pReg_->r2_.Br1, BL2); }
};

// SW9: Y3, Br3, Bl1
class Sw9 : public Switch {
public:
  Sw9(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL1); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL1); }
};

// SW10: Y3, Br3, Bl4
class Sw10 : public Switch {
public:
  Sw10(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL4); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL4); }
};

// SW11: Y3, Br3, Bl3
class Sw11 : public Switch {
public:
  Sw11(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL3); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL3); }
};

// SW12, Y3, Br3, Bl2
class Sw12 : public Switch {
public:
  Sw12(Registers* pReg) : Switch(pReg) {}

private:
  virtual bool brown() final override { return readBrownWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL2); }
  virtual bool yellow() final override { return readYellowWire(pReg_->r2_.Y3, pReg_->r2_.Br3, BL2); }
};

//------------------------------------------
// SchalterWand
//------------------------------------------

class SchalterWand {
public:
  SchalterWand() :
    sw1_(&reg_),
    sw2_(&reg_),
    sw3_(&reg_),
    sw4_(&reg_),
    sw5_(&reg_),
    sw6_(&reg_),
    sw7_(&reg_),
    sw8_(&reg_),
    sw9_(&reg_),
    sw10_(&reg_),
    sw11_(&reg_),
    sw12_(&reg_) {

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

  Registers reg_;
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
  _schalterWand.reg_.r3_.LED_1 = 1;
  _schalterWand.reg_.r3_.LED_2 = 0;
  _schalterWand.reg_.r2_.LED_3 = 0;
  _schalterWand.reg_.r2_.LED_4 = 0;
  _schalterWand.reg_.r3_.LED_5 = 0;
  _schalterWand.reg_.r3_.LED_6 = 0;
  _schalterWand.reg_.r2_.LED_7 = 0;
  _schalterWand.reg_.r2_.LED_8 = 0;
  
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

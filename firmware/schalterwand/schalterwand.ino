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

//------------------------------------------
// Registers
//------------------------------------------

class Registers {
public:
  void write();

  struct {
    uint8_t
            : 1,
    Br2 : 1,
    Y1   : 1;
  } r1_;

  struct  {
    uint8_t
    LED_4 : 1,
    LED_3 : 1,
    LED_8 : 1,
    LED_7 : 1,
    Y2        : 1,
    Y3        : 1,
    Br3      : 1,
    Br1      : 1;
  } r2_;

  struct {
    uint8_t
    LED_2 : 1,
    LED_5 : 1,
    LED_6 :  1,
                :  1,
    LED_1 : 1;
  } r3_;
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
  static const char* posToString(Position pos);

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

const char* Switch::posToString(Position pos) {
  switch(pos) {
    case Switch::Position::Down: return "Down";
    case Switch::Position::Up: return "Up";
    case Switch::Position::LeftOrRight: return "Left or Right";

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

typedef void (*OnSwitchPositionChange)(int id, Switch::Position pos);

class SchalterWand {
public:
  SchalterWand(OnSwitchPositionChange onSwitchPositionChange) :
    onSwitchPositionChange_(onSwitchPositionChange),    
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

    Switch::Position sw1Last_ = sw1_.readPos();
    Switch::Position sw2Last_ = sw2_.readPos();
    Switch::Position sw3Last_ = sw3_.readPos();
    Switch::Position sw4Last_ = sw4_.readPos();
    Switch::Position sw5Last_ = sw5_.readPos();
    Switch::Position sw6Last_ = sw6_.readPos();
    Switch::Position sw7Last_ = sw7_.readPos();
    Switch::Position sw8Last_ = sw8_.readPos();
    Switch::Position sw9Last_ = sw9_.readPos();
    Switch::Position sw10Last_= sw10_.readPos();
    Switch::Position sw11Last_= sw11_.readPos();
    Switch::Position sw12Last_= sw12_.readPos();
  }

  void setLed(int id, bool enable);
  void readSwitches();

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

  Switch::Position sw1Last_;
  Switch::Position sw2Last_;
  Switch::Position sw3Last_;
  Switch::Position sw4Last_;
  Switch::Position sw5Last_;
  Switch::Position sw6Last_;
  Switch::Position sw7Last_;
  Switch::Position sw8Last_;
  Switch::Position sw9Last_;
  Switch::Position sw10Last_;
  Switch::Position sw11Last_;
  Switch::Position sw12Last_;

  Registers reg_;
  // --
  
private:
  OnSwitchPositionChange onSwitchPositionChange_;  
};

void SchalterWand::setLed(int id, bool enable) {
  switch(id) {
    case 1: reg_.r3_.LED_1 = enable ? 1 : 0;
    case 2: reg_.r3_.LED_2 = enable ? 1 : 0;
    case 3: reg_.r2_.LED_3 = enable ? 1 : 0;
    case 4: reg_.r2_.LED_4 = enable ? 1 : 0;
    case 5: reg_.r3_.LED_5 = enable ? 1 : 0;
    case 6: reg_.r3_.LED_6 = enable ? 1 : 0;
    case 7: reg_.r2_.LED_7 = enable ? 1 : 0;
    case 8: reg_.r2_.LED_8 = enable ? 1 : 0;
  }
}

void SchalterWand::readSwitches() {
  Switch::Position sw1Cur_ = sw1_.readPos();
  Switch::Position sw2Cur_ = sw2_.readPos();
  Switch::Position sw3Cur_ = sw3_.readPos();
  Switch::Position sw4Cur_ = sw4_.readPos();
  Switch::Position sw5Cur_ = sw5_.readPos();
  Switch::Position sw6Cur_ = sw6_.readPos();
  Switch::Position sw7Cur_ = sw7_.readPos();
  Switch::Position sw8Cur_ = sw8_.readPos();
  Switch::Position sw9Cur_ = sw9_.readPos();
  Switch::Position sw10Cur_ = sw10_.readPos();
  Switch::Position sw11Cur_ = sw11_.readPos();
  Switch::Position sw12Cur_ = sw12_.readPos();

  if (sw1Cur_   != sw1Last_)   onSwitchPositionChange_(1, sw1Cur_);
  if (sw2Cur_   != sw2Last_)   onSwitchPositionChange_(2, sw2Cur_);
  if (sw3Cur_   != sw3Last_)   onSwitchPositionChange_(3, sw3Cur_);
  if (sw4Cur_   != sw4Last_)   onSwitchPositionChange_(4, sw4Cur_);
  if (sw5Cur_   != sw5Last_)   onSwitchPositionChange_(5, sw5Cur_);
  if (sw6Cur_   != sw6Last_)   onSwitchPositionChange_(6, sw6Cur_);
  if (sw7Cur_   != sw7Last_)   onSwitchPositionChange_(7, sw7Cur_);
  if (sw8Cur_   != sw8Last_)   onSwitchPositionChange_(8, sw8Cur_);
  if (sw9Cur_   != sw9Last_)   onSwitchPositionChange_(9, sw9Cur_);
  if (sw10Cur_ != sw10Last_) onSwitchPositionChange_(10, sw10Cur_);
  if (sw11Cur_ != sw11Last_) onSwitchPositionChange_(11, sw11Cur_);
  if (sw12Cur_ != sw12Last_) onSwitchPositionChange_(12, sw12Cur_);
}

void onSwitchPositionChange(int id, Switch::Position pos) {
  Serial.print("SW");
  Serial.print(id);
  Serial.print(": ");
  Serial.println(Switch::posToString(pos));
}

SchalterWand _schalterWand(onSwitchPositionChange);

void setup() {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);  
  pinMode(LATCH, OUTPUT);

  Serial.begin(115200);
  SPI.begin();

  _schalterWand.setLed(1, true);
  _schalterWand.setLed(2, false);
  _schalterWand.setLed(3, false);
  _schalterWand.setLed(4, false);
  _schalterWand.setLed(5, false);
  _schalterWand.setLed(6, false);
  _schalterWand.setLed(7, false);
  _schalterWand.setLed(8, false);
}

void loop() {
  _schalterWand.readSwitches();

  /*
    Serial.print("SW1: ");   Serial.print(Switch::posToString(_schalterWand.sw1_.readPos()));   Serial.print(", ");
    Serial.print("SW2: ");   Serial.print(Switch::posToString(_schalterWand.sw2_.readPos()));   Serial.print(", ");
    Serial.print("SW3: ");   Serial.print(Switch::posToString(_schalterWand.sw3_.readPos()));   Serial.print(", ");
    Serial.print("SW4: ");   Serial.print(Switch::posToString(_schalterWand.sw4_.readPos()));   Serial.print(", ");
    Serial.print("SW5: ");   Serial.print(Switch::posToString(_schalterWand.sw5_.readPos()));   Serial.print(", ");
    Serial.print("SW6: ");   Serial.print(Switch::posToString(_schalterWand.sw6_.readPos()));   Serial.print(", ");
    Serial.print("SW7: ");   Serial.print(Switch::posToString(_schalterWand.sw7_.readPos()));   Serial.print(", ");
    Serial.print("SW8: ");   Serial.print(Switch::posToString(_schalterWand.sw8_.readPos()));   Serial.print(", ");
    Serial.print("SW9: ");   Serial.print(Switch::posToString(_schalterWand.sw9_.readPos()));   Serial.print(", ");
    Serial.print("SW10: "); Serial.print(Switch::posToString(_schalterWand.sw10_.readPos())); Serial.print(", ");
    Serial.print("SW11: "); Serial.print(Switch::posToString(_schalterWand.sw11_.readPos())); Serial.print(", ");
    Serial.print("SW12: "); Serial.print(Switch::posToString(_schalterWand.sw12_.readPos())); Serial.print(", ");
  */
}

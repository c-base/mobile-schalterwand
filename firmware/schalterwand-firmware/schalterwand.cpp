#include <SPI.h>
#include "schalterwand.h"

#define BL1 2
#define BL2 5
#define BL3 3
#define BL4 4
#define LATCH A2

#define readWire(Y, Br, Bl, enY, enBr) ({  \
  bool __wireState;                                           \
  {                                                                        \
    Y = enY;                                                         \
    Br = enBr;                                                     \
    pReg_->write();                                            \
                                                                           \
    __wireState = digitalRead(Bl);                  \
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

#define readWires(Y, Br, Bl) ({                             \
  WireStates __states;                                              \
  {                                                                                 \
    __states.brown = readBrownWire(Y, Br, Bl);  \
    __states.yellow = readYellowWire(Y, Br, Bl);  \
  }                                                                                 \
                                                                                     \
  __states;                                                                   \
})

//------------------------------------------
// Registers
//------------------------------------------

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

Switch::Position Switch::readPos() {
  WireStates states = getWireStates();

  if(states.brown)
    return Position::Down;
  else if (states.yellow)
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

WireStates Sw1:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL4); 
}

WireStates Sw2:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL4);
}

WireStates Sw3:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL3);
}

WireStates Sw4:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL3);
}

WireStates Sw5:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL1);
}

WireStates Sw6:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL1);
}

WireStates Sw7:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL2);
}

WireStates Sw8:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL2);
}

WireStates Sw9:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL1);
}

WireStates Sw10:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL4);
}

WireStates Sw11:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL3);
}

WireStates Sw12:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL2);
}

//------------------------------------------
// SchalterWand
//------------------------------------------

void SchalterWand::begin() {  
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);  
  pinMode(LATCH, OUTPUT);
  SPI.begin();
}

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

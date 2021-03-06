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
// SchalterWandRegisters
//------------------------------------------

void SchalterWandRegisters::write() {
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
// SchalterWandSwitch
//------------------------------------------

SchalterWandSwitch::Position SchalterWandSwitch::readPos() {
  WireStates states = getWireStates();

  if(states.brown)
    return Position::Down;
  else if (states.yellow)
    return Position::Up;
  else
    return Position::LeftOrRight;
}

const char* SchalterWandSwitch::posToString(Position pos) {
  switch(pos) {
    case SchalterWandSwitch::Position::Down: return "Down";
    case SchalterWandSwitch::Position::Up: return "Up";
    case SchalterWandSwitch::Position::LeftOrRight: return "Left or Right";

    default: return "Invalid";
  }
}

SchalterWandSwitch::WireStates Sw1:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL4); 
}

SchalterWandSwitch::WireStates Sw2:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL4);
}

SchalterWandSwitch::WireStates Sw3:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL3);
}

SchalterWandSwitch::WireStates Sw4:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL3);
}

SchalterWandSwitch::WireStates Sw5:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL1);
}

SchalterWandSwitch::WireStates Sw6:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL1);
}

SchalterWandSwitch::WireStates Sw7:: getWireStates() {
  return readWires(pReg_->r2_.Y2, pReg_->r1_.Br2, BL2);
}

SchalterWandSwitch::WireStates Sw8:: getWireStates() {
  return readWires(pReg_->r1_.Y1, pReg_->r2_.Br1, BL2);
}

SchalterWandSwitch::WireStates Sw9:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL1);
}

SchalterWandSwitch::WireStates Sw10:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL4);
}

SchalterWandSwitch::WireStates Sw11:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL3);
}

SchalterWandSwitch::WireStates Sw12:: getWireStates() {
  return readWires(pReg_->r2_.Y3, pReg_->r2_.Br3, BL2);
}

//------------------------------------------
// SchalterWandObj
//------------------------------------------

void SchalterWandObj::begin(OnSwitchPositionChange onSwitchPositionChange) {
  pinMode(BL1, INPUT);
  pinMode(BL2, INPUT);
  pinMode(BL3, INPUT);
  pinMode(BL4, INPUT);  
  pinMode(LATCH, OUTPUT);
  SPI.begin();

  onSwitchPositionChange_ = onSwitchPositionChange;
}

void SchalterWandObj::setLed(int id, bool enable) {
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

  reg_.write();
}

void SchalterWandObj::tick() {
  SchalterWandSwitch::Position sw1Cur_ = sw1.readPos();
  SchalterWandSwitch::Position sw2Cur_ = sw2.readPos();
  SchalterWandSwitch::Position sw3Cur_ = sw3.readPos();
  SchalterWandSwitch::Position sw4Cur_ = sw4.readPos();
  SchalterWandSwitch::Position sw5Cur_ = sw5.readPos();
  SchalterWandSwitch::Position sw6Cur_ = sw6.readPos();
  SchalterWandSwitch::Position sw7Cur_ = sw7.readPos();
  SchalterWandSwitch::Position sw8Cur_ = sw8.readPos();
  SchalterWandSwitch::Position sw9Cur_ = sw9.readPos();
  SchalterWandSwitch::Position sw10Cur_ = sw10.readPos();
  SchalterWandSwitch::Position sw11Cur_ = sw11.readPos();
  SchalterWandSwitch::Position sw12Cur_ = sw12.readPos();

  if (!onSwitchPositionChange_)
    return;

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

#ifdef _SCHALTERWAND_H
  SchalterWandObj SchalterWand;
#endif // _SCHALTERWAND_H

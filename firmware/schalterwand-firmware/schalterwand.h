#ifndef _SCHALTERWAND_H
#define _SCHALTERWAND_H

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

struct WireStates {
  bool brown;
  bool yellow;
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

  Switch(Registers* pReg) : pReg_(pReg) { }
  Switch::Position readPos();
  static const char* posToString(Position pos);

protected:
  Registers* const pReg_; // TODO: make private
  
private:
  virtual WireStates getWireStates() = 0;
};

// SW1:  Y1, Br1, Bl4
class Sw1 : public Switch {
public:
  Sw1(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW2: Y2, Br2, Bl4
class Sw2 : public Switch {
public:
  Sw2(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW3: Y2, Br2, Bl3
class Sw3 : public Switch {
public:
  Sw3(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW4: Y1, Br1, Bl3
class Sw4 : public Switch {
public:
  Sw4(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW5: Y1, Br1, Bl1
class Sw5 : public Switch {
public:
  Sw5(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW6: Y2, Br2, Bl1
class Sw6 : public Switch {
public:
  Sw6(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW7: Y2, Br2, Bl2
class Sw7 : public Switch {
public:
  Sw7(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW8: Y1, Br1, Bl2
class Sw8 : public Switch {
public:
  Sw8(Registers* pReg) : Switch(pReg) {}

private:  
  virtual WireStates getWireStates() final override;
};

// SW9: Y3, Br3, Bl1
class Sw9 : public Switch {
public:
  Sw9(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW10: Y3, Br3, Bl4
class Sw10 : public Switch {
public:
  Sw10(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW11: Y3, Br3, Bl3
class Sw11 : public Switch {
public:
  Sw11(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW12, Y3, Br3, Bl2
class Sw12 : public Switch {
public:
  Sw12(Registers* pReg) : Switch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

//------------------------------------------
// SchalterWandObj
//------------------------------------------

typedef void (*OnSwitchPositionChange)(int id, Switch::Position pos);

class SchalterWandObj {
public:
  SchalterWandObj() :
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

  void begin(OnSwitchPositionChange onSwitchPositionChange);
  void setLed(int id, bool enable);
  void readSwitches();
    
private:
  Registers reg_;
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
  OnSwitchPositionChange onSwitchPositionChange_{nullptr};
};

extern SchalterWandObj SchalterWand;

#endif // !_SCHALTERWAND_H

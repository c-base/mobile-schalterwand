#ifndef _SCHALTERWAND_H
#define _SCHALTERWAND_H

//------------------------------------------
// SchalterWandRegisters
//------------------------------------------

class SchalterWandRegisters {
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

//------------------------------------------
// SchalterWandSwitch
//------------------------------------------

class SchalterWandSwitch {
public:
  enum class Position {
    Invalid,
    LeftOrRight,
    Down,
    Up,
  };

  struct WireStates {
    bool brown;
    bool yellow;
  };

  SchalterWandSwitch(SchalterWandRegisters* pReg) : pReg_(pReg) { }
  SchalterWandSwitch::Position readPos();
  static const char* posToString(Position pos);

protected:
  SchalterWandRegisters* const pReg_; // TODO: make private
  
private:
  virtual WireStates getWireStates() = 0;
};

// SW1:  Y1, Br1, Bl4
class Sw1 : public SchalterWandSwitch {
public:
  Sw1(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW2: Y2, Br2, Bl4
class Sw2 : public SchalterWandSwitch {
public:
  Sw2(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW3: Y2, Br2, Bl3
class Sw3 : public SchalterWandSwitch {
public:
  Sw3(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW4: Y1, Br1, Bl3
class Sw4 : public SchalterWandSwitch {
public:
  Sw4(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW5: Y1, Br1, Bl1
class Sw5 : public SchalterWandSwitch {
public:
  Sw5(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW6: Y2, Br2, Bl1
class Sw6 : public SchalterWandSwitch {
public:
  Sw6(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW7: Y2, Br2, Bl2
class Sw7 : public SchalterWandSwitch {
public:
  Sw7(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW8: Y1, Br1, Bl2
class Sw8 : public SchalterWandSwitch {
public:
  Sw8(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:  
  virtual WireStates getWireStates() final override;
};

// SW9: Y3, Br3, Bl1
class Sw9 : public SchalterWandSwitch {
public:
  Sw9(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW10: Y3, Br3, Bl4
class Sw10 : public SchalterWandSwitch {
public:
  Sw10(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW11: Y3, Br3, Bl3
class Sw11 : public SchalterWandSwitch {
public:
  Sw11(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

// SW12, Y3, Br3, Bl2
class Sw12 : public SchalterWandSwitch {
public:
  Sw12(SchalterWandRegisters* pReg) : SchalterWandSwitch(pReg) {}

private:
  virtual WireStates getWireStates() final override;
};

//------------------------------------------
// SchalterWandObj
//------------------------------------------

typedef void (*OnSwitchPositionChange)(int id, SchalterWandSwitch::Position pos);

class SchalterWandObj {
public:
  SchalterWandObj() :
      sw1(&reg_),
      sw2(&reg_),
      sw3(&reg_),
      sw4(&reg_),
      sw5(&reg_),
      sw6(&reg_),
      sw7(&reg_),
      sw8(&reg_),
      sw9(&reg_),
      sw10(&reg_),
      sw11(&reg_),
      sw12(&reg_) {

    SchalterWandSwitch::Position sw1Last_ = sw1.readPos();
    SchalterWandSwitch::Position sw2Last_ = sw2.readPos();
    SchalterWandSwitch::Position sw3Last_ = sw3.readPos();
    SchalterWandSwitch::Position sw4Last_ = sw4.readPos();
    SchalterWandSwitch::Position sw5Last_ = sw5.readPos();
    SchalterWandSwitch::Position sw6Last_ = sw6.readPos();
    SchalterWandSwitch::Position sw7Last_ = sw7.readPos();
    SchalterWandSwitch::Position sw8Last_ = sw8.readPos();
    SchalterWandSwitch::Position sw9Last_ = sw9.readPos();
    SchalterWandSwitch::Position sw10Last_= sw10.readPos();
    SchalterWandSwitch::Position sw11Last_= sw11.readPos();
    SchalterWandSwitch::Position sw12Last_= sw12.readPos();
  }

  void begin(OnSwitchPositionChange onSwitchPositionChange);
  void setLed(int id, bool enable);
  void tick();

  Sw1 sw1;
  Sw2 sw2;
  Sw3 sw3;
  Sw4 sw4;
  Sw5 sw5;
  Sw6 sw6;
  Sw7 sw7;
  Sw8 sw8;
  Sw9 sw9;
  Sw10 sw10;
  Sw11 sw11;
  Sw12 sw12;
    
private:
  SchalterWandRegisters reg_;

  SchalterWandSwitch::Position sw1Last_;
  SchalterWandSwitch::Position sw2Last_;
  SchalterWandSwitch::Position sw3Last_;
  SchalterWandSwitch::Position sw4Last_;
  SchalterWandSwitch::Position sw5Last_;
  SchalterWandSwitch::Position sw6Last_;
  SchalterWandSwitch::Position sw7Last_;
  SchalterWandSwitch::Position sw8Last_;
  SchalterWandSwitch::Position sw9Last_;
  SchalterWandSwitch::Position sw10Last_;
  SchalterWandSwitch::Position sw11Last_;
  SchalterWandSwitch::Position sw12Last_;
  OnSwitchPositionChange onSwitchPositionChange_{nullptr};
};

extern SchalterWandObj SchalterWand;

#endif // !_SCHALTERWAND_H

#include "schalterwand.h"

void onSwitchPositionChange(int id, Switch::Position pos) {
  Serial.print("SW");
  Serial.print(id);
  Serial.print(": ");
  Serial.println(Switch::posToString(pos));
}

SchalterWand _schalterWand(onSwitchPositionChange);

void setup() {  
  Serial.begin(115200);
  SchalterWand::begin(); // TODO: use dot notation like in Serial library
  
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

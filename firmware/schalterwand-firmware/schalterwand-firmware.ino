#include "schalterwand.h"

void onSwitchPositionChange(int id, Switch::Position pos) {
  Serial.print("SW");
  Serial.print(id);
  Serial.print(": ");
  Serial.println(Switch::posToString(pos));
}

void setup() {
  Serial.begin(115200);
  SchalterWand.begin(onSwitchPositionChange);
  
  SchalterWand.setLed(1, true);
  SchalterWand.setLed(2, false);
  SchalterWand.setLed(3, false);
  SchalterWand.setLed(4, false);
  SchalterWand.setLed(5, false);
  SchalterWand.setLed(6, false);
  SchalterWand.setLed(7, false);
  SchalterWand.setLed(8, false);
}

void loop() {
  SchalterWand.readSwitches();

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

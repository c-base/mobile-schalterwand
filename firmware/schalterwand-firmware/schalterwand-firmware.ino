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
  Serial.print("SW1: ");   Serial.print(Switch::posToString(SchalterWand.sw1.readPos()));   Serial.print(", ");
  Serial.print("SW2: ");   Serial.print(Switch::posToString(SchalterWand.sw2.readPos()));   Serial.print(", ");
  Serial.print("SW3: ");   Serial.print(Switch::posToString(SchalterWand.sw3.readPos()));   Serial.print(", ");
  Serial.print("SW4: ");   Serial.print(Switch::posToString(SchalterWand.sw4.readPos()));   Serial.print(", ");
  Serial.print("SW5: ");   Serial.print(Switch::posToString(SchalterWand.sw5.readPos()));   Serial.print(", ");
  Serial.print("SW6: ");   Serial.print(Switch::posToString(SchalterWand.sw6.readPos()));   Serial.print(", ");
  Serial.print("SW7: ");   Serial.print(Switch::posToString(SchalterWand.sw7.readPos()));   Serial.print(", ");
  Serial.print("SW8: ");   Serial.print(Switch::posToString(SchalterWand.sw8.readPos()));   Serial.print(", ");
  Serial.print("SW9: ");   Serial.print(Switch::posToString(SchalterWand.sw9.readPos()));   Serial.print(", ");
  Serial.print("SW10: "); Serial.print(Switch::posToString(SchalterWand.sw10.readPos())); Serial.print(", ");
  Serial.print("SW11: "); Serial.print(Switch::posToString(SchalterWand.sw11.readPos())); Serial.print(", ");
  Serial.print("SW12: "); Serial.print(Switch::posToString(SchalterWand.sw12.readPos())); Serial.print(", ");
*/
}

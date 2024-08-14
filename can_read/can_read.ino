//teensy3.2でとりあえず読むサンプル
#include <FlexCAN.h>

FlexCAN CANbus(1000000);
static CAN_message_t rxmsg;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  CANbus.begin();
}

void loop() {
  while ( CANbus.read(rxmsg) ) {
    if (rxmsg.id == 0x100) {
      Serial.println(rxmsg.buf[0],BIN);
      Serial.println(rxmsg.buf[1],BIN);
      Serial.print(rxmsg.buf[2]);
      Serial.print(",");
      Serial.print(rxmsg.buf[3]);
      Serial.print(",");
      Serial.print(rxmsg.buf[4]);
      Serial.print(",");
      Serial.println(rxmsg.buf[5]);
      Serial.println("");
    }
  }
  delay(50);
}

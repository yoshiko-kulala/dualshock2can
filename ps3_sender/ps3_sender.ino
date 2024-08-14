#include <Arduino.h>
#include <CAN.h>
#include <Ps3Controller.h>

int8_t buf[6] = {0};

void notify()
{
  if ( Ps3.event.button_down.cross )
    buf[0] = buf[0] | 0x04;
  if ( Ps3.event.button_up.cross )
    buf[0] = buf[0] & 0xFB;

  if ( Ps3.event.button_down.square )
    buf[0] = buf[0] | 0x01;
  if ( Ps3.event.button_up.square )
    buf[0] = buf[0] & 0xFE;

  if ( Ps3.event.button_down.triangle )
    buf[0] = buf[0] | 0x08;
  if ( Ps3.event.button_up.triangle )
    buf[0] = buf[0] & 0xF7;

  if ( Ps3.event.button_down.circle )
    buf[0] = buf[0] | 0x02;
  if ( Ps3.event.button_up.circle )
    buf[0] = buf[0] & 0xFD;

  if ( Ps3.event.button_down.up )
    buf[0] = buf[0] | 0x80;
  if ( Ps3.event.button_up.up )
    buf[0] = buf[0] & 0x7F;

  if ( Ps3.event.button_down.right )
    buf[0] = buf[0] | 0x20;
  if ( Ps3.event.button_up.right )
    buf[0] = buf[0] & 0xDF;

  if ( Ps3.event.button_down.down )
    buf[0] = buf[0] | 0x40;
  if ( Ps3.event.button_up.down )
    buf[0] = buf[0] & 0xBF;

  if ( Ps3.event.button_down.left )
    buf[0] = buf[0] | 0x10;
  if ( Ps3.event.button_up.left )
    buf[0] = buf[0] & 0xEF;

  if ( Ps3.event.button_down.l1 )
    buf[1] = buf[1] | 0x40;
  if ( Ps3.event.button_up.l1 )
    buf[1] = buf[1] & 0xBF;

  if ( Ps3.event.button_down.r1 )
    buf[1] = buf[1] | 0x80;
  if ( Ps3.event.button_up.r1 )
    buf[1] = buf[1] & 0x7F;

  if ( Ps3.event.button_down.l2 )
    buf[1] = buf[1] | 0x10;
  if ( Ps3.event.button_up.l2 )
    buf[1] = buf[1] & 0xEF;

  if ( Ps3.event.button_down.r2 )
    buf[1] = buf[1] | 0x20;
  if ( Ps3.event.button_up.r2 )
    buf[1] = buf[1] & 0xDF;

  if ( Ps3.event.button_down.l3 )
    buf[1] = buf[1] | 0x04;
  if ( Ps3.event.button_up.l3 )
    buf[1] = buf[1] & 0xFB;

  if ( Ps3.event.button_down.r3 )
    buf[1] = buf[1] | 0x08;
  if ( Ps3.event.button_up.r3 )
    buf[1] = buf[1] & 0xF7;

  if ( Ps3.event.button_down.select )
    buf[1] = buf[1] | 0x01;
  if ( Ps3.event.button_up.select )
    buf[1] = buf[1] & 0xFE;

  if ( Ps3.event.button_down.start )
    buf[1] = buf[1] | 0x02;
  if ( Ps3.event.button_up.start )
    buf[1] = buf[1] & 0xFD;

  buf[2] = Ps3.data.analog.stick.rx+127;
  buf[3] = Ps3.data.analog.stick.ry+127;
  buf[4] = Ps3.data.analog.stick.lx+127;
  buf[5] = Ps3.data.analog.stick.ly+127;
}

void onConnect() {
  Serial.println("Connected.");
}

void setup() {
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);

  Ps3.begin("FC:F5:C4:45:5F:82");

  CAN.setPins(26, 27);
  if (!CAN.begin(1000E3)) {
    while (1);
  }
}

void loop() {
  if (!Ps3.isConnected())
    return;

  CAN.beginPacket(0x100);
  for (int i = 0; i < 6; i++) {
    CAN.write(buf[i]);
  }
  CAN.endPacket();

  delay(100);
}

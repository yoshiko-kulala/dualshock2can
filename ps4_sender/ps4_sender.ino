#include <CAN.h>
#include <PS4Controller.h>

uint8_t buf[6] = { 0 };

void setup() {
  Serial.begin(115200);
  PS4.begin("FC:F5:C4:45:82:72");
  Serial.println("Ready.");
  CAN.setPins(26, 27);
  if (!CAN.begin(1000E3)) {
    while (1)
      ;
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (i < 2) buf[i] = 0;
    else buf[i] = 127;
  }
  if (PS4.isConnected()) {
    if (PS4.Right())buf[0] = buf[0] | 0x20;
    if (PS4.Down())buf[0] = buf[0] | 0x40;
    if (PS4.Up())buf[0] = buf[0] | 0x80;
    if (PS4.Left())buf[0] = buf[0] | 0x10;

    if (PS4.Square())buf[0] = buf[0] | 0x01;
    if (PS4.Cross())buf[0] = buf[0] | 0x04;
    if (PS4.Circle())buf[0] = buf[0] | 0x02;
    if (PS4.Triangle())buf[0] = buf[0] | 0x08;

    if (PS4.L1())buf[1] = buf[1] | 0x40;
    if (PS4.R1())buf[1] = buf[1] | 0x80;

    if (PS4.Share())buf[1] = buf[1] | 0x01;
    if (PS4.Options())buf[1] = buf[1] | 0x02;
    if (PS4.L3())buf[1] = buf[1] | 0x04;
    if (PS4.R3())buf[1] = buf[1] | 0x08;


    if (PS4.L2())buf[1] = buf[1] | 0x10;
    if (PS4.R2())buf[1] = buf[1] | 0x20;

    buf[2] = PS4.RStickX() + 128;
    buf[3] = PS4.RStickY() + 128;
    buf[4] = PS4.LStickX() + 128;
    buf[5] = PS4.LStickY() + 128;
  }
  CAN.beginPacket(0x100);
  for (int i = 0; i < 6; i++) {
    CAN.write(buf[i]);
  }
  CAN.endPacket();
  delay(100);
}

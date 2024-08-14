# dualshock2can  
## これはなに  
ESP32でPS3やPS4のコントローラの信号を読んでCANに流すプログラム  

## 動作環境  
恐らく依存しているのはこれくらい  
- [arduino-esp32](https://github.com/espressif/arduino-esp32)  
  v3.0.4
- [PS4-esp32](https://github.com/AzSaSiN/PS4-esp32)  
  PS4コントローラ受信用  
  folk元はこの環境だと動かない
- [esp32-ps3](https://github.com/jvpernis/esp32-ps3)  
  PS3コントローラ受信用  
  v1.1.0
- [arduino-CAN](https://github.com/sandeepmistry/arduino-CAN)  
  v0.3.1
  ESP32からCANを送るやつ



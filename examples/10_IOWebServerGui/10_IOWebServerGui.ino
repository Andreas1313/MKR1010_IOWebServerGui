#ifndef ARDUINO_SAMD_MKRWIFI1010
  #error "This library is only tested (compatible) with the Arduino MKR WiFi 1010."
#endif

#include "IOWebServerGui.h"
ClassIOWebServerGui iOWebServerGui;

// Pin modes: 0=analog input, 1=digital output, 2=PWM output, 3=digital input, 4=digital input pullup, 5=DAC output (A0 only)
int a0Mode = 5, a1Mode = 0, a2Mode = 1, a3Mode = 2, a4Mode = 3, a5Mode = 4, a6Mode = 0,
    d0Mode = 1, d1Mode = 2, d2Mode = 3, d3Mode = 4, d4Mode = 1, d5Mode = 1, d6Mode = 3, d7Mode = 1, d8Mode = 1, d9Mode = 1, d10Mode = 1, d11Mode = 1, d12Mode = 1,
    ledRedMode = 2, ledGreenMode = 2, ledBlueMode = 2;
bool a0State = false, a1State = true, a2State = false, a3State = false, a4State = false, a5State = false, a6State = false,
    d0State = false, d1State = false, d2State = false, d3State = false, d4State = false, d5State = false, d6State = false, d7State = false, d8State = false, d9State = false, d10State = false, d11State = false, d12State = false;
int a0PWMValue = 0, a1PWMValue = 0, a2PWMValue = 0, a3PWMValue = 50, a4PWMValue = 0, a5PWMValue = 0, a6PWMValue = 0,
    d0PWMValue = 0, d1PWMValue = 60, d2PWMValue = 0, d3PWMValue = 0, d4PWMValue = 0, d5PWMValue = 0, d6PWMValue = 0, d7PWMValue = 0, d8PWMValue = 0, d9PWMValue = 0, d10PWMValue = 0, d11PWMValue = 0, d12PWMValue = 0,
    a0DACValue = 0,
    ledRedValue = 0, ledGreenValue = 40, ledBlueValue = 0;

void setup() {
  Serial.begin(1200);
  //while ( ! Serial){}
  delay(100);
  iOWebServerGui.setupIOWebServerGui();

  iOWebServerGui.setMode(a0Mode, a1Mode, a2Mode, a3Mode, a4Mode, a5Mode, a6Mode,
      d0Mode, d1Mode, d2Mode, d3Mode, d4Mode, d5Mode, d6Mode, d7Mode, d8Mode, d9Mode, d10Mode, d11Mode, d12Mode,
      ledRedMode, ledGreenMode, ledBlueMode);
  iOWebServerGui.setState(a0State, a1State, a2State, a3State, a4State, a5State, a6State,
      d0State, d1State, d2State, d3State, d4State, d5State, d6State, d7State, d8State, d9State, d10State, d11State, d12State);
  iOWebServerGui.setValue(a0PWMValue, a1PWMValue, a2PWMValue, a3PWMValue, a4PWMValue, a5PWMValue, a6PWMValue, d0PWMValue, d1PWMValue, d2PWMValue, d3PWMValue, d4PWMValue, d5PWMValue, d6PWMValue, d7PWMValue, d8PWMValue, d9PWMValue, d10PWMValue, d11PWMValue, d12PWMValue,
      a0DACValue,
      ledRedValue, ledGreenValue, ledBlueValue);
}

void loop() {
  iOWebServerGui.loopIOWebServerGui();
}
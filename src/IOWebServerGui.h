#pragma once

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include "arduino_secrets.h"
#include <Arduino.h>

class ClassIOWebServerGui{
 private:

  const char*  _ssid = SECRET_SSID;
  const char*  _pass = SECRET_PASS;
  int _status = WL_IDLE_STATUS;

  // Pin modes: 0=analog input, 1=digital output, 2=PWM output, 3=digital input, 4=digital input pullup, 5=DAC output (A0 only)
  int _a0Mode = 0, _a1Mode = 0, _a2Mode = 0, _a3Mode = 0, _a4Mode = 0, _a5Mode = 0, _a6Mode = 0,
      _d0Mode = 4, _d1Mode = 4, _d2Mode = 4, _d3Mode = 4, _d4Mode = 4, _d5Mode = 4, _d6Mode = 4, _d7Mode = 4, _d8Mode = 4, _d9Mode = 4, _d10Mode = 4, _d11Mode = 4, _d12Mode = 4,
      _ledRedMode = 2, _ledGreenMode = 2, _ledBlueMode = 2;
  bool _a0State = false, _a1State = false, _a2State = false, _a3State = false, _a4State = false, _a5State = false, _a6State = false,
       _d0State = false, _d1State = false, _d2State = false, _d3State = false, _d4State = false, _d5State = false, _d6State = false, _d7State = false, _d8State = false, _d9State = false, _d10State = false, _d11State = false, _d12State = false;
  int _a0PWMValue = 0, _a1PWMValue = 0, _a2PWMValue = 0, _a3PWMValue = 0, _a4PWMValue = 0, _a5PWMValue = 0, _a6PWMValue = 0,
      _d0PWMValue = 0, _d1PWMValue = 0, _d2PWMValue = 0, _d3PWMValue = 0, _d4PWMValue = 0, _d5PWMValue = 0, _d6PWMValue = 0, _d7PWMValue = 0, _d8PWMValue = 0, _d9PWMValue = 0, _d10PWMValue = 0, _d11PWMValue = 0, _d12PWMValue = 0,
      _a0DACValue = 0,
      _ledRedValue = 0, _ledGreenValue = 0, _ledBlueValue = 0;

  void sendValuesJSON(WiFiClient &client);

  String getPinValue(int pin, int mode, bool state, int pwmValue, int dacValue);
  void sendHTMLPage(WiFiClient &client);
  void generatePinRow(WiFiClient &client, String pinName, String pinId, int mode, bool state, int pwmValue, int dacValue, bool hasPWM, bool hasDAC);
  void generatePinRowDigital(WiFiClient &client, String pinName, String pinId, int mode, bool state, int pwmValue, bool hasPWM);
  void generatePinRowRGB(WiFiClient &client, String pinName, String pinId, int mode, int value);
  void handleRequests(String request);
  void setPinMode(int pin, int mode);
  void printWiFiStatus();

 public:
  ClassIOWebServerGui();

  void setupIOWebServerGui();
  void loopIOWebServerGui();

  void setMode(int a0Mode, int a1Mode, int a2Mode, int a3Mode, int a4Mode, int a5Mode, int a6Mode,
               int d0Mode, int d1Mode, int d2Mode, int d3Mode, int d4Mode, int d5Mode, int d6Mode, int d7Mode, int d8Mode, int d9Mode, int d10Mode, int d11Mode, int d12Mode,
               int ledRedMode, int ledGreenMode, int ledBlueMode);
  void setState(bool a0State, bool a1State, bool a2State, bool a3State, bool a4State, bool a5State, bool a6State,
       bool d0State, bool d1State, bool d2State, bool d3State, bool d4State, bool d5State, bool d6State, bool d7State, bool d8State, bool d9State, bool d10State, bool d11State, bool d12State);
  void setValue(int a0PWMValue, int a1PWMValue, int a2PWMValue, int a3PWMValue, int a4PWMValue, int a5PWMValue, int a6PWMValue,
      int d0PWMValue, int d1PWMValue, int d2PWMValue, int d3PWMValue, int d4PWMValue, int d5PWMValue, int d6PWMValue, int d7PWMValue, int d8PWMValue, int d9PWMValue, int d10PWMValue, int d11PWMValue, int d12PWMValue,
      int a0DACValue,
      int ledRedValue, int ledGreenValue, int ledBlueValue);
};
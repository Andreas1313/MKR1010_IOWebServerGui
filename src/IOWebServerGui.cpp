#include "IOWebServerGui.h"
WiFiServer server(80);
//private:
void ClassIOWebServerGui::sendValuesJSON(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: application/json");
  client.println("Connection: close");
  client.println();
  
  client.println("{");
  client.println("\"a0\":" + String(getPinValue(A0, _a0Mode, _a0State, _a0PWMValue, _a0DACValue)) + ",");
  client.println("\"a1\":" + String(getPinValue(A1, _a1Mode, _a1State, _a1PWMValue, 0)) + ",");
  client.println("\"a2\":" + String(getPinValue(A2, _a2Mode, _a2State, _a2PWMValue, 0)) + ",");
  client.println("\"a3\":" + String(getPinValue(A3, _a3Mode, _a3State, _a3PWMValue, 0)) + ",");
  client.println("\"a4\":" + String(getPinValue(A4, _a4Mode, _a4State, _a4PWMValue, 0)) + ",");
  client.println("\"a5\":" + String(getPinValue(A5, _a5Mode, _a5State, _a5PWMValue, 0)) + ",");
  client.println("\"a6\":" + String(getPinValue(A6, _a6Mode, _a6State, _a6PWMValue, 0)) + ",");
  client.println("\"d0\":" + String(getPinValue(0, _d0Mode, _d0State, _d0PWMValue, 0)) + ",");
  client.println("\"d1\":" + String(getPinValue(1, _d1Mode, _d1State, _d1PWMValue, 0)) + ",");
  client.println("\"d2\":" + String(getPinValue(2, _d2Mode, _d2State, _d2PWMValue, 0)) + ",");
  client.println("\"d3\":" + String(getPinValue(3, _d3Mode, _d3State, _d3PWMValue, 0)) + ",");
  client.println("\"d4\":" + String(getPinValue(4, _d4Mode, _d4State, _d4PWMValue, 0)) + ",");
  client.println("\"d5\":" + String(getPinValue(5, _d5Mode, _d5State, _d5PWMValue, 0)) + ",");
  client.println("\"d6\":" + String(getPinValue(6, _d6Mode, _d6State, _d6PWMValue, 0)) + ",");
  client.println("\"d7\":" + String(getPinValue(7, _d7Mode, _d7State, _d7PWMValue, 0)) + ",");
  client.println("\"d8\":" + String(getPinValue(8, _d8Mode, _d8State, _d8PWMValue, 0)) + ",");
  client.println("\"d9\":" + String(getPinValue(9, _d9Mode, _d9State, _d9PWMValue, 0)) + ",");
  client.println("\"d10\":" + String(getPinValue(10, _d10Mode, _d10State, _d10PWMValue, 0)) + ",");
  client.println("\"d11\":" + String(getPinValue(11, _d11Mode, _d11State, _d11PWMValue, 0)) + ",");
  client.println("\"d12\":" + String(getPinValue(12, _d12Mode, _d12State, _d12PWMValue, 0)) + ",");
  client.println("\"ledRed\":" + String(_ledRedValue) + ",");
  client.println("\"ledGreen\":" + String(_ledGreenValue) + ",");
  client.println("\"ledBlue\":" + String(_ledBlueValue) + "");
  client.println("}");
}

String ClassIOWebServerGui::getPinValue(int pin, int mode, bool state, int pwmValue, int dacValue) {
  if (mode == 0) return String(analogRead(pin));
  else if (mode == 1) return String(state ? 1 : 0);
  else if (mode == 2) return String(pwmValue);
  else if (mode == 3 || mode == 4) return String(digitalRead(pin) ? 1 : 0);
  else if (mode == 5) return String(dacValue);
  return "0";
}

void ClassIOWebServerGui::sendHTMLPage(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println("Connection: close");
  client.println();
  
  client.println("<!DOCTYPE html><html>");
  client.println("<meta name='viewport' content='width=device-width,initial-scale=1'>");
  client.println("<head><title>Arduino Pin Control</title>");
  client.println("<style>");
  client.println("body{font-family:'Roboto',Arial,sans-serif;margin:0;padding:20px;background-color:#f8f9fa;}");
  client.println("h1{color:#00979D;font-size:28px;margin-bottom:30px;}");
  client.println("table{border-collapse:collapse;width:100%;background-color:white;border-radius:8px;overflow:hidden;box-shadow:0 2px 10px rgba(0,0,0,0.1);}");
  client.println("th{background-color:#00979D;color:white;padding:15px;text-align:left;font-weight:500;}");
  client.println("td{border-bottom:1px solid #e9ecef;padding:12px 15px;vertical-align:middle;}");
  client.println("tr:hover{background-color:#f8f9fa;}");
  client.println("select{background-color:white;border:2px solid #00979D;border-radius:4px;padding:8px 12px;color:#333;font-size:14px;}");
  client.println("input[type='checkbox']{width:20px;height:20px;accent-color:#00979D;}");
  client.println("input[type='range']{width:150px;height:6px;background:#ddd;border-radius:3px;outline:none;appearance:none;}");
  client.println("input[type='range']::-webkit-slider-thumb{appearance:none;width:20px;height:20px;background:#00979D;border-radius:50%;cursor:pointer;}");
  client.println("input[type='range']::-moz-range-thumb{width:20px;height:20px;background:#00979D;border-radius:50%;cursor:pointer;border:none;}");
  client.println(".pin-name{font-weight:bold;color:#00979D;}");
  client.println("@media (max-width:768px){");
  client.println("body{padding:10px;font-size:14px;}");
  client.println("h1{font-size:22px;margin-bottom:20px;}");
  client.println("table{font-size:12px;}th,td{padding:8px 6px;}");
  client.println("select{padding:4px 6px;font-size:12px;}");
  client.println("input[type='range']{width:100px;}}");
  client.println("</style></head>");
  
  client.println("<body>");
  client.println("<h1>Arduino MKR WiFi 1010 Pin Control</h1>");
  client.println("<table>");
  client.println("<tr><th>Pin</th><th>Mode</th><th>Value</th><th>Control</th></tr>");
  
  generatePinRow(client, "A0", "a0", _a0Mode, _a0State, _a0PWMValue, _a0DACValue, false, true);
  generatePinRow(client, "A1", "a1", _a1Mode, _a1State, _a1PWMValue, 0, false, false);
  generatePinRow(client, "A2", "a2", _a2Mode, _a2State, _a2PWMValue, 0, false, false);
  generatePinRow(client, "A3", "a3", _a3Mode, _a3State, _a3PWMValue, 0, true, false);
  generatePinRow(client, "A4", "a4", _a4Mode, _a4State, _a4PWMValue, 0, true, false);
  generatePinRow(client, "A5", "a5", _a5Mode, _a5State, _a5PWMValue, 0, false, false);
  generatePinRow(client, "A6", "a6", _a6Mode, _a6State, _a6PWMValue, 0, false, false);
  generatePinRowDigital(client, "D0", "d0", _d0Mode, _d0State, _d0PWMValue, true);
  generatePinRowDigital(client, "D1", "d1", _d1Mode, _d1State, _d1PWMValue, true);
  generatePinRowDigital(client, "D2", "d2", _d2Mode, _d2State, _d2PWMValue, true);
  generatePinRowDigital(client, "D3", "d3", _d3Mode, _d3State, _d3PWMValue, true);
  generatePinRowDigital(client, "D4", "d4", _d4Mode, _d4State, _d4PWMValue, true);
  generatePinRowDigital(client, "D5", "d5", _d5Mode, _d5State, _d5PWMValue, true);
  generatePinRowDigital(client, "D6", "d6", _d6Mode, _d6State, _d6PWMValue, true);
  generatePinRowDigital(client, "D7", "d7", _d7Mode, _d7State, _d7PWMValue, true);
  generatePinRowDigital(client, "D8", "d8", _d8Mode, _d8State, _d8PWMValue, true);
  generatePinRowDigital(client, "D9", "d9", _d9Mode, _d9State, _d9PWMValue, false);
  generatePinRowDigital(client, "D10", "d10", _d10Mode, _d10State, _d10PWMValue, true);
  generatePinRowDigital(client, "D11", "d11", _d11Mode, _d11State, _d11PWMValue, false);
  generatePinRowDigital(client, "D12", "d12", _d12Mode, _d12State, _d12PWMValue, true);
  generatePinRowRGB(client, "LED Red", "ledRed", _ledRedMode, _ledRedValue);
  generatePinRowRGB(client, "LED Green", "ledGreen", _ledGreenMode, _ledGreenValue);
  generatePinRowRGB(client, "LED Blue", "ledBlue", _ledBlueMode, _ledBlueValue);
  
  client.println("</table>");
  client.println("<script>");
  client.println("function updateValues(){");
  client.println("fetch('/api/values').then(r=>r.json()).then(data=>{");
  client.println("Object.keys(data).forEach(pin=>{");
  client.println("const elem=document.getElementById(pin+'_value');");
  client.println("if(elem)elem.textContent=data[pin];});});};");
  client.println("setInterval(updateValues,1000);");
  
  client.println("function changeMode(pin){");
  client.println("const mode=document.getElementById(pin+'_mode').value;");
  client.println("const toggle=document.getElementById(pin+'_toggle');");
  client.println("const slider=document.getElementById(pin+'_slider');");
  client.println("const dac=document.getElementById(pin+'_dac');");
  client.println("if(toggle)toggle.style.display=mode==1?'inline':'none';");
  client.println("if(slider)slider.style.display=mode==2?'inline':'none';");
  client.println("if(dac)dac.style.display=mode==5?'inline':'none';");
  client.println("fetch('/?'+pin+'_mode='+mode).then(()=>updateValues());};");

  client.println("function setValue(pin){");
  client.println("const mode=parseInt(document.getElementById(pin+'_mode').value);");
  client.println("let value;");
  client.println("if(mode==1){");
  client.println("value=document.getElementById(pin+'_toggle').checked?1:0;");
  client.println("}else if(mode==2){");
  client.println("value=document.getElementById(pin+'_slider').value;");
  client.println("}else if(mode==5){");
  client.println("value=document.getElementById(pin+'_dac').value;");
  client.println("}");
  client.println("if(value!==undefined){");
  client.println("fetch('/?'+pin+'_value='+value).then(()=>updateValues());");
  client.println("}};");
  client.println("</script></body></html>");
}

void ClassIOWebServerGui::generatePinRow(WiFiClient &client, String pinName, String pinId, int mode, bool state, int pwmValue, int dacValue, bool hasPWM, bool hasDAC) {
  client.println("<tr><td class='pin-name'>" + pinName + "</td>");
  client.println("<td><select id='" + pinId + "_mode' onchange='changeMode(\"" + pinId + "\")'>");
  client.println("<option value='0'" + String(mode == 0 ? " selected" : "") + ">Analog Input</option>");
  client.println("<option value='1'" + String(mode == 1 ? " selected" : "") + ">Digital Output</option>");
  if (hasPWM) client.println("<option value='2'" + String(mode == 2 ? " selected" : "") + ">PWM Output</option>");
  client.println("<option value='3'" + String(mode == 3 ? " selected" : "") + ">Digital Input</option>");
  client.println("<option value='4'" + String(mode == 4 ? " selected" : "") + ">Digital Input Pullup</option>");
  if (hasDAC) client.println("<option value='5'" + String(mode == 5 ? " selected" : "") + ">DAC Output</option>");
  client.println("</select></td>");
  client.println("<td id='" + pinId + "_value'>-</td>");
  client.println("<td>");
  client.println("<input type='checkbox' id='" + pinId + "_toggle' onchange='setValue(\"" + pinId + "\")'" + String(state ? " checked" : "") + " style='display:" + String(mode == 1 ? "inline" : "none") + "'>");
  if (hasPWM) client.println("<input type='range' id='" + pinId + "_slider' min='0' max='1023' value='" + String(pwmValue) + "' onchange='setValue(\"" + pinId + "\")' style='display:" + String(mode == 2 ? "inline" : "none") + "'>");
  if (hasDAC) client.println("<input type='range' id='" + pinId + "_dac' min='0' max='1023' value='" + String(dacValue) + "' onchange='setValue(\"" + pinId + "\")' style='display:" + String(mode == 5 ? "inline" : "none") + "'>");
  client.println("</td></tr>");
}

void ClassIOWebServerGui::generatePinRowDigital(WiFiClient &client, String pinName, String pinId, int mode, bool state, int pwmValue, bool hasPWM) {
  client.println("<tr><td class='pin-name'>" + pinName + "</td>");
  client.println("<td><select id='" + pinId + "_mode' onchange='changeMode(\"" + pinId + "\")'>");
  client.println("<option value='1'" + String(mode == 1 ? " selected" : "") + ">Digital Output</option>");
  if (hasPWM) client.println("<option value='2'" + String(mode == 2 ? " selected" : "") + ">PWM Output</option>");
  client.println("<option value='3'" + String(mode == 3 ? " selected" : "") + ">Digital Input</option>");
  client.println("<option value='4'" + String(mode == 4 ? " selected" : "") + ">Digital Input Pullup</option>");
  client.println("</select></td>");
  client.println("<td id='" + pinId + "_value'>-</td>");
  client.println("<td>");
  client.println("<input type='checkbox' id='" + pinId + "_toggle' onchange='setValue(\"" + pinId + "\")'" + String(state ? " checked" : "") + " style='display:" + String(mode == 1 ? "inline" : "none") + "'>");
  if (hasPWM) client.println("<input type='range' id='" + pinId + "_slider' min='0' max='1023' value='" + String(pwmValue) + "' onchange='setValue(\"" + pinId + "\")' style='display:" + String(mode == 2 ? "inline" : "none") + "'>");
  client.println("</td></tr>");
}

void ClassIOWebServerGui::generatePinRowRGB(WiFiClient &client, String pinName, String pinId, int mode, int value) {
  client.println("<tr><td class='pin-name'>" + pinName + "</td>");
  client.println("<td><select id='" + pinId + "_mode' onchange='changeMode(\"" + pinId + "\")'>");
  client.println("<option value='1'" + String(mode == 1 ? " selected" : "") + ">Digital Output</option>");
  client.println("<option value='2'" + String(mode == 2 ? " selected" : "") + ">Analog Output</option>");
  client.println("</select></td>");
  client.println("<td id='" + pinId + "_value'>" + String(value) + "</td>");
  client.println("<td>");
  client.println("<input type='checkbox' id='" + pinId + "_toggle' onchange='setValue(\"" + pinId + "\")' style='display:" + String(mode == 1 ? "inline" : "none") + "'>");
  client.println("<input type='range' id='" + pinId + "_slider' min='0' max='255' value='" + String(value) + "' onchange='setValue(\"" + pinId + "\")' style='display:" + String(mode == 2 ? "inline" : "none") + "'>");
  client.println("</td></tr>");
}

void ClassIOWebServerGui::handleRequests(String request) {
  // A0 requests
  if (request.indexOf("a0_mode=") >= 0) {
    _a0Mode = request.substring(request.indexOf("a0_mode=") + 8, request.indexOf("a0_mode=") + 9).toInt();
    setPinMode(A0, _a0Mode);
  }
  if (request.indexOf("a0_value=") >= 0) {
    int value = request.substring(request.indexOf("a0_value=") + 9).toInt();
    if (_a0Mode == 1) { _a0State = (value == 1); digitalWrite(A0, _a0State); }
    else if (_a0Mode == 2) { _a0PWMValue = value; analogWrite(A0, _a0PWMValue); }
    else if (_a0Mode == 5) { _a0DACValue = value; analogWrite(A0, _a0DACValue); }
  }

  // A1 requests
  if (request.indexOf("a1_mode=") >= 0) {
    _a1Mode = request.substring(request.indexOf("a1_mode=") + 8, request.indexOf("a1_mode=") + 9).toInt();
    setPinMode(A1, _a1Mode);
  }
  if (request.indexOf("a1_value=") >= 0) {
    int value = request.substring(request.indexOf("a1_value=") + 9).toInt();
    if (_a1Mode == 1) { _a1State = (value == 1); digitalWrite(A1, _a1State); }
    else if (_a1Mode == 2) { _a1PWMValue = value; analogWrite(A1, _a1PWMValue); }
  }

  // A2 requests
  if (request.indexOf("a2_mode=") >= 0) {
    _a2Mode = request.substring(request.indexOf("a2_mode=") + 8, request.indexOf("a2_mode=") + 9).toInt();
    setPinMode(A2, _a2Mode);
  }
  if (request.indexOf("a2_value=") >= 0) {
    int value = request.substring(request.indexOf("a2_value=") + 9).toInt();
    if (_a2Mode == 1) { _a2State = (value == 1); digitalWrite(A2, _a2State); }
    else if (_a2Mode == 2) { _a2PWMValue = value; analogWrite(A2, _a2PWMValue); }
  }

  // A3 requests
  if (request.indexOf("a3_mode=") >= 0) {
    _a3Mode = request.substring(request.indexOf("a3_mode=") + 8, request.indexOf("a3_mode=") + 9).toInt();
    setPinMode(A3, _a3Mode);
  }
  if (request.indexOf("a3_value=") >= 0) {
    int value = request.substring(request.indexOf("a3_value=") + 9).toInt();
    if (_a3Mode == 1) { _a3State = (value == 1); digitalWrite(A3, _a3State); }
    else if (_a3Mode == 2) { _a3PWMValue = value; analogWrite(A3, _a3PWMValue); }
  }

  // A4 requests
  if (request.indexOf("a4_mode=") >= 0) {
    _a4Mode = request.substring(request.indexOf("a4_mode=") + 8, request.indexOf("a4_mode=") + 9).toInt();
    setPinMode(A4, _a4Mode);
  }
  if (request.indexOf("a4_value=") >= 0) {
    int value = request.substring(request.indexOf("a4_value=") + 9).toInt();
    if (_a4Mode == 1) { _a4State = (value == 1); digitalWrite(A4, _a4State); }
    else if (_a4Mode == 2) { _a4PWMValue = value; analogWrite(A4, _a4PWMValue); }
  }

  // A5 requests
  if (request.indexOf("a5_mode=") >= 0) {
    _a5Mode = request.substring(request.indexOf("a5_mode=") + 8, request.indexOf("a5_mode=") + 9).toInt();
    setPinMode(A5, _a5Mode);
  }
  if (request.indexOf("a5_value=") >= 0) {
    int value = request.substring(request.indexOf("a5_value=") + 9).toInt();
    if (_a5Mode == 1) { _a5State = (value == 1); digitalWrite(A5, _a5State); }
    else if (_a5Mode == 2) { _a5PWMValue = value; analogWrite(A5, _a5PWMValue); }
  }

  // A6 requests
  if (request.indexOf("a6_mode=") >= 0) {
    _a6Mode = request.substring(request.indexOf("a6_mode=") + 8, request.indexOf("a6_mode=") + 9).toInt();
    setPinMode(A6, _a6Mode);
  }
  if (request.indexOf("a6_value=") >= 0) {
    int value = request.substring(request.indexOf("a6_value=") + 9).toInt();
    if (_a6Mode == 1) { _a6State = (value == 1); digitalWrite(A6, _a6State); }
    else if (_a6Mode == 2) { _a6PWMValue = value; analogWrite(A6, _a6PWMValue); }
  }

  // D0 requests
  if (request.indexOf("d0_mode=") >= 0) {
    _d0Mode = request.substring(request.indexOf("d0_mode=") + 8, request.indexOf("d0_mode=") + 9).toInt();
    setPinMode(0, _d0Mode);
  }
  if (request.indexOf("d0_value=") >= 0) {
    int value = request.substring(request.indexOf("d0_value=") + 9).toInt();
    if (_d0Mode == 1) { _d0State = (value == 1); digitalWrite(0, _d0State); }
    else if (_d0Mode == 2) { _d0PWMValue = value; analogWrite(0, _d0PWMValue); }
  }

  // D1 requests
  if (request.indexOf("d1_mode=") >= 0) {
    _d1Mode = request.substring(request.indexOf("d1_mode=") + 8, request.indexOf("d1_mode=") + 9).toInt();
    setPinMode(1, _d1Mode);
  }
  if (request.indexOf("d1_value=") >= 0) {
    int value = request.substring(request.indexOf("d1_value=") + 9).toInt();
    if (_d1Mode == 1) { _d1State = (value == 1); digitalWrite(1, _d1State); }
    else if (_d1Mode == 2) { _d1PWMValue = value; analogWrite(1, _d1PWMValue); }
  }

  // D2 requests
  if (request.indexOf("d2_mode=") >= 0) {
    _d2Mode = request.substring(request.indexOf("d2_mode=") + 8, request.indexOf("d2_mode=") + 9).toInt();
    setPinMode(2, _d2Mode);
  }
  if (request.indexOf("d2_value=") >= 0) {
    int value = request.substring(request.indexOf("d2_value=") + 9).toInt();
    if (_d2Mode == 1) { _d2State = (value == 1); digitalWrite(2, _d2State); }
    else if (_d2Mode == 2) { _d2PWMValue = value; analogWrite(2, _d2PWMValue); }
  }

  // D3 requests
  if (request.indexOf("d3_mode=") >= 0) {
    _d3Mode = request.substring(request.indexOf("d3_mode=") + 8, request.indexOf("d3_mode=") + 9).toInt();
    setPinMode(3, _d3Mode);
  }
  if (request.indexOf("d3_value=") >= 0) {
    int value = request.substring(request.indexOf("d3_value=") + 9).toInt();
    if (_d3Mode == 1) { _d3State = (value == 1); digitalWrite(3, _d3State); }
    else if (_d3Mode == 2) { _d3PWMValue = value; analogWrite(3, _d3PWMValue); }
  }

  // D4 requests
  if (request.indexOf("d4_mode=") >= 0) {
    _d4Mode = request.substring(request.indexOf("d4_mode=") + 8, request.indexOf("d4_mode=") + 9).toInt();
    setPinMode(4, _d4Mode);
  }
  if (request.indexOf("d4_value=") >= 0) {
    int value = request.substring(request.indexOf("d4_value=") + 9).toInt();
    if (_d4Mode == 1) { _d4State = (value == 1); digitalWrite(4, _d4State); }
    else if (_d4Mode == 2) { _d4PWMValue = value; analogWrite(4, _d4PWMValue); }
  }

  // D5 requests
  if (request.indexOf("d5_mode=") >= 0) {
    _d5Mode = request.substring(request.indexOf("d5_mode=") + 8, request.indexOf("d5_mode=") + 9).toInt();
    setPinMode(5, _d5Mode);
  }
  if (request.indexOf("d5_value=") >= 0) {
    int value = request.substring(request.indexOf("d5_value=") + 9).toInt();
    if (_d5Mode == 1) { _d5State = (value == 1); digitalWrite(5, _d5State); }
    else if (_d5Mode == 2) { _d5PWMValue = value; analogWrite(5, _d5PWMValue); }
  }

  // D6 requests
  if (request.indexOf("d6_mode=") >= 0) {
    _d6Mode = request.substring(request.indexOf("d6_mode=") + 8, request.indexOf("d6_mode=") + 9).toInt();
    setPinMode(6, _d6Mode);
  }
  if (request.indexOf("d6_value=") >= 0) {
    int value = request.substring(request.indexOf("d6_value=") + 9).toInt();
    if (_d6Mode == 1) { _d6State = (value == 1); digitalWrite(6, _d6State); }
    else if (_d6Mode == 2) { _d6PWMValue = value; analogWrite(6, _d6PWMValue); }
  }

  // D7 requests
  if (request.indexOf("d7_mode=") >= 0) {
    _d7Mode = request.substring(request.indexOf("d7_mode=") + 8, request.indexOf("d7_mode=") + 9).toInt();
    setPinMode(7, _d7Mode);
  }
  if (request.indexOf("d7_value=") >= 0) {
    int value = request.substring(request.indexOf("d7_value=") + 9).toInt();
    if (_d7Mode == 1) { _d7State = (value == 1); digitalWrite(7, _d7State); }
    else if (_d7Mode == 2) { _d7PWMValue = value; analogWrite(7, _d7PWMValue); }
  }

  // D8 requests
  if (request.indexOf("d8_mode=") >= 0) {
    _d8Mode = request.substring(request.indexOf("d8_mode=") + 8, request.indexOf("d8_mode=") + 9).toInt();
    setPinMode(8, _d8Mode);
  }
  if (request.indexOf("d8_value=") >= 0) {
    int value = request.substring(request.indexOf("d8_value=") + 9).toInt();
    if (_d8Mode == 1) { _d8State = (value == 1); digitalWrite(8, _d8State); }
    else if (_d8Mode == 2) { _d8PWMValue = value; analogWrite(8, _d8PWMValue); }
  }

  // D9 requests
  if (request.indexOf("d9_mode=") >= 0) {
    _d9Mode = request.substring(request.indexOf("d9_mode=") + 8, request.indexOf("d9_mode=") + 9).toInt();
    setPinMode(9, _d9Mode);
  }
  if (request.indexOf("d9_value=") >= 0) {
    int value = request.substring(request.indexOf("d9_value=") + 9).toInt();
    if (_d9Mode == 1) { _d9State = (value == 1); digitalWrite(9, _d9State); }
    else if (_d9Mode == 2) { _d9PWMValue = value; analogWrite(9, _d9PWMValue); }
  }

  // D10 requests
  if (request.indexOf("d10_mode=") >= 0) {
    _d10Mode = request.substring(request.indexOf("d10_mode=") + 9, request.indexOf("d10_mode=") + 10).toInt();
    setPinMode(10, _d10Mode);
  }
  if (request.indexOf("d10_value=") >= 0) {
    int value = request.substring(request.indexOf("d10_value=") + 10).toInt();
    if (_d10Mode == 1) { _d10State = (value == 1); digitalWrite(10, _d10State); }
    else if (_d10Mode == 2) { _d10PWMValue = value; analogWrite(10, _d10PWMValue); }
  }

  // D11 requests
  if (request.indexOf("d11_mode=") >= 0) {
    _d11Mode = request.substring(request.indexOf("d11_mode=") + 9, request.indexOf("d11_mode=") + 10).toInt();
    setPinMode(11, _d11Mode);
  }
  if (request.indexOf("d11_value=") >= 0) {
    int value = request.substring(request.indexOf("d11_value=") + 10).toInt();
    if (_d11Mode == 1) { _d11State = (value == 1); digitalWrite(11, _d11State); }
    else if (_d11Mode == 2) { _d11PWMValue = value; analogWrite(11, _d11PWMValue); }
  }

  // D12 requests
  if (request.indexOf("d12_mode=") >= 0) {
    _d12Mode = request.substring(request.indexOf("d12_mode=") + 9, request.indexOf("d12_mode=") + 10).toInt();
    setPinMode(12, _d12Mode);
  }
  if (request.indexOf("d12_value=") >= 0) {
    int value = request.substring(request.indexOf("d12_value=") + 10).toInt();
    if (_d12Mode == 1) { _d12State = (value == 1); digitalWrite(12, _d12State); }
    else if (_d12Mode == 2) { _d12PWMValue = value; analogWrite(12, _d12PWMValue); }
  }

  // RGB LED requests
  if (request.indexOf("ledRed_mode=") >= 0) {
    _ledRedMode = request.substring(request.indexOf("ledRed_mode=") + 12, request.indexOf("ledRed_mode=") + 13).toInt();
  }
  if (request.indexOf("ledRed_value=") >= 0) {
    _ledRedValue = request.substring(request.indexOf("ledRed_value=") + 13).toInt();
    WiFiDrv::analogWrite(25, _ledRedValue);
  }
  if (request.indexOf("ledGreen_mode=") >= 0) {
    _ledGreenMode = request.substring(request.indexOf("ledGreen_mode=") + 14, request.indexOf("ledGreen_mode=") + 15).toInt();
  }
  if (request.indexOf("ledGreen_value=") >= 0) {
    _ledGreenValue = request.substring(request.indexOf("ledGreen_value=") + 15).toInt();
    WiFiDrv::analogWrite(26, _ledGreenValue);
  }
  if (request.indexOf("ledBlue_mode=") >= 0) {
    _ledBlueMode = request.substring(request.indexOf("ledBlue_mode=") + 13, request.indexOf("ledBlue_mode=") + 14).toInt();
  }
  if (request.indexOf("ledBlue_value=") >= 0) {
    _ledBlueValue = request.substring(request.indexOf("ledBlue_value=") + 14).toInt();
    WiFiDrv::analogWrite(27, _ledBlueValue);
  }
}

void ClassIOWebServerGui::setPinMode(int pin, int mode) {
  if (mode == 0) {
    // Analog input - no pinMode needed
  } else if (mode == 1) {
    pinMode(pin, OUTPUT);
  } else if (mode == 2) {
    pinMode(pin, OUTPUT);
  } else if (mode == 3) {
    pinMode(pin, INPUT);
  } else if (mode == 4) {
    pinMode(pin, INPUT_PULLUP);
  } else if (mode == 5) {
    pinMode(pin, INPUT); //Also when it is Ouput (DAC), INPUT is correct.
  }
  if (pin == A0){
    DAC->CTRLA.bit.ENABLE = 0; //Disable DAC to make it possible to change DAC registers
    while (DAC->STATUS.bit.SYNCBUSY); 
  }
}

void ClassIOWebServerGui::printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//public:
ClassIOWebServerGui::ClassIOWebServerGui(){
}

void ClassIOWebServerGui::setupIOWebServerGui() {
  Serial.begin(1200);
  //while ( ! Serial){}
  delay(1);

  analogWriteResolution(10); //DAC A0

  WiFiDrv::pinMode(25, OUTPUT); // Red
  WiFiDrv::pinMode(26, OUTPUT); // Green  
  WiFiDrv::pinMode(27, OUTPUT); // Blue

  // Apply initial values
  // Analog pins
  setPinMode(A0, _a0Mode);
  if (_a0Mode == 1) digitalWrite(A0, _a0State);
  else if (_a0Mode == 2) analogWrite(A0, _a0PWMValue);
  else if (_a0Mode == 5) analogWrite(A0, _a0DACValue);
  
  setPinMode(A1, _a1Mode);
  if (_a1Mode == 1) digitalWrite(A1, _a1State);
  else if (_a1Mode == 2) analogWrite(A1, _a1PWMValue);
  
  setPinMode(A2, _a2Mode);
  if (_a2Mode == 1) digitalWrite(A2, _a2State);
  else if (_a2Mode == 2) analogWrite(A2, _a2PWMValue);
  
  setPinMode(A3, _a3Mode);
  if (_a3Mode == 1) digitalWrite(A3, _a3State);
  else if (_a3Mode == 2) analogWrite(A3, _a3PWMValue);
  
  setPinMode(A4, _a4Mode);
  if (_a4Mode == 1) digitalWrite(A4, _a4State);
  else if (_a4Mode == 2) analogWrite(A4, _a4PWMValue);
  
  setPinMode(A5, _a5Mode);
  if (_a5Mode == 1) digitalWrite(A5, _a5State);
  else if (_a5Mode == 2) analogWrite(A5, _a5PWMValue);
  
  setPinMode(A6, _a6Mode);
  if (_a6Mode == 1) digitalWrite(A6, _a6State);
  else if (_a6Mode == 2) analogWrite(A6, _a6PWMValue);
  
  // Digital pins
  for (int i = 0; i <= 12; i++) {
    int mode = (i == 0) ? _d0Mode : (i == 1) ? _d1Mode : (i == 2) ? _d2Mode : 
               (i == 3) ? _d3Mode : (i == 4) ? _d4Mode : (i == 5) ? _d5Mode :
               (i == 6) ? _d6Mode : (i == 7) ? _d7Mode : (i == 8) ? _d8Mode :
               (i == 9) ? _d9Mode : (i == 10) ? _d10Mode : (i == 11) ? _d11Mode : _d12Mode;
    bool state = (i == 0) ? _d0State : (i == 1) ? _d1State : (i == 2) ? _d2State :
                 (i == 3) ? _d3State : (i == 4) ? _d4State : (i == 5) ? _d5State :
                 (i == 6) ? _d6State : (i == 7) ? _d7State : (i == 8) ? _d8State :
                 (i == 9) ? _d9State : (i == 10) ? _d10State : (i == 11) ? _d11State : _d12State;
    int pwm = (i == 0) ? _d0PWMValue : (i == 1) ? _d1PWMValue : (i == 2) ? _d2PWMValue :
              (i == 3) ? _d3PWMValue : (i == 4) ? _d4PWMValue : (i == 5) ? _d5PWMValue :
              (i == 6) ? _d6PWMValue : (i == 7) ? _d7PWMValue : (i == 8) ? _d8PWMValue :
              (i == 9) ? _d9PWMValue : (i == 10) ? _d10PWMValue : (i == 11) ? _d11PWMValue : _d12PWMValue;
    
    setPinMode(i, mode);
    if (mode == 1) digitalWrite(i, state);
    else if (mode == 2) analogWrite(i, pwm);
  }
  
  // RGB LEDs
  WiFiDrv::analogWrite(25, _ledRedValue);
  WiFiDrv::analogWrite(26, _ledGreenValue);
  WiFiDrv::analogWrite(27, _ledBlueValue);
  
  while (_status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(_ssid);
    _status = WiFi.begin(_ssid, _pass);
    delay(10000);
  }
  
  server.begin();
  printWiFiStatus();
}

void ClassIOWebServerGui::loopIOWebServerGui() {
  WiFiClient client = server.available();

  String request = "";
  if (client) {
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (request == "" && currentLine.length() > 0) {
            request = currentLine;
          }
          if (currentLine.length() == 0) {
            if (request.indexOf("GET /api/values") >= 0) {
              sendValuesJSON(client);
            } else {
              sendHTMLPage(client);
            }
            break;
          } else {
            handleRequests(request.length() > 0 ? request : currentLine);
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    
    client.stop();
  }
}

void ClassIOWebServerGui::setMode(int a0Mode, int a1Mode, int a2Mode, int a3Mode, int a4Mode, int a5Mode, int a6Mode,
              int d0Mode, int d1Mode, int d2Mode, int d3Mode, int d4Mode, int d5Mode, int d6Mode, int d7Mode, int d8Mode, int d9Mode, int d10Mode, int d11Mode, int d12Mode,
              int ledRedMode, int ledGreenMode, int ledBlueMode){
  _a0Mode = a0Mode; _a1Mode = a1Mode; _a2Mode = a2Mode; _a3Mode = a3Mode; _a4Mode = a4Mode; _a5Mode = a5Mode; _a6Mode = a6Mode;
    _d0Mode = d0Mode; _d1Mode = d1Mode; _d2Mode = d2Mode; _d3Mode = d3Mode; _d4Mode = d4Mode; _d5Mode = d5Mode; _d6Mode = d6Mode; _d7Mode = d7Mode; _d8Mode = d8Mode; _d9Mode = d9Mode; _d10Mode = d10Mode; _d11Mode = d11Mode, _d12Mode = d12Mode,
    _ledRedMode = ledRedMode, _ledGreenMode = ledGreenMode, _ledBlueMode = ledBlueMode;
}
void ClassIOWebServerGui::setState(bool a0State, bool a1State, bool a2State, bool a3State, bool a4State, bool a5State, bool a6State,
              bool d0State, bool d1State, bool d2State, bool d3State, bool d4State, bool d5State, bool d6State, bool d7State, bool d8State, bool d9State, bool d10State, bool d11State, bool d12State){
  _a0State = a0State, _a1State = a1State, _a2State = a2State, _a3State = a3State, _a4State = a4State, _a5State = a5State, _a6State = a6State,
    _d0State = d0State, _d1State = d1State, _d2State = d2State, _d3State = d3State, _d4State = d4State, _d5State = d5State, _d6State = d6State, _d7State = d7State, _d8State = d8State, _d9State = d9State, _d10State = d10State, _d11State = d11State, _d12State = d12State;
}
void ClassIOWebServerGui::setValue(int a0PWMValue, int a1PWMValue, int a2PWMValue, int a3PWMValue, int a4PWMValue, int a5PWMValue, int a6PWMValue,
              int d0PWMValue, int d1PWMValue, int d2PWMValue, int d3PWMValue, int d4PWMValue, int d5PWMValue, int d6PWMValue, int d7PWMValue, int d8PWMValue, int d9PWMValue, int d10PWMValue, int d11PWMValue, int d12PWMValue,
              int a0DACValue,
              int ledRedValue, int ledGreenValue, int ledBlueValue){
  _a0PWMValue = a0PWMValue, _a1PWMValue = a1PWMValue, _a2PWMValue = a2PWMValue, _a3PWMValue = a3PWMValue, _a4PWMValue = a4PWMValue, _a5PWMValue = a5PWMValue, _a6PWMValue = a6PWMValue,
    _d0PWMValue = d0PWMValue, _d1PWMValue = d1PWMValue, _d2PWMValue = d2PWMValue, _d3PWMValue = d3PWMValue, _d4PWMValue = d4PWMValue, _d5PWMValue = d5PWMValue, _d6PWMValue = d6PWMValue, _d7PWMValue = d7PWMValue, _d8PWMValue = d8PWMValue, _d9PWMValue = d9PWMValue, _d10PWMValue = d10PWMValue, _d11PWMValue = d11PWMValue, _d12PWMValue = d12PWMValue,
    _a0DACValue = a0DACValue,
    _ledRedValue = ledRedValue, _ledGreenValue = ledGreenValue, _ledBlueValue = ledBlueValue;
}
                MKR1010 IO Web Server Gui Control               28 December 2025 Andreas1313

This code was generated with the help of the AI Assistant (Experimental) from Arduino online IDE Version 1.4.1. So I will not be able to help you a lot. We (me and the AI) need a lot of try and errors until it works now as it is.

What it does:
It show each Pin A0 - A6, D0 - D12 and RGB LED from MKR1010 at a Webserver- Browser page. (D13 and D14 not, because of Serial Monitor). It is optimized for mobile phone (hotspot or local network).

Use/Function:
- Make a file arduino_secrets.h with SECRET_SSID and SECRET_PASS
- See at serial monitor which IP address you get from DHCP
- Open a Web Browser and type in the IP
- You will see a internet page with a table:
| Pin | Mode       | Value | Control              |
| A0  | DAC Output | 0     | (You will see a bar) |
| A1  | Analog Inp.| 224   |                      |
| A2  | Digital Ou.| 0     | (Tickbox)            |
| A3...


Hints:
- You can change the name of A0, A1... according to your needs. generatePinRow(client, "A0"...
- You can change the start mode and the start state (value) of each pin
- "Digital Output Pullup" and "Digital Output Pullup Negated" should only be used if you know what you are doing.(Open Collector with an internal 20kΩ to 50kΩ pullup resistor). Because of the "floating" pin, it is possible that the Control is different from the Valus. The reason is, that it really reads back the status of the pin.
- This needs only 15% of program storage and 12% of dynamic memory. This is because the Webpage is saved in the W-Lan u-blox NINA-W102.

Not fixed:
- A0 only switch between DAC and Analog Input. If you want to use other, set it at beginning (Example: int a0Mode = 1, a...)

START
  ↓
SETUP()
  ├── Initialize Serial (1200 baud)
  ├── Set analogWriteResolution(10) for DAC
  ├── Configure RGB LED pins (25, 26, 27)
  ├── Apply initial pin modes & values:
  │   ├── Analog pins A0-A6 (modes, states, PWM, DAC)
  │   └── Digital pins D0-D12 (modes, states, PWM)
  ├── Set RGB LED initial values
  ├── Connect to WiFi (retry every 10s until connected)
  ├── Start web server on port 80
  └── Print WiFi status
  ↓
LOOP()
  ├── Check for WiFi client connection
  │   ↓ (if client available)
  ├── Read HTTP request line by line
  ├── Parse GET request string
  │   ↓
  ├── Route request:
  │   ├── "/api/values" → sendValuesJSON()
  │   └── Other → handleRequests() → sendHTMLPage()
  └── Close client connection
  ↓ (repeat)

SENDVALUESJSON()
  ├── Send JSON HTTP headers
  ├── Build JSON response with:
  │   ├── All pin values (a0-a6, d0-d12)
  │   └── RGB LED values
  └── Send to client

SENDHTTMLPAGE()
  ├── Send HTML HTTP headers
  ├── Generate HTML structure:
  │   ├── CSS styling (responsive design)
  │   ├── Pin control table with rows for:
  │   │   ├── A0-A6 (with mode dropdowns, controls)
  │   │   ├── D0-D12 (with mode dropdowns, controls)
  │   │   └── RGB LEDs (Red, Green, Blue)
  │   └── JavaScript for:
  │       ├── Real-time value updates (1s interval)
  │       ├── Mode change handlers
  │       └── Value change handlers
  └── Send to client

HANDLEREQUESTS()
  ├── Parse URL parameters for each pin:
  │   ├── Mode changes (a0_mode=, d0_mode=, etc.)
  │   └── Value changes (a0_value=, d0_value=, etc.)
  ├── Update global variables
  ├── Apply changes to physical pins:
  │   ├── setPinMode() for mode changes
  │   ├── digitalWrite() for digital outputs
  │   ├── analogWrite() for PWM/DAC outputs
  │   └── WiFiDrv::analogWrite() for RGB LEDs
  └── Return

HELPER FUNCTIONS:
├── getPinValue() - Returns current pin value based on mode
├── generatePinRow() - Creates HTML table row for analog pins
├── generatePinRowDigital() - Creates HTML table row for digital pins
├── generatePinRowRGB() - Creates HTML table row for RGB LEDs
├── setPinMode() - Sets Arduino pin mode (INPUT/OUTPUT/INPUT_PULLUP)
└── printWiFiStatus() - Prints connection info to Serial

PIN MODES SUPPORTED:
├── 0: Analog Input
├── 1: Digital Output  
├── 2: PWM Output
├── 3: Digital Input
├── 4: Digital Input Pullup
└── 5: DAC Output (A0 only)

Key Features:
Real-time web interface with responsive design
Multi-mode pin control (analog/digital/PWM/DAC)
Live value updates via JSON API
RGB LED control using WiFiDrv library
Mobile-friendly responsive layout

Only as a hint: I have asked the AI after most of this was working: What would be a good prompt to generate this code?
***Answere from AI***
Here's a good prompt to generate this Arduino MKR WiFi 1010 pin control code:

"Create a comprehensive web-based pin control system for Arduino MKR WiFi 1010 with the following features:
• Web server that serves an HTML control panel and JSON API
• All pins controllable: A0-A6 (analog) and D0-D12 (digital) with multiple modes:
Analog input (0-1023 readings)
Digital output (HIGH/LOW toggle)
PWM output (0-1023 slider control)
Digital input / input pullup (live readings)
DAC output for A0 only (0-1023 slider) • Built-in RGB LED control (pins 25=Red, 26=Green, 27=Blue via WiFiDrv) • Responsive HTML interface with:
Pin mode dropdown selectors
Live value display (auto-refresh every second)
Checkboxes for digital outputs
Sliders for PWM/DAC control
Mobile-friendly design • State persistence: All pin configurations maintained between web requests • Pin initialization: Apply all default states/values at startup • URL parameter handling for changing modes and values • JSON API endpoint (/api/values) for real-time data fetching

Include proper pin mode validation (e.g., PWM only on capable pins), Arduino secrets for WiFi credentials, and handle both GET requests and live updates efficiently."

This prompt captures the key architecture, features, and technical requirements needed to generate similar comprehensive pin control code.
**********************
***
***License***

Copyright (c) 2025. Andreas1313. 83022 Rosenheim. Germany. No:250803_sT_C_0_132\
Licensed under CC BY-NC-SA 4.0: https://creativecommons.org/licenses/by-nc-sa/4.0/.\
-Credit required  -Share alike  -No warranty provided\
-Free for private use.\
-Free for prototype use, but send an e-mail that you want to use it for prototype to andreas.rosenheim@gmail.com. You can directly start. You do not have to wait for an answer.\
-Contact for commercial use: andreas.rosenheim@gmail.com.(You only have to donate to "Doctors Without Borders", or similar institution. Which should be tax-deductible)
 

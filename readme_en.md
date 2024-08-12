# Welcome to the NMEA 0183 display project.
## *We've had enough of Raymargarine!*
[![Build Status](https://github.com/guybel/afficheur?branch=main)](https://github.com/guybel/afficheur)
Frustrated by the prices of Rayma... products, you're thinking of undertaking to build your own boat speed display. This ingenious DIY project costs you only $50, which is ten times cheaper than commercial options. Using inexpensive electronic components and your technical skills, you've created an economical and customized alternative that perfectly meets your nautical needs.

## Software:
This project is made on VS Code and PlatformIO. You'll find the settings in the .ini file of the project.

## Hardware:
    an M5Stack Core2 => $50

## Library:
    https://github.com/Glinnes/NMEAParser 

### Library summary:
We declare a parser with a certain number of NMEA 0183 codes to parse.
We redirect the serial streams into the parser as follows:
```sh
            singlechar = client.read();        
            parser << singlechar;
```

## Features:
- Directly read NMEA 0183 codes on the WiFi serial link.
- Read and display depth on an M5Core2.
- Read and display speed on an M5Core2.

## Code:
The first part is for WiFi connection.
```sh
    const char* ssid = "NMEA2000-Gateway";
    const char* password = "password";
    const char * serverAddress = "192.168.4.1";
    const int serverPort = 2222; // Serial port 2222
```

Declaration of handlers that capture
```sh
NMEAParser<2> parser;
void handleDepthSounder(){
  float depth;
  if (parser.getArg(0, depth)){
    depthBelowKeel = depth;
  }
}
```
```sh
void handleSpeed()
{
  float speed;
  if (parser.getArg(4, speed)){
    speedOverWater = speed * 1.1 ;
  }
}
```

Somewhere in setup()
```sh
 parser.addHandler("IIDBK", handleDepthSounder);
  parser.addHandler("VWVHW", handleSpeed);
```

## In loop():
Connect the WiFi client and collect the stream (character by character)
```sh
 if (client.connect(serverAddress, serverPort)) {
 ...
  while (client.connected()) {
        
        if (client.available()) {
            singlechar = client.read();        
            parser << singlechar;
            }
      // a sentence is finished
      ... do something
  }
..
```

For more information, you can contact me at belleygu@hotmail.com

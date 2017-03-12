# IoT intro

In this project we control LEDs and display analog voltages using a web interface and an ESP8266.

This wiki gives a few steps to approach this introduction:

https://github.com/honnet/iot_intro/wiki/IOT-Intro


## Dependencies

ESP8266 Arduino:

https://github.com/esp8266/Arduino#installing-with-boards-manager

WiFiManager - WiFi Configuration Magic:

https://github.com/tzapu/WiFiManager#installing


## Usage

### 1st time
  * program the ESP with the arduino IDE using "Wemos D1" as board (more
explanations available [here](https://github.com/esp8266/Arduino)
  * connect your phone/computer to your the wifi network called 'iot_intro'
  * go to the following URL with your browser: http://192.168.4.1/
  * set the ESP to connect to your favorite network (set the SSID and password)

### ...then
  * your phone/computer should connect back to your favorite network
  * put the following URL in your browser, the rest should be intuitive:

[http://iot_intro.local](http://iot_intro.local)

Note: If you need to change the password, uncomment the follwing line in the .ino file:

    wifiManager.resetSettings();

### Documentation
https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi#table-of-contents


## Potential problems

### error: cannot access [serial port]

This might help:

    sudo usermod -a -G dialout $USER  # needs logout  (it might be plugdev too)

Or make a udev file:

    RULES='SUBSYSTEMS=="usb", ATTRS{idProduct}=="7523", ATTRS{idVendor}=="1a86", MODE:="0666", GROUP="plugdev"'
    echo $RULES | sudo tee /etc/udev/rules.d/30-HL-340.rules
    sudo restart udev

### .local address doesn't work

If you are using a smartphone, the .local URL might not work.
Use the serial port display to get the IP address.

If you are using linux or windows, you might need to install these requirements:

https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS#requirements


## TODO

### .local experimentations:

After a successful connection to the AP, we don't know the IP address of the ESP module.
The MDNS solution doesn't work on every system but different alternatives are possible.

The ESP module could broadcast its IP or send it to the MAC address of the phone that just parametered it.

It could also publish it on a server with its MAC address (see cloud solutions such as mydevices.com).


# IoT intro

In this project we control LEDs from a web interface using an ESP8266.

## Dependencies

ESP8266 Arduino:

https://github.com/esp8266/Arduino

WiFiManager - WiFi Configuration Magic:

https://github.com/tzapu/WiFiManager


## Usage

1st time:
  * program the ESP with the arduino IDE (the 1st link should have every details needed)
  * connect your phone/computer to your the wifi network called 'iot_intro'
  * go to the following URL with your browser: http://192.168.4.1/
  * set the ESP to connect to your favorite network (set the SSID and password)

Then:
  * your phone/computer should connect back to your favorite network
  * put the following URL in your browser, the rest should be intuitive:

[http://iot_intro.local](http://iot_intro.local)

Note: If you need to change the password, uncomment the follwing line in the .ino file:

    wifiManager.resetSettings();


## Potential problems

### error: cannot access [serial port]

This might help:

    sudo usermod -a -G dialout $USER  # needs logout  (it might be plugdev too)

Or make a udev file:

    RULES='SUBSYSTEMS=="usb", ATTRS{idProduct}=="7523", ATTRS{idVendor}=="1a86", MODE:="0666", GROUP="plugdev"'
    echo $RULES | sudo tee /etc/udev/rules.d/30-HL-340.rules
    sudo restart udev


### TODO...


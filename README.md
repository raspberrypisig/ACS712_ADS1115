ACS712 [![Build Status](https://travis-ci.org/rkoptev/ACS712-arduino.svg?branch=master)](https://travis-ci.org/rkoptev/ACS712-arduino)
======
An Arduino library to interact with the ACS712 Hall effect-based linear analog current sensor. Includes DC and RMS AC current measuring. Supports ACS712-05B, ACS712-20A, ACS712-30A sensors. Typical applications include motor control, load detection and management, switch mode power supplies, and overcurrent fault protection.

For more information see the datasheet: http://www.allegromicro.com/~/media/files/datasheets/acs712-datasheet.ashx

The accuracy of the analog sensors in conjunction with the low resolution of built-in Arduino ADC hardly allows you to accurately measure the current. So, this sensor is not suitable for precise measurements, but it will be useful in cases where you need to detect the presence of current and approximately estimate its amount. For more accurate measurements, I recommend using digital sensors such as Adafruit INA219.

Wiring
======
### Arduino
![alt arduino](https://raw.githubusercontent.com/rkoptev/ACS712-arduino/master/img/ACS712_arduino_wiring.jpg)
### ESP8266
In order to use the sensor with the ESP8266, you definitely need to take care of two things:
1. You need a 5V power for the sensor (the ESP works on 3.3V), or you can use Vin pin if you powering board with USB.
2. ESP8266's ADC input works in range 0-1 Volts, it means you need to use voltage divider to convert 0-5V range from sensor to 0-1V (Note that NodeMCU already has built-in voltage divider for 3.3V input, you need to take care about that and add additional resistors or solder wire directly to ESP analog input pin).
![alt esp8266](https://raw.githubusercontent.com/rkoptev/ACS712-arduino/master/img/ACS712_esp8266_wiring.jpg)



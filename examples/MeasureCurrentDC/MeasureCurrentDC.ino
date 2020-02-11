#include "ACS712_ADS1115.h"

#define AINX 0 // channel 0 on ADS1115
#define ZEROPOINTVOLTAGE 2500 // 2.5V (VCC/2) quiescent voltage 
#define ACS712_SENSITIVITY 66.0   // ACS712_30A

/*
  This example shows how to measure DC current using ACS712 in combination with ADS1115
*/

Adafruit_ADS1115 ads;

// We have 30 amps version sensor connected to A0 pin of arduino
// Replace with your version if necessary
// {ACS712_05B, ACS712_20A, ACS712_30A}
ACS712_ADS1115 sensor(AINX);

void setup() {
  Serial.begin(9600);
  ads.setGain(GAIN_ONE);  // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.begin();
  sensor.setADS1115(&ads);
  sensor.setZeroPointVoltage(ZEROPOINTVOLTAGE);
  sensor.setSensitivity(ACS712_SENSITIVITY);
}

void loop() {
  int16_t current = sensor.getCurrentDCMilliamps();
  Serial.print("Current:");
  Serial.print(current);
  Serial.println("mA");
  delay(1000);
}
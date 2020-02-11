#include "ACS712_ADS1115.h"

#define AINX 0

Adafruit_ADS1115 ads;
ACS712_ADS1115 sensor(AINX);

void zeroPointVoltage() {
  Serial.println("Starting measuring zero point voltage....");
  int16_t zeroPointVoltage = sensor.measureZeroPointVoltage();
  sensor.setZeroPointVoltage(zeroPointVoltage);
  Serial.print("Zero Point (no current) voltage: ");
  Serial.print(zeroPointVoltage);
  Serial.println("mV");
  Serial.println('\n');
  delay(4000);
  menu();
}

void sensitivity() {
  Serial.println("Starting calibrating sensitivity. Info needed ....\n"); 
  Serial.println("Enter the zero point(no current) voltage(mV):");
  while(!Serial.available()){}
  int zeroPointVoltage = Serial.parseInt();

  Serial.println("Enter the current source value (mA):");
  while(!Serial.available()){}
  int currentMilliamps = Serial.parseInt();

  float sensitivity = sensor.calculateSensitivity(zeroPointVoltage, currentMilliamps);
  sensor.setSensitivity(sensitivity);

  Serial.print("Sensitivity:");
  Serial.println(sensitivity);
  delay(4000);
  menu();
}

void measurement() {
  int16_t current = sensor.getCurrentDCMilliamps();
  Serial.print("Current:");
  Serial.print(current);
  Serial.println("mA");
  delay(1000);
}

void menu() {
  Serial.println("Please pick one of the following:\n");
  Serial.println("1 Measure zero point voltage");
  Serial.println("2 Calculate sensitivity");
  Serial.println("3 Measure DC current\n");
  
  while (!Serial.available() > 0) {}
  int option =  Serial.parseInt();

  if (option == 1) {
    zeroPointVoltage();      
  }
  
  else if (option == 2) {
    sensitivity();
  }

  else if (option == 3) {
     measurement();
  }
  
  else {
    menu();
  }
  
}

void setup() {
  Serial.begin(9600);

  ads.setGain(GAIN_ONE);  // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.begin();
  sensor.setADS1115(&ads);
  menu();
}

void loop() {

}
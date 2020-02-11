#include "ACS712_ADS1115.h"

ACS712_ADS1115::ACS712_ADS1115(int _ainx) {
    ainx = _ainx;
    zeroVoltage = 2500; //default 2.5V zero point voltage
    millivoltsPerBit = 0.185;
    sensitivity = 66.0;
}

void ACS712_ADS1115::setADS1115(Adafruit_ADS1115 *_ads) {
    ads = _ads;
    adsGain_t t = _ads->getGain();

	switch(t) {
      case GAIN_TWOTHIRDS:
        millivoltsPerBit = 0.185;
        break;
      case GAIN_ONE:
        millivoltsPerBit = 0.125;
        break;

	}
	
}

void ACS712_ADS1115::setSensitivity(float _sensitivity) {
  sensitivity = _sensitivity;
}

int16_t ACS712_ADS1115::readADCValue() {
  int16_t adc = ads->readADC_SingleEnded(ainx);
  return adc;
}

int16_t ACS712_ADS1115::ADCtoMillivolts(int16_t adc) {
	return (int16_t) (adc * millivoltsPerBit);
}

int16_t ACS712_ADS1115::getVoltageMillivolts() {
	int16_t reading = readADCValue();
	return ADCtoMillivolts(reading);
}

int16_t ACS712_ADS1115::smoothADCValue() {
	float weight = 0.5;
	int16_t acc = 0;
    int16_t newValue = 0;
    int16_t previousValue = readADCValue();
    int16_t smoothValue = 0;

	for (int i = 0; i < OVERSAMPLE_SMOOTH - 1; i++) {
		delay(ADS1115_ADDITIONAL_DELAY);
		newValue = readADCValue();
        smoothValue = (int16_t) (weight * previousValue + (1 - weight) * newValue);
        previousValue = newValue; 
	}

	return smoothValue;	
}

int16_t ACS712_ADS1115::getZeroPointVoltage() {
	return zeroVoltage;
}

void ACS712_ADS1115::setZeroPointVoltage(int16_t _zeroVoltage) {
	zeroVoltage = _zeroVoltage;
}

double ACS712_ADS1115::getMillivoltsPerBit() {
	return millivoltsPerBit;
}

int16_t ACS712_ADS1115::measureZeroPointVoltage() {
	int16_t maxReading = 0;

	for (int i=0; i<OVERSAMPLE_CALIBRATION; i++) {
	  int16_t reading = readADCValue();
	  if (reading > maxReading) 
	    maxReading = reading;
	}
	
	return ADCtoMillivolts(maxReading); 
}


int16_t ACS712_ADS1115::getVoltageMillivoltsFromZeroPoint() {
  int16_t reading = getVoltageMillivolts();
  return reading - zeroVoltage;
}

int16_t ACS712_ADS1115::getCurrentDCMilliamps() {
	int16_t acc = getVoltageMillivoltsFromZeroPoint();
	int16_t result = (int16_t) ((acc * 1000.0) / sensitivity);
	if (result < 0) return 0;
	return result;
} 

float ACS712_ADS1115::calculateSensitivity(int16_t _zeroVoltage, int16_t _currentMilliamps) {
    int voltage = getVoltageMillivolts();
    float _sensitivity = 1000.0 * (voltage - _zeroVoltage) / _currentMilliamps;
    return _sensitivity;
}

float ACS712_ADS1115::getCurrentDC() {
	return getCurrentDCMilliamps() / 1000.0;
}
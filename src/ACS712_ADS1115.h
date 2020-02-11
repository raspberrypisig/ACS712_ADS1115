#ifndef ACS712_ADS1115_h
#define ACS712_ADS1115_h

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define ADC_SCALE 32767.0
#define DEFAULT_FREQUENCY 50
#define ADS1115_ADDITIONAL_DELAY 2

#define ACS712_05B_SENSITIVITY 185
#define ACS712_20A_SENSITIVITY 100
#define ACS712_30A_SENSITIVITY 66

#define OVERSAMPLE_CALIBRATION 1024
#define OVERSAMPLE_SMOOTH 16

enum ACS712_variant {ACS712_05B, ACS712_20A, ACS712_30A};

class ACS712_ADS1115 {
public:
	ACS712_ADS1115(int _ainx);
	void setADS1115(Adafruit_ADS1115 *_ads);
	void setSensitivity(float _sensitivity);
	void setZeroPointVoltage(int16_t _zeroVoltage);
	float getCurrentDC();
	int16_t getCurrentDCMilliamps();
	int16_t measureZeroPointVoltage();
	float calculateSensitivity(int16_t _zeroVoltage, int16_t _currentMilliamps);

	int16_t getVoltageMillivolts();
	int16_t getZeroPointVoltage();
	int16_t readADCValue();
	int16_t smoothADCValue();
	int16_t getVoltageMillivoltsFromZeroPoint();
	int16_t ADCtoMillivolts(int16_t adc);
	double getMillivoltsPerBit();

private:
	double millivoltsPerBit;
    int16_t zeroVoltage;
	float sensitivity;
	int ainx;
	Adafruit_ADS1115 *ads;
};


#endif
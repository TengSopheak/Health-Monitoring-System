#ifndef MALE_H
#define MALE_H

#include "../child/child.h"
using namespace std;

class Male : public Child {
private:
	string heartRateInterval;
	string bloodPressureInterval;
	string temperatureInterval;

	bool isHeartRateNormal;
	bool isBloodPressureNormal;
	bool isTemperatureNormal;

public:
	Male();

	void heartRate(int age, int bpm);
	void bloodPressure(int age, int sys, int dia);
	void temperature(int age, double temp);

	string getHeartRateInterval() const;
	string getBloodPressureInterval() const;
	string getTemperatureInterval() const;

	bool getHeartRateNormal() const;
	bool getBloodPressureNormal() const;
	bool getTemperatureNormal() const;
};

#endif

#ifndef CHILD_H
#define CHILD_H

#include <string>
using namespace std;

class Child {
private:
	string heartRateInterval;
	string bloodPressureInterval;
	string temperatureInterval;

	bool isHeartRateNormal;
	bool isBloodPressureNormal;
	bool isTemperatureNormal;

public:
	Child();

	void heartRate(const string& ageGroup, int bpm);
	void bloodPressure(const string& ageGroup, int sys, int dia);
	void temperature(const string& ageGroup, double temp);

	string getHeartRateInterval() const;
	string getBloodPressureInterval() const;
	string getTemperatureInterval() const;

	bool getHeartRateNormal() const;
	bool getBloodPressureNormal() const;
	bool getTemperatureNormal() const;
};

#endif

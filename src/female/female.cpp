#include <iostream>
#include <string>

#include "../child/child.h"
#include "female.h"
using namespace std;

// Constructor
Female::Female() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

// Override the heartRate function in class Child
void Female::heartRate(int age, int bpm) {
	heartRateInterval = "66 - 78";
	if (age >= 18 && age <= 25) {
		if (bpm >= 66 && bpm <= 78) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 26 && age <= 35) {
		heartRateInterval = "65 - 76";
		if (bpm >= 65 && bpm <= 76) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 36 && age <= 45) {
		heartRateInterval = "65 - 78";
		if (bpm >= 65 && bpm <= 78) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 46 && age <= 55) {
		heartRateInterval = "66 - 77";
		if (bpm >= 66 && bpm <= 77) {
			isHeartRateNormal = true;
		}
		isHeartRateNormal = false;
	}

	if (age >= 56 && age <= 65) {
		heartRateInterval = "65 - 77";
		if (bpm >= 65 && bpm <= 77) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age > 65) {
		heartRateInterval = "65 - 76";
		if (bpm >= 65 && bpm <= 76) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}
}

// Override the bloodPressure function in class Child
void Female::bloodPressure(int age, int sys, int dia) {
	if (age >= 18 && age <= 39) {
		bloodPressureInterval = "< 110 / < 68";
		if ((sys < 110) && (dia < 68)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (age >= 40 && age <= 59) {
		bloodPressureInterval = "< 122 / < 74";
		if ((sys < 122) && (dia < 74)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (age >= 60) {
		bloodPressureInterval = "< 139 / < 68";
		if ((sys < 139) && (dia < 68)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}
}

// Override the temperature function in class Child
void Female::temperature(int age, double temp) {
	if (age >= 18 && age <= 64) {
		temperatureInterval = "36.2 - 37.8";
		if (temp >= 36.2 && temp <= 37.8) {
			isTemperatureNormal = true;
		}
		else {
			isTemperatureNormal = false;
		}
	}

	if (age >= 65) {
		temperatureInterval = "35.5 - 37.1";
		if (temp >= 35.5 && temp <= 37.1) {
			isTemperatureNormal = true;
		}
		else {
			isTemperatureNormal = false;
		}
	}
}

// This is the same as class Child
string Female::getHeartRateInterval() const {
	return heartRateInterval;
}

string Female::getBloodPressureInterval() const {
	return bloodPressureInterval;
}

string Female::getTemperatureInterval() const {
	return temperatureInterval;
}

bool Female::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Female::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Female::getTemperatureNormal() const {
	return isTemperatureNormal;
}
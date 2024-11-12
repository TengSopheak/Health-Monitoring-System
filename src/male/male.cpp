#include <iostream>
#include <string>
#include "../child/child.h"
#include "male.h"
using namespace std;

Male::Male() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

// Override the heartRate function in class Child
void Male::heartRate(int age, int bpm) {
	if (age >= 18 && age <= 25) {
		heartRateInterval = "62 - 73";
		if (bpm >= 62 && bpm <= 73) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 26 && age <= 35) {
		heartRateInterval = "62 - 74";
		if (bpm >= 62 && bpm <= 74) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 36 && age <= 45) {
		heartRateInterval = "63 - 75";
		if (bpm >= 63 && bpm <= 75) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 46 && age <= 55) {
		heartRateInterval = "63 - 76";
		if (bpm >= 63 && bpm <= 76) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age >= 56 && age <= 65) {
		heartRateInterval = "62 - 75";
		if (bpm >= 62 && bpm <= 75) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (age > 65) {
		heartRateInterval = "62 - 73";
		if (bpm >= 62 && bpm <= 73) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}
}

// Override the bloodPressure function in class Child
void Male::bloodPressure(int age, int sys, int dia) {
	if (age >= 18 && age <= 39) {
		bloodPressureInterval = "< 119 / < 70";
		if ((sys < 119) && (dia < 70)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (age >= 40 && age <= 59) {
		bloodPressureInterval = "< 124 / < 77";
		if ((sys < 124) && (dia < 77)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (age >= 60) {
		bloodPressureInterval = "< 133 / < 69";
		if ((sys < 133) && (dia < 69)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}
}

// Override the temperature function in class Child
void Male::temperature(int age, double temp) {
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
string Male::getHeartRateInterval() const {
	return heartRateInterval;
}

string Male::getBloodPressureInterval() const {
	return bloodPressureInterval;
}

string Male::getTemperatureInterval() const {
	return temperatureInterval;
}

bool Male::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Male::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Male::getTemperatureNormal() const {
	return isTemperatureNormal;
}
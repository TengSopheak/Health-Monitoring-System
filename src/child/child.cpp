#include <iostream>
#include <string>
#include "child.h"
using namespace std;

// Constructor
Child::Child() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

void Child::heartRate(const string& ageGroup, int bpm) {
	if (ageGroup == "Newborn") {
		heartRateInterval = "100 - 205";
		if (bpm >= 100 && bpm <= 205) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (ageGroup == "Infant") {
		heartRateInterval = "100 - 180";
		if (bpm >= 100 && bpm <= 180) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (ageGroup == "Toddler") {
		heartRateInterval = "98 - 140";
		if (bpm >= 98 && bpm <= 140) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (ageGroup == "Preschooler") {
		heartRateInterval = "80 - 120";
		if (bpm >= 80 && bpm <= 120) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (ageGroup == "School-aged child") {
		heartRateInterval = "75 - 118";
		if (bpm >= 75 && bpm <= 118) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}

	if (ageGroup == "Teenager") {
		heartRateInterval = "60 - 100";
		if (bpm >= 60 && bpm <= 100) {
			isHeartRateNormal = true;
		}
		else {
			isHeartRateNormal = false;
		}
	}
}


// sys for Systolic and dia for Diastolic (in excel sheet)
void Child::bloodPressure(const string& ageGroup, int sys, int dia) {
	if (ageGroup == "Newborn") {
		bloodPressureInterval = "60 - 90 / 20 - 60";
		if ((sys >= 60 && sys <= 90) && (dia >= 20 && dia <= 60)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (ageGroup == "Infant") {
		bloodPressureInterval = "87 - 105 / 53 - 66";
		if ((sys >= 87 && sys <= 105) && (dia >= 53 && dia <= 66)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (ageGroup == "Toddler") {
		bloodPressureInterval = "95 - 105 / 53 - 66";
		if ((sys >= 95 && sys <= 105) && (dia >= 53 && dia <= 66)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (ageGroup == "Preschooler") {
		bloodPressureInterval = "95 - 110 / 56 - 70";
		if ((sys >= 95 && sys <= 110) && (dia >= 56 && dia <= 70)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (ageGroup == "School-aged child") {
		bloodPressureInterval = "97 - 112 / 57 - 71";
		if ((sys >= 97 && sys <= 112) && (dia >= 57 && dia <= 71)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}

	if (ageGroup == "Teenager") {
		bloodPressureInterval = "112 - 128 / 66 - 80";
		if ((sys >= 112 && sys <= 128) && (dia >= 66 && dia <= 80)) {
			isBloodPressureNormal = true;
		}
		else {
			isBloodPressureNormal = false;
		}
	}
}


// in degree celsius
void Child::temperature(const string& ageGroup, double temp) {
	if (ageGroup == "Newborn" || ageGroup == "Infant" || ageGroup == "Toddler" ||
		ageGroup == "Preschooler" || ageGroup == "School-aged child") {

		temperatureInterval = "35.2 - 37.8";

		if (temp >= 35.2 && temp <= 37.8) {
			isTemperatureNormal = true;
		}
		else {
			isTemperatureNormal = false;
		}
	}

	if (ageGroup == "Teenager") {
		temperatureInterval = "36.2 - 37.8";
		if (temp >= 36.2 && temp <= 37.8) {
			isTemperatureNormal = true;
		}
		else {
			isTemperatureNormal = false;
		}
	}
}


// For encapsulation, we only use Getter (no Setter)
// because we don't need to manually modify the boolean values.
string Child::getHeartRateInterval() const {
	return heartRateInterval;
}

string Child::getBloodPressureInterval() const {
	return bloodPressureInterval;
}

string Child::getTemperatureInterval() const {
	return temperatureInterval;
}

bool Child::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Child::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Child::getTemperatureNormal() const {
	return isTemperatureNormal;
}

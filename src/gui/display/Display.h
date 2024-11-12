#ifndef DISPLAY_H
#define DISPLAY_H

#include "..src/database/databaseConnection.h"

#include <wx/wx.h>

class Display : public wxFrame {
public:
	Display(const wxString& title, int id, std::string name, std::string gender, std::string ageGroup, std::string exactAge,
		int heartRate, int bloodPressure1, int bloodPressure2, double temperature);

private:
	DatabaseConnection dbConnection;
	PGconn* conn = dbConnection.getConnection();

	wxPanel* panel;

	// 1
	wxStaticText* patientText;
	wxStaticText* patientName;
	wxStaticText* patientGender;
	wxStaticText* patientAgeGroup;
	wxStaticText* patientExactAge;

	// 2
	wxStaticText* testsText;
	wxStaticText* resultsText;
	wxStaticText* unitsText;
	wxStaticText* referenceIntervalText;
	wxStaticText* normalityText;

	// 3
	wxStaticText* heartRateText;
	wxStaticText* bloodPressureText;
	wxStaticText* temperatureCelsiusText;
	// 4
	wxStaticText* heartRateResult;
	wxStaticText* bloodPressureResult;
	wxStaticText* temperatureCelsiusResult;

	// 5
	wxStaticText* heartRateUnit;
	wxStaticText* bloodPressureUnit;
	wxStaticText* temperatureCelsiusUnit;

	std::string retrievedHeartRateInterval;
	std::string retrievedBloodPressureInterval;
	std::string retrievedTemperatureCelsiusInterval;

	bool retrievedIsHeartRateNormal;
	bool retrievedIsBloodPressureNormal;
	bool retrievedIsTemperatureNormal;

	wxStaticText* heartRateInterval;
	wxStaticText* bloodPressureInterval;
	wxStaticText* temperatureCelsiusInterval;

	wxStaticText* heartRateNormality;
	wxStaticText* bloodPressureNormality;
	wxStaticText* temperatureCelsiusNormality;

	// Database Retrieval
	int retrievedId;
	std::string retrievedName;
	std::string retrievedGender;
	std::string retrievedAgeGroup;
	std::string retrievedExactAge;
	int retrievedHeartRate;
	int retrievedBloodPressure1;
	int retrievedBloodPressure2;
	double retrievedTemperature;

	wxButton* previousButton;
	wxButton* nextButton;

	void drawShape(wxPaintEvent& event);
	void Initialize(const std::string gender, const std::string ageGroup, const std::string exactAge,
		int heartRate, int bloodPressure1, int bloodPressure2, double temperature);
	void checkNormality(wxPanel* panel, wxFont font4);

	bool checkPreviousPatient(PGconn* conn, int currentPatientId);
	bool checkNextPatient(PGconn* conn, int currentPatientId);

	void previousButtonClicked(wxCommandEvent& event);
	void nextButtonClicked(wxCommandEvent& event);

	void setData(const std::string name, const std::string gender, const std::string ageGroup, const std::string exactAge,
		int heartRate, int bloodPressure1, int bloodPressure2, double temperature);
};

#endif
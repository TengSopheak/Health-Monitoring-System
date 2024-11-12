#ifndef FRAME2_H
#define FRAME2_H

#include "../src/database/databaseConnection.h"
#include <iostream>
#include <libpq-fe.h>
#include <wx/wx.h>


class Frame2 : public wxFrame {
	public:
		Frame2(const wxString& title);

	private:
		DatabaseConnection dbConnection;
		PGconn* conn = dbConnection.getConnection();

		std::string storedName;
		std::string storedGender;
		bool isMaleChecked;
		bool isFemaleChecked;
		std::string storedAgeGroup;
		std::string storedExactAge;

		int storedHeartRate;
		int storedBloodPressure1;
		int storedBloodPressure2;
		double storedTemperature;

		wxStaticText* welcomeText;
		wxStaticText* instructionText;
		wxStaticText* nameText;
		wxStaticText* genderText;
		wxStaticText* ageGroupText;
		wxStaticText* exactAgeText;
		wxStaticText* heartRateText;
		wxStaticText* bloodPressureText;
		wxStaticText* temperatureText;
		wxStaticText* labelText;

		wxTextCtrl* nameInput;
		wxTextCtrl* heartRateInput;
		wxTextCtrl* bloodPressureInput1;
		wxTextCtrl* bloodPressureInput2;
		wxTextCtrl* temperatureInput;
		wxTextCtrl* exactAgeInput;

		wxCheckBox* maleCheckBox;
		wxCheckBox* femaleCheckBox;

		wxChoice* ageGroupChoice;

		wxButton* continueButton;

		void drawLine(wxPaintEvent& event);
		void styleInputBox(wxTextCtrl* nameInput);
		void styleButton(wxButton* continueButton);
		void continueButtonClicked(wxCommandEvent& event);
};

#endif
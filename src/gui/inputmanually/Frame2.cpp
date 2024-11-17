#include "Frame2.h"
#include "../display/Frame3.h"
#include "../database/databaseConnection.h"

#include <iostream>
#include <wx/font.h>

Frame2::Frame2(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 680),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    wxPanel* panel = new wxPanel(this);

    // Welcome Text
    welcomeText = new wxStaticText(panel, wxID_ANY, "Welcome!", wxPoint(165.3, 15.1));
    wxFont font1(37.3, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    welcomeText->SetFont(font1);
    welcomeText->SetForegroundColour(*wxBLACK);

    // Draw the line that seperates Welcome and Instruction text, and Instruction text and input
    panel->Bind(wxEVT_PAINT, &Frame2::drawLine, this);

    // set font for all
    wxFont staticFont(18.7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    wxFont boxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    // Instruction Text
    instructionText = new wxStaticText(panel, wxID_ANY,
        "Please enter the details below to monitor your\n"
        "health metrics. This information will help us track\n"
        "your health status accurately.",
        wxPoint(25, 113.2));
    
    instructionText->SetFont(staticFont);
    instructionText->SetForegroundColour(*wxBLACK);

    // Name Text
    nameText = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(25, 263.7));
    nameText->SetFont(staticFont);
    nameText->SetForegroundColour(*wxBLACK);

    nameInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(25, 298.9), wxSize(205.1, 33.7));

    genderText = new wxStaticText(panel, wxID_ANY, "Gender", wxPoint(25, 343.3));
    genderText->SetFont(staticFont);
    genderText->SetForegroundColour(*wxBLACK);

    maleCheckBox = new wxCheckBox(panel, wxID_ANY, " Male", wxPoint(46.4, 383.1), wxSize(210, 25));
    maleCheckBox->SetFont(boxFont);
    maleCheckBox->SetForegroundColour(*wxBLACK);

    femaleCheckBox = new wxCheckBox(panel, wxID_ANY, " Female", wxPoint(46.4, 421.5), wxSize(210, 25));
    femaleCheckBox->SetFont(boxFont);
    femaleCheckBox->SetForegroundColour(*wxBLACK);

    ageGroupText = new wxStaticText(panel, wxID_ANY, "Age Group", wxPoint(25, 459.9));
    ageGroupText->SetFont(staticFont);
    ageGroupText->SetForegroundColour(*wxBLACK);

    wxArrayString choices = {
        "Newborn",
        "Infant",
        "Toddler",
        "Preschooler",
        "School-aged child",
        "Teenager",
        "Adult",
        "Older Adult"
    };
    ageGroupChoice = new wxChoice(panel, wxID_ANY, wxPoint(25, 497.2), wxSize(190, 33.7), choices);
    ageGroupChoice->SetFont(boxFont);
    ageGroupChoice->SetForegroundColour(*wxBLACK);

    exactAgeText = new wxStaticText(panel, wxID_ANY,
        "What is your\n"
        "exact age?",
        wxPoint(25, 540.9));
    exactAgeText->SetFont(boxFont);
    exactAgeText->SetForegroundColour(*wxBLACK);

    exactAgeInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(127.5, 567.8), wxSize(100, 26.9));
    wxFont exactAgeFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    exactAgeInput->SetFont(exactAgeFont);
    exactAgeInput->SetForegroundColour(*wxBLACK);

    heartRateText = new wxStaticText(panel, wxID_ANY, "Heart Rate (bpm)", wxPoint(294, 263.7));
    heartRateText->SetFont(staticFont);
    heartRateText->SetForegroundColour(*wxBLACK);

    heartRateInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 298.9), wxSize(100, 33.7));

    bloodPressureText = new wxStaticText(panel, wxID_ANY, "Blood Pressure (mmHg)", wxPoint(294, 345.9));
    bloodPressureText->SetFont(staticFont);
    bloodPressureText->SetForegroundColour(*wxBLACK);

    bloodPressureInput1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 381.1), wxSize(70, 33.7));
    bloodPressureInput2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(394, 381.1), wxSize(70, 33.7));

    temperatureText = new wxStaticText(panel, wxID_ANY, "Temperature (°C)", wxPoint(294, 428.2));
    temperatureText->SetFont(staticFont);
    temperatureText->SetForegroundColour(*wxBLACK);

    temperatureInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 463.4), wxSize(100, 33.7));

    continueButton = new wxButton(panel, wxID_ANY, "Continue", wxPoint(294, 517.2), wxSize(142.7, 40));

    labelText = new wxStaticText(panel, wxID_ANY, "", wxPoint(25, 606.7));
    wxFont labelTextFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    labelText->SetFont(labelTextFont);
    labelText->SetForegroundColour(*wxRED);

    styleInputBox(nameInput);
    styleInputBox(heartRateInput);
    styleInputBox(bloodPressureInput1);
    styleInputBox(bloodPressureInput2);
    styleInputBox(temperatureInput);

    styleButton(continueButton);

    continueButton->Bind(wxEVT_BUTTON, &Frame2::continueButtonClicked, this);
}

void Frame2::drawLine(wxPaintEvent& event)
{
    // Get the panel from the event (if needed)
    wxPanel* panel = dynamic_cast<wxPanel*>(event.GetEventObject());

    // Create a wxPaintDC object to perform drawing
    wxPaintDC dc(panel);

    // Set the pen for drawing
    wxPen pen(*wxBLACK, 2); // Black color, 2 pixels wide
    dc.SetPen(pen);

    dc.DrawLine(172.6, 88.2, 407.4, 88.2);
    dc.DrawLine(25, 236.7, 555, 236.7);
}

void Frame2::styleInputBox(wxTextCtrl* inputBox)
{
    inputBox->SetBackgroundColour(*wxWHITE);
    inputBox->SetForegroundColour(*wxBLACK);
    wxFont inputFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    inputBox->SetFont(inputFont);
}

void Frame2::styleButton(wxButton* continueButton)
{
    continueButton->SetBackgroundColour(wxColour("#7ed957"));
    continueButton->SetForegroundColour(*wxBLACK);
    wxFont inputFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    continueButton->SetFont(inputFont);
}

void Frame2::continueButtonClicked(wxCommandEvent& event)
{
    // Retrieve input values
    wxString name = nameInput->GetValue();
    bool isMaleChecked = maleCheckBox->IsChecked();
    bool isFemaleChecked = femaleCheckBox->IsChecked();
    int selectionIndex = ageGroupChoice->GetSelection(); // Get the index of the selected item
    wxString selectedAgeGroup;
    wxString exactAge = exactAgeInput->GetValue();
    wxString heartRate = heartRateInput->GetValue();
    wxString bloodPressure1 = bloodPressureInput1->GetValue();
    wxString bloodPressure2 = bloodPressureInput2->GetValue();
    wxString temperature = temperatureInput->GetValue();

    if ((!name.IsEmpty()) && (isMaleChecked || isFemaleChecked) && (selectionIndex != wxNOT_FOUND) &&
        (!heartRate.IsEmpty()) && (!bloodPressure1.IsEmpty()) && (!bloodPressure2.IsEmpty()) && (!temperature.IsEmpty()) &&
        (!exactAge.IsEmpty()))
    {
        // Store user inputs
        storedName = name.ToStdString();
        // Get the string of the selected item
        selectedAgeGroup = ageGroupChoice->GetStringSelection();
        storedAgeGroup = selectedAgeGroup.ToStdString();
        storedExactAge = exactAge.ToStdString();
        storedHeartRate = wxAtoi(heartRate);
        storedBloodPressure1 = wxAtoi(bloodPressure1);
        storedBloodPressure2 = wxAtoi(bloodPressure2);
        storedTemperature = wxAtof(temperature);

        std::string newbornExactAgeList[5] =
        {
            "Birth", "1 week", "2 weeks", "3 weeks", "4 weeks"
        };

        std::string infantExactAgeList[11] =
        {
            "1 month", "2 months", "3 months", "4 months", "5 months",
            "6 months", "7 months", "8 months", "9 months", "10 months",
            "11 months"
        };

        if (storedHeartRate < 0 || storedBloodPressure1 < 0 || storedBloodPressure2 < 0 || storedTemperature < 0)
        {
            labelText->SetLabel("Please input only positive numbers!");
            return;
        }
        if (isMaleChecked && isFemaleChecked)
        {
            labelText->SetLabel("Select Male or Female, not Both!");
            return;
        }
        else if (selectedAgeGroup == "Newborn" && std::find(std::begin(newbornExactAgeList), std::end(newbornExactAgeList), exactAge) == std::end(newbornExactAgeList))
        {
            labelText->SetLabel("Newborn age must be between Birth and 4 weeks!");
            return;
        }
        else if (selectedAgeGroup == "Infant" && std::find(std::begin(infantExactAgeList), std::end(infantExactAgeList), exactAge) == std::end(infantExactAgeList))
        {
            labelText->SetLabel("Infant age must be between 1 and 11 months!");
            return;
        }
        else if (selectedAgeGroup == "Toddler" && (wxAtoi(exactAge) < 1 || wxAtoi(exactAge) > 3))
        {
            labelText->SetLabel("Infant age must be between 1 and 3!");
            return;
        }
        else if (selectedAgeGroup == "Preschooler" && (wxAtoi(exactAge) < 4 || wxAtoi(exactAge) > 5))
        {
            labelText->SetLabel("Preschooler age must either be 4 or 5!");
            return;
        }
        else if (selectedAgeGroup == "School-aged child" && (wxAtoi(exactAge) < 6 || wxAtoi(exactAge) > 12))
        {
            labelText->SetLabel("School-aged child age must be between 6 and 12!");
            return;
        }
        else if (selectedAgeGroup == "Teenager" && (wxAtoi(exactAge) < 13 || wxAtoi(exactAge) > 17))
        {
            labelText->SetLabel("Teenager age must be between 13 and 17!");
            return;
        }
        else if (selectedAgeGroup == "Adult" && (wxAtoi(exactAge) < 18 || wxAtoi(exactAge) > 64))
        {
            labelText->SetLabel("Adult age must be between 18 and 64!");
            return;
        }
        else if (selectedAgeGroup == "Older Adult" && (wxAtoi(exactAge) < 65 || wxAtoi(exactAge) > 120))
        {
            labelText->SetLabel("Older Adult age must be between 65 and 120!");
            return;
        }
        else
        {
            // Set gender based on selection
            storedGender = isMaleChecked ? "Male" : "Female";

            if (!conn) {
                labelText->SetLabel("Database connection error.");
                return;
            }

            // Insert data into the database
            dbConnection.insertPatientData(conn, storedName, storedGender, storedAgeGroup, storedExactAge,
                storedHeartRate, storedBloodPressure1, storedBloodPressure2, storedTemperature);

            // Initialize image handlers
            wxInitAllImageHandlers();

            // Open Frame3
            Frame3* frame3 = new Frame3("Health Monitor", storedName, storedGender, storedAgeGroup, storedExactAge, storedHeartRate,
                storedBloodPressure1, storedBloodPressure2, storedTemperature);
            frame3->Show();

            // Close the current frame (Frame3)
            Close();
        }
    }
    else {
        labelText->SetLabel("Please don't leave anything blank!");
    }
}
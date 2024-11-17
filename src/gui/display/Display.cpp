#include "Display.h"
#include "../child/child.h"
#include "../male/male.h"
#include "../female/female.h"
#include "..src/database/databaseConnection.h"

#include <wx/font.h>

Display::Display(const wxString& title, int id, std::string name, std::string gender, std::string ageGroup, std::string exactAge,
    int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1920, 730),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), retrievedId(id)
{
    panel = new wxPanel(this);

    // Draw line that separates the Patient Text and Patient Information and other necessary shapes
    panel->Bind(wxEVT_PAINT, &Display::drawShape, this);

    // Patient Text
    patientText = new wxStaticText(panel, wxID_ANY, "", wxPoint(838.4, 4.5));
    patientText->SetLabel("Patient #" + std::to_string(retrievedId));

    wxFont font1(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    patientText->SetFont(font1);
    patientText->SetForegroundColour(*wxBLACK);

    // Patient Information
    patientName = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 122.9));
    patientGender = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 175.7));
    patientAgeGroup = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 226.2));
    patientExactAge = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 278.9));

    wxFont font2(28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    patientName->SetFont(font2);
    patientName->SetForegroundColour(*wxBLACK);
    patientGender->SetFont(font2);
    patientGender->SetForegroundColour(*wxBLACK);
    patientAgeGroup->SetFont(font2);
    patientAgeGroup->SetForegroundColour(*wxBLACK);
    patientExactAge->SetFont(font2);
    patientExactAge->SetForegroundColour(*wxBLACK);

    // Load Monitor Image
    wxImage image;
    if (!image.LoadFile("monitor.png", wxBITMAP_TYPE_PNG)) {
        wxLogError("Could not load image");
        return;
    }

    wxSize imageSize(static_cast<int>(226.7), static_cast<int>(226.7));
    image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

    wxBitmap bitmap(image);

    wxPoint imagePosition(static_cast<int>(1106.2), static_cast<int>(109.9));
    wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

    wxFont font3(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    wxFont font4(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    testsText = new wxStaticText(panel, wxID_ANY, "TESTS", wxPoint(26.2, 366.7));
    testsText->SetFont(font3);
    testsText->SetForegroundColour(*wxWHITE);
    testsText->SetBackgroundColour(wxColour(56, 182, 255));

    resultsText = new wxStaticText(panel, wxID_ANY, "RESULTS", wxPoint(350, 366.7));
    resultsText->SetFont(font3);
    resultsText->SetForegroundColour(*wxWHITE);
    resultsText->SetBackgroundColour(wxColour(56, 182, 255));

    unitsText = new wxStaticText(panel, wxID_ANY, "UNITS", wxPoint(750, 366.7));
    unitsText->SetFont(font3);
    unitsText->SetForegroundColour(*wxWHITE);
    unitsText->SetBackgroundColour(wxColour(56, 182, 255));

    referenceIntervalText = new wxStaticText(panel, wxID_ANY, "REFERENCE INTERVAL", wxPoint(1104.5, 366.7));
    referenceIntervalText->SetFont(font3);
    referenceIntervalText->SetForegroundColour(*wxWHITE);
    referenceIntervalText->SetBackgroundColour(wxColour(56, 182, 255));

    normalityText = new wxStaticText(panel, wxID_ANY, "NORMALITY", wxPoint(1629.5, 366.7));
    normalityText->SetFont(font3);
    normalityText->SetForegroundColour(*wxWHITE);
    normalityText->SetBackgroundColour(wxColour(56, 182, 255));

    heartRateText = new wxStaticText(panel, wxID_ANY, "Heart Rate", wxPoint(26.2, 430.4));
    heartRateText->SetFont(font4);
    heartRateText->SetForegroundColour(*wxBLACK);

    bloodPressureText = new wxStaticText(panel, wxID_ANY, "Blood Pressure", wxPoint(26.2, 491.9));
    bloodPressureText->SetFont(font4);
    bloodPressureText->SetForegroundColour(*wxBLACK);

    temperatureCelsiusText = new wxStaticText(panel, wxID_ANY, "Temperature (°C)", wxPoint(26.2, 553.4));
    temperatureCelsiusText->SetFont(font4);
    temperatureCelsiusText->SetForegroundColour(*wxBLACK);

    heartRateResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 430.4));
    bloodPressureResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(385, 491.9));
    temperatureCelsiusResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(400, 553.4));

    heartRateResult->SetFont(font4);
    heartRateResult->SetForegroundColour(*wxBLACK);
    bloodPressureResult->SetFont(font4);
    bloodPressureResult->SetForegroundColour(*wxBLACK);
    temperatureCelsiusResult->SetFont(font4);
    temperatureCelsiusResult->SetForegroundColour(*wxBLACK);

    heartRateUnit = new wxStaticText(panel, wxID_ANY, "bpm (beat per minute)", wxPoint(661.6, 430.4));
    heartRateUnit->SetFont(font4);
    heartRateUnit->SetForegroundColour(*wxBLACK);

    bloodPressureUnit = new wxStaticText(panel, wxID_ANY, "mmHg (millimeters of mercury)", wxPoint(584.2, 491.9));
    bloodPressureUnit->SetFont(font4);
    bloodPressureUnit->SetForegroundColour(*wxBLACK);

    temperatureCelsiusUnit = new wxStaticText(panel, wxID_ANY, "°C (Degree Celsius)", wxPoint(674.3, 553.4));
    temperatureCelsiusUnit->SetFont(font4);
    temperatureCelsiusUnit->SetForegroundColour(*wxBLACK);

    heartRateInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1234, 430.4));
    bloodPressureInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1187, 491.9));
    temperatureCelsiusInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1224, 553.4));

    Initialize(gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature);

    heartRateInterval->SetLabel(retrievedHeartRateInterval);
    bloodPressureInterval->SetLabel(retrievedBloodPressureInterval);
    temperatureCelsiusInterval->SetLabel(retrievedTemperatureCelsiusInterval);

    heartRateInterval->SetFont(font4);
    heartRateInterval->SetForegroundColour(*wxBLACK);

    bloodPressureInterval->SetFont(font4);
    bloodPressureInterval->SetForegroundColour(*wxBLACK);

    temperatureCelsiusInterval->SetFont(font4);
    temperatureCelsiusInterval->SetForegroundColour(*wxBLACK);

    heartRateNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712.3, 430.4));
    bloodPressureNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712.3, 491.9));
    temperatureCelsiusNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712.3, 553.4));

    setData(name, gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature);
    checkNormality(panel, font4);

    previousButton = new wxButton(panel, wxID_ANY, "Previous", wxPoint(10, 620), wxSize(160, 54));
    nextButton = new wxButton(panel, wxID_ANY, "Next", wxPoint(1730, 620), wxSize(160, 54)); 
    returnButton = new wxButton(panel, wxID_ANY, "Return", wxPoint(870, 620), wxSize(160, 54));

    wxFont buttonFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");

    previousButton->SetFont(buttonFont);
    previousButton->SetBackgroundColour(wxColour("#38b6ff"));
    previousButton->SetForegroundColour(*wxWHITE);

    nextButton->SetFont(buttonFont);
    nextButton->SetBackgroundColour(wxColour("#38b6ff"));
    nextButton->SetForegroundColour(*wxWHITE);

    returnButton->SetFont(buttonFont);
    returnButton->SetBackgroundColour(wxColour("#38b6ff"));
    returnButton->SetForegroundColour(*wxWHITE);

    previousButton->Bind(wxEVT_BUTTON, &Display::previousButtonClicked, this);
    nextButton->Bind(wxEVT_BUTTON, &Display::nextButtonClicked, this);
    returnButton->Bind(wxEVT_BUTTON, &Display::returnButtonClicked, this);
}

void Display::drawShape(wxPaintEvent& event)
{
    wxPanel* panel = dynamic_cast<wxPanel*>(event.GetEventObject());

    wxPaintDC dc(panel);

    dc.SetPen(wxPen(wxColour("#38b6ff"), 2)); // Outline color
    dc.SetBrush(wxBrush(wxColour("#38b6ff"))); // Fill color

    dc.DrawLine(552.6, 87.5, 1367.4, 87.5);
    dc.DrawRectangle(0, 359, 1920, 54); // Draw a rectangle
}

bool Display::checkPreviousPatient(PGconn* conn, int currentPatientId)
{
    const char* query = "SELECT id FROM patient_health_data WHERE id < $1 ORDER BY id DESC LIMIT 1;";

    // Convert id to string for parameter
    std::string idStr = std::to_string(currentPatientId);
    const char* paramValues[1] = { idStr.c_str() };

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        wxMessageBox(wxString::FromUTF8(PQerrorMessage(conn)), "Query Failed", wxICON_ERROR);
        return false;
    }
    else if (PQntuples(res) == 0) {
        // if no previous patient
        return false;
    }
    else {
        // if previous patient found
        return true;
    }

    PQclear(res);
}

bool Display::checkNextPatient(PGconn* conn, int currentPatientId) {
    const char* query = "SELECT id FROM patient_health_data WHERE id > $1 ORDER BY id ASC LIMIT 1;";

    // Convert id to string for parameter
    std::string idStr = std::to_string(currentPatientId);
    const char* paramValues[1] = { idStr.c_str() };

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        wxMessageBox(wxString::FromUTF8(PQerrorMessage(conn)), "Query Failed", wxICON_ERROR);
        return false;
    }
    else if (PQntuples(res) == 0) {
        // if no next patient
        return false;
    }
    else {
        // if next patient found
        return true;
    }

    PQclear(res);
}

void Display::previousButtonClicked(wxCommandEvent& event)
{
    wxFont font4(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    if (checkPreviousPatient(conn, retrievedId))
    {
        dbConnection.retrievePatientData(conn, --retrievedId, retrievedName, retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        Initialize(retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        heartRateInterval->SetLabel(retrievedHeartRateInterval);
        bloodPressureInterval->SetLabel(retrievedBloodPressureInterval);
        temperatureCelsiusInterval->SetLabel(retrievedTemperatureCelsiusInterval);

        setData(retrievedName, retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        checkNormality(panel, font4);

        Refresh();
    }
    else {
        wxMessageBox("No previous patient found.", "No Previous Patient", wxICON_INFORMATION);
    }
}

void Display::nextButtonClicked(wxCommandEvent& event)
{
    wxFont font4(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    if (checkNextPatient(conn, retrievedId))
    {
        dbConnection.retrievePatientData(conn, ++retrievedId, retrievedName, retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        Initialize(retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        heartRateInterval->SetLabel(retrievedHeartRateInterval);
        bloodPressureInterval->SetLabel(retrievedBloodPressureInterval);
        temperatureCelsiusInterval->SetLabel(retrievedTemperatureCelsiusInterval);

        setData(retrievedName, retrievedGender, retrievedAgeGroup, retrievedExactAge,
            retrievedHeartRate, retrievedBloodPressure1, retrievedBloodPressure2, retrievedTemperature);

        checkNormality(panel, font4);

        Refresh();
    }
    else {
        wxMessageBox("No next patient found.", "No Next Patient", wxICON_INFORMATION);
    }
}

void Display::returnButtonClicked(wxCommandEvent& event)
{
    Frame1* frame1 = new Frame1("Health Monitor");
    frame1->Show();

    Close();
}

void Display::setData(const std::string name, const std::string gender, const std::string ageGroup, const std::string exactAge,
    int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
{
    patientText->SetLabel("Patient #" + std::to_string(retrievedId));
    patientName->SetLabel("Name: " + name);
    patientGender->SetLabel("Gender: " + gender);
    patientAgeGroup->SetLabel("Age Group: " + ageGroup);
    patientExactAge->SetLabel("Exact Age (years): " + exactAge);
    heartRateResult->SetLabel(wxString::Format("%d", heartRate));
    bloodPressureResult->SetLabel(wxString::Format("%d / %d", bloodPressure1, bloodPressure2));
    temperatureCelsiusResult->SetLabel(wxString::Format("%.1f", temperature));
}

void Display::Initialize(const std::string gender, const std::string ageGroup, const std::string exactAge,
    int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
{
    // Create instances
    Child child;
    Male male;
    Female female;

    if (ageGroup == "Newborn" || ageGroup == "Infant" || ageGroup == "Toddler" || ageGroup == "Preschooler" ||
        ageGroup == "School-aged child" || ageGroup == "Teenager")
    {
        child.heartRate(ageGroup, heartRate);
        child.bloodPressure(ageGroup, bloodPressure1, bloodPressure2);
        child.temperature(ageGroup, temperature);

        retrievedHeartRateInterval = child.getHeartRateInterval();
        retrievedBloodPressureInterval = child.getBloodPressureInterval();
        retrievedTemperatureCelsiusInterval = child.getTemperatureInterval();

        retrievedIsHeartRateNormal = child.getHeartRateNormal();
        retrievedIsBloodPressureNormal = child.getBloodPressureNormal();
        retrievedIsTemperatureNormal = child.getTemperatureNormal();
    }
    else {
        if (gender == "Male") {
            male.heartRate(std::stoi(exactAge), heartRate);
            male.bloodPressure(std::stoi(exactAge), bloodPressure1, bloodPressure2);
            male.temperature(std::stoi(exactAge), temperature);

            retrievedHeartRateInterval = male.getHeartRateInterval();
            retrievedBloodPressureInterval = male.getBloodPressureInterval();
            retrievedTemperatureCelsiusInterval = male.getTemperatureInterval();

            retrievedIsHeartRateNormal = male.getHeartRateNormal();
            retrievedIsBloodPressureNormal = male.getBloodPressureNormal();
            retrievedIsTemperatureNormal = male.getTemperatureNormal();
        }
        else
        {
            female.heartRate(std::stoi(exactAge), heartRate);
            female.bloodPressure(std::stoi(exactAge), bloodPressure1, bloodPressure2);
            female.temperature(std::stoi(exactAge), temperature);

            retrievedHeartRateInterval = female.getHeartRateInterval();
            retrievedBloodPressureInterval = female.getBloodPressureInterval();
            retrievedTemperatureCelsiusInterval = female.getTemperatureInterval();

            retrievedIsHeartRateNormal = female.getHeartRateNormal();
            retrievedIsBloodPressureNormal = female.getBloodPressureNormal();
            retrievedIsTemperatureNormal = female.getTemperatureNormal();
        }
    }
}

void Display::checkNormality(wxPanel* panel, wxFont font4)
{
    wxImage image;

    if (!retrievedIsHeartRateNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(430.4));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        heartRateNormality->SetLabel("Alert");

        heartRateNormality->SetFont(font4);
        heartRateNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(430.4));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        heartRateNormality->SetLabel("Normal");

        heartRateNormality->SetFont(font4);
        heartRateNormality->SetForegroundColour(wxColour("#4bae4f"));
    }

    if (!retrievedIsBloodPressureNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(491.9));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        bloodPressureNormality->SetLabel("Alert");

        bloodPressureNormality->SetFont(font4);
        bloodPressureNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(491.9));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        bloodPressureNormality->SetLabel("Normal");

        bloodPressureNormality->SetFont(font4);
        bloodPressureNormality->SetForegroundColour(wxColour("#4bae4f"));
    }

    if (!retrievedIsTemperatureNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(553.4));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        temperatureCelsiusNormality->SetLabel("Alert");

        temperatureCelsiusNormality->SetFont(font4);
        temperatureCelsiusNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxSize imageSize(static_cast<int>(37.6), static_cast<int>(37.6));
        image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());

        wxBitmap bitmap(image);

        wxPoint imagePosition(static_cast<int>(1660), static_cast<int>(553.4));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, imagePosition);

        temperatureCelsiusNormality->SetLabel("Normal");

        temperatureCelsiusNormality->SetFont(font4);
        temperatureCelsiusNormality->SetForegroundColour(wxColour("#4bae4f"));
    }
}
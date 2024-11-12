#include <wx/wx.h>
#include "Frame1.h"

class App : public wxApp
{
public:
    bool OnInit()
    {
        Frame1* frame1 = new Frame1("Health Monitor");
        frame1->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);

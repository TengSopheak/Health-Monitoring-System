#ifndef APP_H
#define APP_H

#include <wx/wx.h>
#include "Frame1.h"

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    Frame1* frame1{ nullptr };  // Main window of the application
};

#endif 
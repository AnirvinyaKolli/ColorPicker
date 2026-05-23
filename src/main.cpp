#include <wx/wx.h>
#include "ColorPicker.h"

class MyFrame : public wxFrame {
    public:
        MyFrame() 
        : wxFrame(nullptr, wxID_ANY, "Hello world!")
        {
            panel = new wxPanel(this);

            for (int i = 0; i < 3; i++) {
                sliders[i] = new wxSlider(panel, wxID_ANY, 0, 0, 255, wxPoint(20, 40+(50*i)));
                panel->Bind(wxEVT_SLIDER, &MyFrame::OnSliderChange, this, sliders[i]->GetId());
            }
            
            swatch = new wxPanel(panel, wxID_ANY, wxPoint(150, 40), wxSize(80, 80));
            hexText = new wxStaticText(panel, wxID_ANY, "#000000", wxPoint(20, 20));
        }

    private:
        wxPanel* panel;
        wxSlider* sliders[3];
        wxPanel* swatch; 
        wxStaticText* hexText;

        void OnExit(wxCommandEvent& e);
        void OnAbout(wxCommandEvent& e);
        void OnSliderChange(wxCommandEvent& e);
};

class ColorPicker : public wxApp {
    public:
        virtual bool OnInit()
        {
            MyFrame* frame = new MyFrame();
            frame->Show(true);
            return true;
        }
};



wxIMPLEMENT_APP(ColorPicker);


void MyFrame::OnSliderChange(wxCommandEvent& e) {
    int rVal = sliders[0]->GetValue();
    int gVal = sliders[1]->GetValue();
    int bVal = sliders[2]->GetValue();

    hexText->SetLabel(
        getHexcode(
            rVal,
            gVal,
            bVal
        )
    );

    swatch->SetBackgroundColour(wxColour(
        rVal,
        gVal,
        bVal
    ));

    swatch->Refresh();
}
#include <wx/wx.h>
#include "ColorPicker.h"
#include <string>
#include <vector>
class MyFrame : public wxFrame {
    public:
        MyFrame() 
        : wxFrame(nullptr, wxID_ANY, "Color Picker", wxDefaultPosition, wxSize(300, 500))
        {

            panel = new wxPanel(this);
            // Defining sliders
            for (int i = 0; i < 3; i++) {
                sliders[i] = new wxSlider(panel, wxID_ANY, 0, 0, 255, wxPoint(20, 40+(50*i)));
                sliders[i]->Bind(wxEVT_SLIDER, &MyFrame::OnSliderChange, this);
            }
            
            // Color swatch and text
            swatch = new wxPanel(panel, wxID_ANY, wxPoint(150, 40), wxSize(80, 80));
            hexText = new wxStaticText(panel, wxID_ANY, "#000000", wxPoint(20, 20));
            
            // Save button
            saveButton = new wxButton(panel, wxID_ANY, "Save color", wxPoint(20,200)); 
            saveButton->Bind(wxEVT_BUTTON, &MyFrame::OnButtonPress, this);

            // Color for Astheticss 
            hexText->SetForegroundColour(wxColour(255,255,255));
            panel->SetBackgroundColour(0);
        }

    private:
        wxPanel* panel;
        wxSlider* sliders[3];
        wxPanel* swatch; 
        wxStaticText* hexText;
        wxButton* saveButton; 
        std::vector<wxButton*> savedSwatches;

        void OnExit(wxCommandEvent& e);
        void OnAbout(wxCommandEvent& e);
        void OnSliderChange(wxCommandEvent& e);
        void OnButtonPress(wxCommandEvent& e); 
        void OnSwatchPressed(wxCommandEvent& e);

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

class SavedSwatch : public wxButton {
    public:
        SavedSwatch(wxPanel* parent, wxPoint position, std::string hexcode) 
        : wxButton( parent, wxID_ANY, "", position, wxSize(20, 20)) {this->hexcode = hexcode;}

        std::string hexcode; 
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

void MyFrame::OnButtonPress(wxCommandEvent& e) {
    wxColour savedColor =  wxColor(
        sliders[0]->GetValue(),
        sliders[1]->GetValue(),
        sliders[2]->GetValue()
    ); 
    
    SavedSwatch* addedSwatch = new SavedSwatch(
        panel,
        wxPoint(20 + savedSwatches.size() * 30, 240),
        getHexcode(        
            sliders[0]->GetValue(),
            sliders[1]->GetValue(),
            sliders[2]->GetValue()
        )
    );

    addedSwatch->SetBackgroundColour(savedColor);
    addedSwatch->Bind(wxEVT_BUTTON, &MyFrame::OnSwatchPressed, this);
    addedSwatch->Show();
    savedSwatches.push_back(addedSwatch);
    panel->Layout();
    panel->Refresh();
}

void MyFrame::OnSwatchPressed(wxCommandEvent& e) {
    SavedSwatch* clicked = (SavedSwatch*)e.GetEventObject();
    copyToClipboard(clicked->hexcode); 
}
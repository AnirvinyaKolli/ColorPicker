#include <wx/wx.h>
#include "ColorPicker.h"
#include <string>
#include <vector>
class MyFrame : public wxFrame {
    public:
        MyFrame() 
        : wxFrame(nullptr, wxID_ANY, "Color Picker", wxDefaultPosition, wxSize(300, 500))
        {

            //Main panel 
            panel = new wxPanel(this);
            //Main sizer
            wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
            panel->SetSizer(mainSizer); 

            // Sliders 
            mixerPanel = new wxPanel(panel);
            wxBoxSizer* mixerSizer = new wxBoxSizer(wxHORIZONTAL);
            mixerPanel->SetSizer(mixerSizer);

            wxPanel* sliderPanel = new wxPanel(mixerPanel);
            wxBoxSizer* sliderSizer = new wxBoxSizer(wxVERTICAL); 
            sliderPanel->SetSizer(sliderSizer); 

            mixerSizer->Add(sliderPanel);

            swatch = new wxPanel(mixerPanel, wxID_ANY, wxDefaultPosition, wxSize(80, 80));
            swatch->SetBackgroundColour(wxColour(0,0,0));
            
            mixerSizer->Add(swatch);

            mainSizer->Add(mixerPanel);

            

            // Saved swatches
            swatchPanel = new wxPanel(panel);
            mainSizer->Add(swatchPanel);


            
            hexText = new wxStaticText(sliderPanel, wxID_ANY, "#000000");
            sliderSizer->Add(hexText);

            // Defining sliders
            for (int i = 0; i < 3; i++) {
                sliders[i] = new wxSlider(sliderPanel, wxID_ANY, 0, 0, 255);
                sliders[i]->Bind(wxEVT_SLIDER, &MyFrame::OnSliderChange, this);
                sliderSizer->Add(sliders[i]);

            }
            
            
            // Save button
            saveButton = new wxButton(sliderPanel, wxID_ANY, "Save color"); 
            saveButton->Bind(wxEVT_BUTTON, &MyFrame::OnButtonPress, this);
            sliderSizer->Add(saveButton);

            // Sizer for saved swatches 
            swatchSizer = new wxBoxSizer(wxHORIZONTAL);  
            swatchPanel->SetSizer(swatchSizer);

            // Color for Astheticss 
            hexText->SetForegroundColour(wxColour(255,255,255));
            panel->SetBackgroundColour(wxColour(50,50,50));
        }

    private:
        wxPanel* panel;
        wxPanel* mixerPanel;
        wxPanel* swatchPanel;

        wxSlider* sliders[3];
        wxPanel* swatch; 
        wxStaticText* hexText;
        wxButton* saveButton; 

        wxBoxSizer* swatchSizer; 

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
        SavedSwatch(wxPanel* parent, std::string hexcode) 
        : wxButton( parent, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20)) {this->hexcode = hexcode;}

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
        swatchPanel,
        getHexcode(        
            sliders[0]->GetValue(),
            sliders[1]->GetValue(),
            sliders[2]->GetValue()
        )
    );

    swatchSizer->Add(addedSwatch);
    addedSwatch->SetBackgroundColour(savedColor);
    addedSwatch->Bind(wxEVT_BUTTON, &MyFrame::OnSwatchPressed, this);
    addedSwatch->Show();

    panel->Layout();
    panel->Refresh();
}

void MyFrame::OnSwatchPressed(wxCommandEvent& e) {
    SavedSwatch* clicked = (SavedSwatch*)e.GetEventObject();
    copyToClipboard(clicked->hexcode); 

    wxMessageBox("Text copied", "confirmation", wxOK, this);
}
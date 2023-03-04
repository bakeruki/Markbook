#include "AddStudentDialog.h"
#include <string>

BEGIN_EVENT_TABLE(AddStudentDialog, wxDialog)
EVT_UPDATE_UI(wxID_OK, UpdateOkButton)
END_EVENT_TABLE()

AddStudentDialog::AddStudentDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
	const wxPoint& pos, const wxSize& size, long style) : 
	wxDialog(parent, id, title, pos, size, style)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	//first name field
	wxBoxSizer* firstNameSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxStaticText* firstNameLabel = new wxStaticText(this, wxID_ANY, _("First Name"));
	firstNameLabel->SetMinSize(wxSize(150, -1));
	firstNameLabel->SetFont(wxFontInfo(wxSize(0, 24)));
	
	firstNameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, 30));
	firstNameField->SetFont(wxFontInfo(wxSize(0, 24)));

	firstNameSizer->Add(firstNameLabel);
	firstNameSizer->Add(firstNameField, 1);
	
	mainSizer->Add(firstNameSizer, 0, wxEXPAND | wxALL, 5);

	//last name field
	wxBoxSizer* lastNameSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* lastNameLabel = new wxStaticText(this, wxID_ANY, _("Last Name"));
	lastNameLabel->SetMinSize(wxSize(150, -1));
	lastNameLabel->SetFont(wxFontInfo(wxSize(0, 24)));

	lastNameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, 30));
	lastNameField->SetFont(wxFontInfo(wxSize(0, 24)));

	lastNameSizer->Add(lastNameLabel);
	lastNameSizer->Add(lastNameField, 1);

	mainSizer->Add(lastNameSizer, 0, wxEXPAND | wxALL, 5);

	//average field
	wxBoxSizer* averageSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* averageLabel = new wxStaticText(this, wxID_ANY, _("Average"));
	averageLabel->SetMinSize(wxSize(150, -1));
	averageLabel->SetFont(wxFontInfo(wxSize(0, 24)));

	averageField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, 30));
	averageField->SetFont(wxFontInfo(wxSize(0, 24)));

	averageSizer->Add(averageLabel);
	averageSizer->Add(averageField, 1);

	mainSizer->Add(averageSizer, 0, wxEXPAND | wxALL, 5);

	//buttons
	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxBOTTOM, 5);

	SetSizer(mainSizer);
	SetMinSize(wxSize(400, -1));
	SetFont(wxFontInfo(wxSize(0, 24)));
	Fit();
}

bool AddStudentDialog::TransferDataFromWindow()
{
	firstName = firstNameField->GetValue();
	lastName = lastNameField->GetValue();
	average = std::stod(std::string(averageField->GetValue().mb_str()));

	return true;
}

void AddStudentDialog::UpdateOkButton(wxUpdateUIEvent& evt)
{
	evt.Enable(false);

	if (!firstNameField->GetValue().empty() && !lastNameField->GetValue().empty() && !averageField->GetValue().empty()) {
		std::string averageString = std::string(averageField->GetValue().mb_str());
		double average;

		//make sure the average field has a valid number.
		try {
			average = std::stod(averageString);
		}
		catch (std::invalid_argument) {
			return;
		}

		//make sure the average entered is between 0-100
		if (average >= 0 && average <= 100) {
			evt.Enable(true);
		}
	}
}

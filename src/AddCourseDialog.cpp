#include "AddCourseDialog.h"

BEGIN_EVENT_TABLE(AddCourseDialog, wxDialog)
EVT_UPDATE_UI(wxID_OK, UpdateOkButton)
END_EVENT_TABLE()

AddCourseDialog::AddCourseDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
	const wxPoint& pos, const wxSize& size, long style) :
	wxDialog(parent, id, title, pos, size, style)
{
	CreateControls();
}

bool AddCourseDialog::TransferDataFromWindow()
{
	teacher = teacherField->GetValue();
	subject = subjectField->GetValue();
	return true;
}

void AddCourseDialog::CreateControls()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	//teacher field
	wxBoxSizer* teacherSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* teacherLabel = new wxStaticText(this, wxID_ANY, _("Teacher"));
	teacherLabel->SetMinSize(wxSize(150, -1));
	teacherLabel->SetFont(wxFontInfo(wxSize(0, 24)));

	teacherField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, 30));
	teacherField->SetFont(wxFontInfo(wxSize(0, 24)));

	teacherSizer->Add(teacherLabel);
	teacherSizer->Add(teacherField, 1);

	mainSizer->Add(teacherSizer, 0, wxEXPAND | wxALL, 5);

	//subject field
	wxBoxSizer* subjectSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* subjectLabel = new wxStaticText(this, wxID_ANY, _("Subject"));
	subjectLabel->SetMinSize(wxSize(150, -1));
	subjectLabel->SetFont(wxFontInfo(wxSize(0, 24)));

	subjectField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, 30));
	subjectField->SetFont(wxFontInfo(wxSize(0, 24)));

	subjectSizer->Add(subjectLabel);
	subjectSizer->Add(subjectField, 1);

	mainSizer->Add(subjectSizer, 0, wxEXPAND | wxALL, 5);

	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxBOTTOM, 5);

	SetSizer(mainSizer);
	SetMinSize(wxSize(400, -1));
	SetFont(wxFontInfo(wxSize(0, 24)));
	Fit();
}

void AddCourseDialog::UpdateOkButton(wxUpdateUIEvent& evt)
{
	evt.Enable(false);

	if (!teacherField->GetValue().IsEmpty() && !subjectField->GetValue().IsEmpty()) {
		evt.Enable(true);
	}
}

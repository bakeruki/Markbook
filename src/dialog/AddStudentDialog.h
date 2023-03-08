#pragma once
#include <wx/wx.h>

class AddStudentDialog : public wxDialog
{
public:
	AddStudentDialog(wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);

	wxString GetFirstName() const { return firstName; }
	wxString GetLastName() const { return lastName; }
	double GetAverage() const { return average; }
private:
	virtual bool TransferDataFromWindow() override;

	void CreateControls();

	void UpdateOkButton(wxUpdateUIEvent& evt);

	wxTextCtrl* firstNameField;
	wxTextCtrl* lastNameField;
	wxTextCtrl* averageField;

	wxString firstName;
	wxString lastName;
	double average;

	DECLARE_EVENT_TABLE();
};


#pragma once
#include <wx/wx.h>

class AddCourseDialog : public wxDialog
{
public:
	AddCourseDialog(wxWindow* parent, wxWindowID id, const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE);
	wxString GetTeacher() const { return teacher; }
	wxString GetSubject() const { return subject; }

private:
	virtual bool TransferDataFromWindow() override;

	void CreateControls();

	void UpdateOkButton(wxUpdateUIEvent& evt);

	wxString teacher;
	wxString subject;

	wxTextCtrl* teacherField;
	wxTextCtrl* subjectField;

	DECLARE_EVENT_TABLE();
};


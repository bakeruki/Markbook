#pragma once
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Course.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void BindEventHandlers();

	wxArrayString BuildDropdownChoiceArray();
	void OnDropdownChange(wxCommandEvent& evt);

	void UpdateActiveCourse(wxString courseName);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxChoice* courseSelectDropdown;
	wxButton* addCourseButton;

	std::string headline;
	std::vector<Course> courses;
	Course activeCourse;
};


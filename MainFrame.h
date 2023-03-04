#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <string>
#include "Course.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	//init functions
	void CreateControls();
	void BindEventHandlers();

	//control creation helpers
	wxArrayString BuildDropdownChoiceArray();
	void BuildStudentList();

	//event handlers
	void OnDropdownChange(wxCommandEvent& evt);

	//event helpers
	void UpdateActiveCourse(wxString courseName);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxChoice* courseSelectDropdown;
	wxButton* addCourseButton;
	wxListView* studentList;

	std::string headline;
	std::vector<Course> courses;
	Course activeCourse;
};


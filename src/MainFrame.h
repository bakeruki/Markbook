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
	void PopulateStudentList();

	//event handlers
	void OnDropdownChange(wxCommandEvent& evt);
	void OnAddStudentButtonClick(wxCommandEvent& evt);

	//event helpers
	void UpdateActiveCourse(wxString courseName);

	//elements
	wxPanel* panel;
	wxStaticText* headlineText;
	wxChoice* courseSelectDropdown;
	wxButton* addCourseButton;
	wxButton* addStudentButton;
	wxListView* studentList;

	//variables
	std::string headline;
	std::vector<Course> courses;
	Course activeCourse;
};
